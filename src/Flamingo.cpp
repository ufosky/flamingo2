
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

void Flamingo::MountDirectory(std::string path, std::string mtpt, int pre) {

    PHYSFS_mount(path.c_str(), mtpt.c_str(), pre);

}

void Flamingo::_Step() {

    this->PreStep();

    //_entityManager->Process();

    this->PostStep();

}

