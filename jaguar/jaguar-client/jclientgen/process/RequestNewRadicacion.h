/* 
 * File:   RequestNewRadicacion.h
 * Author: cross
 *
 * Created on November 21, 2010, 7:00 PM
 */

#ifndef REQUESTNEWRADICACION_H
#define	REQUESTNEWRADICACION_H

#include "net/request.h"

class RequestNewRadicacion: public Request {
public:
    RequestNewRadicacion();
    RequestNewRadicacion(const RequestNewRadicacion& orig);
    virtual ~RequestNewRadicacion();
private:

};

#endif	/* REQUESTNEWRADICACION_H */

