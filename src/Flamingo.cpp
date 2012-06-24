
#include "FL/Flamingo.h"

Flamingo::Flamingo() {
    _running = true;
    _display = NULL;
}

Flamingo::~Flamingo() {

}

int Flamingo::Execute() {

    if (Init() == -1) {
        return -1;
    }

    while (_running) {
        if (HandleEvents() == -1) {
            _running = false;
            break;
        }
        Step();
        Render();
    }

    Cleanup();
    return 0;
}

void Flamingo::Step() {

    _entityManager->Process();

}

int main (int argc, char *arg[]) {

    Flamingo flamingo;

    return flamingo.Execute();

}

