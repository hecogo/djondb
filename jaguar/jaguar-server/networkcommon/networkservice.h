
/*
 * File:   networkservice.h
 * Author: JuanC
 *
 * Created on November 13, 2008, 5:48 PM
 */

#include "net/defs.h"
class NetworkService {
public:
    NetworkService();
    void start() throw (NetworkException);

    void stop() throw (NetworkException);
};

