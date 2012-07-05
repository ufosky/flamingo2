
#include "FL/Flamingo.h"

#include "physfs.h"

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
        inputSystem->Process();
        if (inputSystem->quit) {
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
    
    this->PostStep();
}

