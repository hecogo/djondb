#include "networkcommon.h"
#include "util/util.h"
#include <stdlib.h>
#include <string.h>

map<int, Controller*> m_controllers;

Response* RequestProcessor::processRequest(Request* request) {
    Controller* controller = m_controllers.find(request->getType())->second;
    Response* response = controller->processRequest(request);

    return response;
};

const char* getData(const char* data, int offset, int size) {
//    char *result = (char*)malloc(size*sizeof(char));
//    memset(result, 0, size);
    string* result = new string();

    for (int x = offset; x < (offset + size); x++) {
        result->push_back(data[x]);
    }
    return result->c_str();
}

Request::Request(const char* data) {
    Logger* log = getLogger(NULL);

    parameters = new map<string, string*>();

    const char *readed = getData(data, 0, 4);
    type = atoi(readed);

    int pos = 4;
    while (true) {
        readed = getData(data, pos, 4);
        pos += 4;
        if (strcmp(readed, "FFFF") != 0) {
            string* codename = new string(readed);
            trim(codename);
            if (log->isDebug()) log->debug("codename: " + *codename);
            readed = getData(data, pos, 2);
            pos += 2;
            int size = atoi(readed);
            if (log->isDebug()) log->debug("size: " + toString(size));
            const char* value = getData(data, pos, size);
            if (log->isDebug()) log->debug("value: " + *(new string(value)));
            pos += size;
            addParameter(*codename, new string(value));
        } else {
            break;
        }
    }
};

void Request::addParameter(string codename, string* value) {
    parameters->insert(pair<string, string*>(codename, value));
};


int Request::getType() {
    return type;
};

string* Request::getParameter(string codename) {
    return parameters->find(codename)->second;
};

vector<string>* Request::getCodeNames() {
    vector<string>* result = new vector<string>();
    map<string,string*>::iterator it;
    for (it = parameters->begin(); it != parameters->end(); it++) {
        result->push_back(it->first);
    }
    return result;
};

Response::Response(string* _data) {
    data = _data;
};

string* Response::getData() {
    return data;
};

void Response::addParameter(char* name, void* contents, int size) {
    if (strlen(name) > 4) {
        throw NetworkException(new string("The codename cannot be larger than 4 bytes"));
    }
    if (!data) {
        data = new string();
    }
    data->append(name, (char*)contents);
}

Controller::Controller(int _requestType) {
    requestType = _requestType;
};

int Controller::getRequestType() {
    return requestType;
};

Response* Controller::processRequest(Request* request) {
    return NULL;
}

void Controller::selfRegister() {
    m_controllers.insert(pair<int, Controller*>(requestType, this));
};

