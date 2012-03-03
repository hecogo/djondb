// *********************************************************************************************************************
// file:
// author: Juan Pablo Crossley (crossleyjuan@gmail.com)
// created:
// updated:
// license:
// 
// This file is part of the djondb project, for license information please refer to the LICENSE file,
// the application and libraries are provided as-is and free of use under the terms explained in the file LICENSE
// Its authors create this application in order to make the world a better place to live, but you should use it on
// your own risks.
// 
// Also, be adviced that, the GPL license force the committers to ensure this application will be free of use, thus
// if you do any modification you will be required to provide it for free unless you use it for personal use (you may 
// charge yourself if you want), bare in mind that you will be required to provide a copy of the license terms that ensures
// this program will be open sourced and all its derivated work will be too.
// *********************************************************************************************************************

#include <string.h>
#include <iostream>
#include <sstream>
#include <map>

#include "util.h"
#include "network.h"
#include "networkservice.h"
#include "networkinputstream.h"
#include "networkoutputstream.h"
#include "command.h"
#include "commandreader.h"
#include "dbcontroller.h"
#include <stdlib.h>
#include <boost/shared_ptr.hpp>
#include <memory>
#ifndef WINDOWS
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#else
	#include <winsock.h>
#endif
//#include <sys/wait.h>

#include "defs.h"
//#include "dbjaguar.h"

// Windows does not have this definition
#ifndef socklen_t
	#define socklen_t int
#endif

#define SERVER_PORT 1243


// Just declared to be used later
void *startSocketListener(void* arg);
int processRequest(void* arg);

bool running;
bool processing;
// id listening socket
int sock;
pthread_mutex_t requests_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  request_cv =   PTHREAD_COND_INITIALIZER;

Logger* log;
Thread* m_thread; // Main thread

DBController* __dbController;
std::map<int, NetworkInputStream*>  __mapInput;
std::map<int, NetworkOutputStream*> __mapOutput;


NetworkService::NetworkService() {
    log = getLogger(NULL);
    m_thread = NULL;
}

NetworkService::~NetworkService() {
    delete(log);
}

void NetworkService::start() { //throw (NetworkException*) {
    if (running) {
        throw new NetworkException(new string("The network service is already active. Try stopping it first"));
    }
    if (log->isInfo()) log->info("Starting network service");

    __dbController = new DBController();
    __dbController->initialize();
    m_thread = new Thread(&startSocketListener);
    m_thread->start(NULL);

}

void NetworkService::stop() { //throw (NetworkException*) {
    log->info("Shutting down the network service");
    if (!running) {
        throw new NetworkException(new string("The network service is not running. Try starting it first"));
    }
    running = false;
    if (processing) {
        cout << "Stop requested but still working" << endl;
    }
    while (processing) {
		Thread::sleep(1000);
    }
    __dbController->shutdown();
#ifndef WINDOWS
    int res = close(sock);
#else
    int res = closesocket(sock);
#endif
    if (res != 0) {
        log->error("The close method returned: " + toString(res));
    }

    m_thread->join();

    if (m_thread) delete(m_thread);
}

void *startSocketListener(void* arg) {

#ifdef WINDOWS
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return NULL;
    }
#endif

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock < 0) {
		log->error(std::string("Error creating the socked"));
    }

    fd_set master;    // master file descriptor list
    FD_ZERO(&master);    // clear the master and temp sets
    fd_set read_fds;  // temp file descriptor list for select()
    FD_ZERO(&read_fds);

    sockaddr_in addr;
    int port = SERVER_PORT;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // the port should be converted to network byte order
    addr.sin_addr.s_addr = INADDR_ANY; // Server address, any to take the current ip address of the host
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) & reuse, sizeof (reuse)) < 0) {
		log->error(std::string("Setting SO_REUSEADDR error"));
    }

    if (bind(sock, (sockaddr *) &addr, sizeof (addr)) < 0) {
		log->error(std::string("Error binding"));
    }
    listen(sock, 5);
    log->info("Accepting new connections");
    running = true;

    // Sets the nonblocking option for this socket
	int flags;

	/* If they have O_NONBLOCK, use the Posix way to do it */
#if defined(O_NONBLOCK)
	/* Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5. */
	if (-1 == (flags = fcntl(_socket, F_GETFL, 0)))
		flags = 0;
	fcntl(sock, F_SETFL, flags | O_NONBLOCK);
#else
#ifndef WINDOWS
	/* Otherwise, use the old way of doing it */
	flags = 1;
	ioctl(sock, FIOBIO, &flags);
#else
	u_long f = 1;
	ioctlsocket(sock, FIONBIO, &f);
#endif
#endif

    processing = false;
    int fdmax = sock;
    FD_SET(sock, &master); // add to master set

    while (running) {
        fd_set read;
        FD_ZERO(&read);
        FD_SET(sock, &read);
        timeval val;
        val.tv_sec = 1;
        val.tv_usec = 0;
        read_fds = master;
        int newsocket = select(fdmax + 1, &read_fds, NULL, NULL, &val);
        for (int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) {
                // the max is the listener
                if (i == sock) {
                    sockaddr_in cliaddr;
                    socklen_t clilen = sizeof (cliaddr);
                    int newsocket = accept(sock, (sockaddr *) & cliaddr, &clilen);

                    if (newsocket == -1) {
                        log->debug("Error accepting");
                    } else {
                        FD_SET(newsocket, &master); // add to master set
                        if (newsocket > fdmax) {    // keep track of the max
                            fdmax = newsocket;
                        }
                        log->info("Accepted socket %d", newsocket);

                    }
                } else {
                    processing = true;
                    if (processRequest((void*) &i) < 0)  {
                        FD_CLR(i, &master);
                        if (i == fdmax) {
                            fdmax--;
                        }
                    }
                    processing = false;
                }
    //            pthread_mutex_lock(&requests_lock);
                //processRequest((void*)&sock);
                /*
                Thread* thread = new Thread(&processRequest);
                thread->start((void*) &sock);
                */
    //            pthread_cond_wait(&request_cv, &requests_lock);
    //            pthread_mutex_unlock(&requests_lock);
    //            m_requestThreads.push_back(thread);
            }
        }
        for (std::map<int, NetworkInputStream*>::iterator i = __mapInput.begin(); i != __mapInput.end(); i++) {
            int sock = i->first;
            NetworkInputStream* nis = i->second;
            if (nis->available() > 0) {
                if (processRequest((void*)&sock) < 0) {
                    // If the socket was closed by the other end, then remove it from the
                    // pull
                    FD_CLR(sock, &master);
                    if (sock == fdmax) {
                        fdmax--;
                    }
                }
            }
        }
    }

    log->info("Thread stopped");

#ifdef WINDOWS
	WSACleanup();
#endif
//    pthread_exit(arg);
    return NULL;
}
    int __status;

int processRequest(void *arg) {
    int sock = *((int*) arg);
    __status = 0;
    NetworkInputStream* nis = NULL;
    NetworkOutputStream* nos = NULL;
    std::map<int, NetworkInputStream*>::iterator itNis = __mapInput.find(sock);
    std::map<int, NetworkOutputStream*>::iterator itNos = __mapOutput.find(sock);
    if (__mapInput.find(sock) == __mapInput.end()) {
        nis = new NetworkInputStream(sock);
        nos = new NetworkOutputStream(sock);
        nos->setNonblocking();
        nos->disableNagle();
        nis->setNonblocking();
        __mapInput.insert(pair<int, NetworkInputStream*>(sock, nis));
        __mapOutput.insert(pair<int, NetworkOutputStream*>(sock, nos));
    } else {
        nis = itNis->second;
        nos = itNos->second;
    }
//    sockaddr_in cliaddr;
//    socklen_t clilen = sizeof (cliaddr);
//    int clientSocket = accept(sock, (sockaddr *) & cliaddr, &clilen);
//    log->debug("Accepted");

//    pthread_mutex_lock(&requests_lock);
//    int rescond = pthread_cond_signal(&request_cv);
//    pthread_mutex_unlock(&requests_lock);

    if (log->isDebug()) log->debug("Receiving request");

    // Checks version
    int commands = 0;
    if (nis->isClosed()) {
        if (log->isDebug()) log->debug("The connection was closed and nothing is available to be processed");
        __mapInput.erase(itNis);
        __mapOutput.erase(itNos);
        return -1;
    }
    std::auto_ptr<CommandReader> reader(new CommandReader(nis));
    // Will wait 5 secs, if no other command is available just close the connection
//    while (nis->waitAvailable(5) > 0) {
//        log->debug("New command available");
        // Reads command
        std::auto_ptr<Command> cmd(reader->readCommand());
        commands++;
        cmd->setDBController(__dbController);
        try {
            if (cmd->commandType() != CLOSECONNECTION) {
                cmd->execute();
                cmd->writeResult(nos);
            } else {
                if (log->isDebug()) log->debug("Close command received");
            }
        } catch (const char *errmsg)
        {
            std::cerr << "error message from connection: " << errmsg << "\n";
            return 1;
        }
//    }

    if (log->isDebug()) log->debug("%d Executed.", commands);

    return 0;
}


