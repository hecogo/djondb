/* 
 * File:   RequestProcessor.cpp
 * Author: cross
 * 
 * Created on November 24, 2009, 8:21 PM
 */

#include "requestprocessor.h"
#include "controller.h"
#include "net/request.h"

extern map<int, Controller*> m_controllers;

RequestProcessor::RequestProcessor() {
}

RequestProcessor::~RequestProcessor() {
}

Response* RequestProcessor::processRequest(Request* request) {
    Controller* controller = m_controllers.find(request->getType())->second;
    Response* response = controller->processRequest(request);

    return response;
};

