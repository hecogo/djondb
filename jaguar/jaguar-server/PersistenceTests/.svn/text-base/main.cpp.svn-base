/* 
 * File:   main.cpp
 * Author: cross
 *
 * Created on November 19, 2008, 11:51 PM
 */

#include <iostream>
#include <fstream>


#include "classdef.h"

using namespace std;

void persist() {
    ofstream myfile;
    myfile.open("test.txt", ios::app);
    myfile << "test" << endl;
    myfile.close();
}

void read() {
    ifstream myfile;
    myfile.open("test.txt");
    
    string text;
    myfile >> text;
    cout << "Leido: " << text << endl;
    myfile.close();
}

void persistClass() {
    ofstream myfile;
    myfile.open("testClass.dat", ios::binary);
    TestClass* test = new TestClass(5, 2);
    
    myfile.write((char*)test, sizeof(*test));
    myfile.close();
}

void readClass() {
    ifstream myfile;
    myfile.open("testClass.dat", ios::binary);
    
    TestClass* test = (TestClass*)malloc(sizeof(TestClass));
    myfile.read((char*)test, sizeof(*test));
    myfile.close();
    
    cout << "Object readed I:" << test->getI() << ", B:" << test->getB() << endl;
}
/*
 * 
 */
int main(int argc, char** argv) {
    persist();
    read();
    persistClass();
    readClass();
    return (EXIT_SUCCESS);
}

