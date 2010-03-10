#include "jaguarui.h"
#include "Radicacion.h"

ScreenBase* createRadicacion() {
    Radicacion* rad = new Radicacion();
    return rad;
}

void registerClient() {
    addScreen(1, &createRadicacion, "Radicacion");
}