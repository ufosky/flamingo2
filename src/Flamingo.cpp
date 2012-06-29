
#include "FL/Flamingo.h"

Flamingo::Flamingo() {
    _running = true;
    _display = NULL;
}

Flamingo::~Flamingo() {

}

int Flamingo::Execute(int argc, char *argv[]) {

    if (_Init(argc, argv) == -1) {
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

    _Cleanup();
    return 0;
}

void Flamingo::_Step() {

    this->PreStep();

    _entityManager->Process();

    this->PostStep();

}

//int main (int argc, char *arg[]) {
//
//    Flamingo flamingo;
//
//    return flamingo.Execute();
//
//}

