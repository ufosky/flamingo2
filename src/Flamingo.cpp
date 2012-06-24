
#include "FL/Flamingo.h"

Flamingo::Flamingo() {
    _running = true;
    _display = NULL;
}

Flamingo::~Flamingo() {

}

int Flamingo::Execute() {

    if (_Init() == -1) {
        return -1;
    }

    while (_running) {
        if (_HandleEvents() == -1) {
            _running = false;
            break;
        }
        _Step();
        _Render();
    }

    Cleanup();
    return 0;
}

void Flamingo::_Step() {

    Flamingo::PreStep();

    _entityManager->Process();

    Flamingo::PostStep();

}

int main (int argc, char *arg[]) {

    Flamingo flamingo;

    return flamingo.Execute();

}

