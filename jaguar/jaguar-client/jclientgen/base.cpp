#include "jaguarui.h"
#include "Radicacion.h"
#include "Clientes.h"

ScreenBase* createRadicacion() {
    Radicacion* rad = new Radicacion();
    return rad;
}

ScreenBase* createClientes() {
    Clientes* cl = new Clientes();
    return cl;
}

void registerClient() {
    addScreen(1, &createRadicacion, "Radicacion");
    addScreen(2, &createClientes, "Clientes");
}