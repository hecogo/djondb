#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>
#include <map>
#include <fcntl.h>

#include "util.h"
#include "networkservice.h"
#include "dbjaguar.h"
#include "net/request.h"
#include "net/response.h"
#include "net/requestprocessor.h"
#include "net/controller.h"

using namespace dbjaguar;

// Just declared to be used later
void *startSocketListener(void* arg);
void *processRequest(void* arg);

Logger* log;
bool running;
bool accepting;
// id listening socket
int sock;
pthread_mutex_t requests_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  request_cv =   PTHREAD_COND_INITIALIZER;
map<int, Controller*> m_controllers;

Connection* m_con;
Thread* m_thread; // Main thread

// Scripts addition
extern void AddWorkflow();
extern void loadProcessDefinitions(Connection* con);
extern void unloadProcessDefinitions();

void initializeDatabase() throw (DBException) {
    if (log->isInfo()) log->info("Initializing DB.");
    m_con = getDefaultMDConnection();
}

void initializeProcessDefinitions() {
    loadProcessDefinitions(m_con);
}

NetworkService::NetworkService() {
    log = getLogger(NULL);
}

NetworkService::~NetworkService() {
    delete(log);
}

void registerControllers() {
    if (log->isDebug()) log->debug("Registering controllers");

    AddWorkflow();
}

void NetworkService::start() throw (NetworkException) {
    if (running) {
        throw NetworkException(new string("The network service is already active. Try stopping it first"));
    }
    if (log->isInfo()) log->info("Starting network service");

    registerControllers();
    initializeDatabase();
    initializeProcessDefinitions();

    m_thread = new Thread(&startSocketListener);
    m_thread->start(NULL);

}

void NetworkService::stop() throw (NetworkException) {
    log->info("Shutting down the network service");
    if (!running) {
        throw NetworkException(new string("The network service is not running. Try starting it first"));
    }
    running = false;
    while (accepting) {
        sleep(1);
    }
    int res = close(sock);
    m_con->close();
    if (res != 0) {
        log->error("The close method returned: " + toString(res));
    }
    
    unloadProcessDefinitions();
    
    cache::cleanGlobalCache();

    for (map<int, Controller*>::iterator iter =  m_controllers.begin(); iter != m_controllers.end(); iter++) {
        delete(iter->second);
    }
    m_controllers.clear();
    destroyPool();
    delete(m_thread);
}

void *startSocketListener(void* arg) {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        log->error("Error creating the socked");
    }

    sockaddr_in* addr = new sockaddr_in();
    int port = 1043;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port); // the port should be converted to network byte order
    addr->sin_addr.s_addr = INADDR_ANY; // Server address, any to take the current ip address of the host
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *) & reuse, sizeof (reuse)) < 0) {
        log->error("Setting SO_REUSEADDR error");
    }

    if (bind(sock, (sockaddr *) addr, sizeof (*addr)) < 0) {
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
        }
    }
    accepting = false;

    delete(addr);

    pthread_exit(arg);
    return NULL;
};

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

    int readed;
    stringstream sreaded;

    char buffer[256];
    memset(buffer, 0, 256);

    bool reachEnd = false;
    // Reads the socket data until the socket sends the end signal 'FFFF'
    while (!reachEnd) {
        fd_set read;
        FD_ZERO(&read);
        FD_SET(sock, &read);
        timeval val;
        val.tv_sec = 10;
        val.tv_usec = 0;

        readed = recv(clientSocket, buffer, 255, 0);
        if (readed < 0) {
            if (log->isDebug()) log->debug("Readed: " + toString(readed));
            int result = select(clientSocket + 1, &read, NULL, NULL, &val);

            if (log->isDebug()) log->debug("result: " + toString(result));
            if (result < 0) {
                log->info("Timeout");
                close(clientSocket);
                return NULL;
            } else {
                readed = recv(clientSocket, buffer, 255, 0);
            }
        }
        sreaded << buffer;
        string s = sreaded.str();
        string::reverse_iterator it;
        it = s.rbegin();
        for (int x = 0; x < 4; x++) {
            char c = *it;
            if (c != 'F') {
                break;
            }
            it++;
            if (x == 3)
                reachEnd = true;
        }
        memset(buffer, 0, 256);
    }

    if (log->isDebug()) log->debug("Buffer received, size: " + toString(readed));

    Request* request = new Request(sreaded.str().c_str());

    RequestProcessor* processor = new RequestProcessor();
    Response* response = processor->processRequest(request);

    string* sresp = response->getData();

    write(clientSocket, sresp->c_str(), sresp->length());
    close(clientSocket);

    delete(response);
    delete(processor);
    return NULL;
};


