#include "util.h"

string toString(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}
