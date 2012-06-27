
#include "FlamingoTest.h"
#include "TestComponent.h"
#include "FL/Components/PositionComp.h"
#include "FL/Components/RenderableComp.h"

int FlamingoTest::Init() {

    Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new TestComponent());
    _entityManager->AddComponent(e, new PositionComp(0, 0, 100, 100));
    _entityManager->AddComponent(e, new RenderableComp());


    return 0;
}

int main (int argc, char *arg[]) {

    FlamingoTest flamingo = FlamingoTest();

    return flamingo.Execute();

}

