/* 
 * File:   Controller.cpp
 * Author: cross
 * 
 * Created on November 24, 2009, 8:25 PM
 */

#include "controller.h"

Controller::Controller(int _requestType) {
    requestType = _requestType;
};

int Controller::getRequestType() {
    return requestType;
};

void Controller::selfRegister() {
    m_controllers.insert(pair<int, Controller*>(requestType, this));
};

Controller::~Controller() {
}

