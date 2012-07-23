#ifndef NETWORKSERVICE_H_INCLUDED
#define NETWORKSERVICE_H_INCLUDED

/*
 * File:   networkservice.h
 * Author: JuanC
 *
 * Created on November 13, 2008, 5:48 PM
 */

//#include "network.h"

#define SERVER_PORT 1243

class NetworkService {
public:
    NetworkService();
    virtual ~NetworkService();

    void start();// throw (NetworkException*);

    void stop();// throw (NetworkException*);

	 bool running() const;
	 void setRunning(bool);
private:
	 bool _running;
};


#endif // NETWORKSERVICE_H_INCLUDED
