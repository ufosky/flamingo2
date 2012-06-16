
#include <iostream>

#include "flamingo.h"

Flamingo::Flamingo() {
    running = true;

    Surf_display = NULL;
}

int Flamingo::execute() {

    if (init() == -1) {
        return -1;
    }

    while (running) {
        if (handle_events() == -1) {
            running = false;
            break;
        }
        step();
        render();
    }

    cleanup();
    return 0;
}

void Flamingo::step() {

}

int main (int argc, char *arg[]) {

    Flamingo flamingo;

    return flamingo.execute();

}

