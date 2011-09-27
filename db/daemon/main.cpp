#include <iostream>

#include "service.h"
#include <stdio.h>

using namespace std;

int main()
{
    service_startup();

    int c = getchar();

    service_shutdown();
    return 0;
}
