#include "util.h"

string toString(float value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

vector<string*>* listDir(string dir, string ext) {
    DIR* dirp = opendir(dir.c_str());
    vector<string*>* res = new vector<string*>();
    dirent* dirfound;
    while ((dirfound = readdir(dirp)) != NULL) {
        stringstream ssfileext;
        ssfileext << dirfound->d_name;
        string fileext = ssfileext.str();
        fileext = fileext.substr(fileext.rfind("."));
        if (fileext.compare(ext) == 0) {
            string* fileFound = new string(dirfound->d_name);
            res->push_back(fileFound);
        }
    }

    return res;
}

const char* strtrim(char* str) {
    string response (str);
    response.erase(response.find_last_not_of(" ") + 1);
    return response.c_str();
}

void trim(string* str) {
    str->erase(str->find_last_not_of(" ") + 1);
}
