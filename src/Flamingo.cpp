
#include "FL/Flamingo.h"

#include "physfs.h"

Flamingo::Flamingo() {
    _running = true;
    _display = NULL;
}

Flamingo::~Flamingo() {

}

#include <iostream>

int Flamingo::Execute(int argc, char *argv[]) {

    if (_Init(argc, argv) == -1) {
        return -1;
    }

    double timestep = 1.0 / 2;
    double accumulator = 0, interpolation;

    long int oldTime, newTime, deltaTime;
    oldTime = _masterClock->GetTime();

    while (_running) {

        _masterClock->Sync();
        oldTime = newTime;
        newTime = _masterClock->GetTime();
        deltaTime = newTime - oldTime;
        accumulator += deltaTime;

        inputSystem->Process();
        if (inputSystem->quit) {
            _running = false;
            break;
        }

        while (accumulator >= timestep) {
            accumulator -= timestep;
            _Step();
        }

        //std::cout << _masterClock->GetFPS() << "\n";

        interpolation = accumulator / timestep;

        _Render();
    }

    _Cleanup();
    return 0;
}

void Flamingo::_Step() {

    //this->PreStep();
    //this->PostStep();
}

