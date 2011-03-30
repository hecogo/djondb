/* 
 * File:   RequestNewRadicacion.cpp
 * Author: cross
 * 
 * Created on November 21, 2010, 7:00 PM
 */

#include "RequestNewRadicacion.h"

RequestNewRadicacion::RequestNewRadicacion()
: Request(1) {
    addParameter("ACT ", new string("NEW"));
    addParameter("DEFI", new string("1"));
}

RequestNewRadicacion::RequestNewRadicacion(const RequestNewRadicacion& orig)
: Request(orig) {
}

RequestNewRadicacion::~RequestNewRadicacion() {
}

