#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

class NetworkService;

int service_startup();
int service_shutdown();
int service_restart();

bool service_running();

#endif // SERVICE_H_INCLUDED
