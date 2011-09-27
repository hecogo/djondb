#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <map>

#include "util.h"
#include "network.h"
#include "networkservice.h"
#include "networkinputstream.h"
#include "command.h"
#include "commandparser.h"

#include "defs.h"
//#include "dbjaguar.h"
#include "config.h"


#define SERVER_PORT 1243


// Just declared to be used later
void *startSocketListener(void* arg);
void *processRequest(void* arg);

bool running;
bool accepting;
// id listening socket
int sock;
pthread_mutex_t requests_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  request_cv =   PTHREAD_COND_INITIALIZER;

Logger* log;
Thread* m_thread; // Main thread


NetworkService::NetworkService() {
    log = getLogger(NULL);
}

NetworkService::~NetworkService() {
    delete(log);
}

void NetworkService::start() { //throw (NetworkException*) {
    if (running) {
        throw new NetworkException(new string("The network service is already active. Try stopping it first"));
    }
    if (log->isInfo()) log->info("Starting network service");


    m_thread = new Thread(&startSocketListener);
    m_thread->start(NULL);

}

void NetworkService::stop() { //throw (NetworkException*) {
    log->info("Shutting down the network service");
    if (!running) {
        throw new NetworkException(new string("The network service is not running. Try starting it first"));
    }
    running = false;
    while (accepting) {
        sleep(1);
    }
    int res = close(sock);
    if (res != 0) {
        log->error("The close method returned: " + toString(res));
    }

    m_thread->join();

    delete(m_thread);
}

void *startSocketListener(void* arg) {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        log->error("Error creating the socked");
    }

    sockaddr_in addr;
    int port = SERVER_PORT;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // the port should be converted to network byte order
    addr.sin_addr.s_addr = INADDR_ANY; // Server address, any to take the current ip address of the host
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) & reuse, sizeof (reuse)) < 0) {
        log->error("Setting SO_REUSEADDR error");
    }

    if (bind(sock, (sockaddr *) &addr, sizeof (addr)) < 0) {
        log->error("Error binding");
    }
    listen(sock, 5);
    log->info("Accepting new connections");
    running = true;
    // Sets the nonblocking option for this socket
    int currentFlag = fcntl(sock, F_GETFD);
    currentFlag = currentFlag | O_NONBLOCK;
    fcntl(sock, F_SETFL, currentFlag);

    accepting = false;
    while (running) {
        sockaddr_in cliaddr;
        socklen_t clilen = sizeof (cliaddr);
        int newsocket = accept(sock, (sockaddr *) & cliaddr, &clilen);
        fd_set read;
        FD_ZERO(&read);
        FD_SET(sock, &read);
        timeval val;
        val.tv_sec = 1;
        val.tv_usec = 0;

        newsocket = select(sock + 1, &read, NULL, NULL, &val);

        if (newsocket > 0) {
            accepting = true;
            pthread_mutex_lock(&requests_lock);
            //processRequest((void*)&sock);
            Thread* thread = new Thread(&processRequest);
            thread->start((void*) &sock);
            pthread_cond_wait(&request_cv, &requests_lock);
            pthread_mutex_unlock(&requests_lock);
//            m_requestThreads.push_back(thread);
        }
    }
    accepting = false;

    log->info("Thread stopped");
//    pthread_exit(arg);
    return NULL;
}

void *processRequest(void *arg) {
    int sock = *((int*) arg);
    sockaddr_in cliaddr;
    socklen_t clilen = sizeof (cliaddr);
    int clientSocket = accept(sock, (sockaddr *) & cliaddr, &clilen);
    log->debug("Accepted");

    pthread_mutex_lock(&requests_lock);
    int rescond = pthread_cond_signal(&request_cv);
    pthread_mutex_unlock(&requests_lock);

    if (log->isDebug()) log->debug("Receiving request");

    NetworkInputStream* nis = new NetworkInputStream(clientSocket);

    // Checks version
    char* version = nis->readChars();
    // Reads command
    CommandParser parser;
    Command* cmd = parser.parse(nis);


//    int readed;
//    stringstream sreaded;
//
//    char buffer[256];
//    memset(buffer, 0, 256);
//
//    bool reachEnd = false;
//    // Reads the socket data until the socket sends the end signal 'FFFF'
//    while (!reachEnd) {
//
//        readed = recv(clientSocket, buffer, 255, 0);
//        if (readed < 0) {
//            if (log->isDebug()) log->debug("Readed: " + toString(readed));
//            } else {
//                readed = recv(clientSocket, buffer, 255, 0);
//            }
//        }
//        sreaded << buffer;
//        string s = sreaded.str();
//        string::reverse_iterator it;
//        it = s.rbegin();
//        for (int x = 0; x < 4; x++) {
//            char c = *it;
//            if (c != 'F') {
//                break;
//            }
//            it++;
//            if (x == 3)
//                reachEnd = true;
//        }
//        memset(buffer, 0, 256);
//    }

//    if (log->isDebug()) log->debug("Buffer received, size: " + toString(readed));

//    write(clientSocket, sresp->c_str(), sresp->length());
    close(clientSocket);

    return NULL;
}


