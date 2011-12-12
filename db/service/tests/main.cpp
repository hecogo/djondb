#include <iostream>
#include "service.h"

#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{
    service_startup();

    getchar();

    service_shutdown();

    return 0;
}
