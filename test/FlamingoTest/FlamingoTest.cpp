
#include "FlamingoTest.h"
#include "TestComponent.h"

int FlamingoTest::Init() {

    Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new TestComponent());

    return 0;
}

int main (int argc, char *arg[]) {

    FlamingoTest flamingo = FlamingoTest();

    return flamingo.Execute();

}

