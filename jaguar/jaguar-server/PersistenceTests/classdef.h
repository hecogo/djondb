/* 
 * File:   classdef.h
 * Author: cross
 *
 * Created on November 19, 2008, 11:56 PM
 */

#ifndef _CLASSDEF_H
#define	_CLASSDEF_H

class TestClass {
private:
    int i;
    int b;
public:
    TestClass() {}
    
    TestClass(int _i, int _b) {
        i = _i;
        b = _b;
    }
    
    int getI() {
        return i;
    }
    
    int getB() {
        return b;
    }
};

#endif	/* _CLASSDEF_H */

