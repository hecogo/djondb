/* 
 * File:   main.cpp
 * Author: cross
 *
 * Created on November 18, 2008, 9:35 PM
 */

#include <iostream>
#include <iosfwd>
#include "util/threads.h"

using namespace std;

void *run(void* arg) {
    int i = *(int*)arg;
    sleep(i);
    cout << "Test" << i << endl;
    
}

int main(int argc, char** argv) {
    Thread* t = new Thread(&run);
    int p = 3;
    t->start(&p);
    Thread* t2 = new Thread(&run);
    int n = 1;
    t2->start(&n);
    
    t->join();
    t2->join();
    
    
    return (EXIT_SUCCESS);
}
