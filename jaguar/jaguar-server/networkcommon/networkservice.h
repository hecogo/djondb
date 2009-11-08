
/*
 * File:   networkservice.h
 * Author: JuanC
 *
 * Created on November 13, 2008, 5:48 PM
 */
#include <sys/socket.h>
#include <string>
#include <map>
#include <vector>
#include "networkcommon.h"

using namespace std;

class NetworkService {
public:
    NetworkService();
    void start() throw (NetworkException);

    void stop() throw (NetworkException);
};

