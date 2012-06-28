
#include "FlamingoTest.h"
#include "TestComponent.h"
#include "FL/Components/PositionComp.h"
#include "FL/Components/SpriteComp.h"

int FlamingoTest::Init() {

    Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new TestComponent());
    _entityManager->AddComponent(e, new PositionComp(0, 0, 256, 256));
    _entityManager->AddComponent(e, new SpriteComp("crate.jpg"));                                            

    return 0;
}

int main (int argc, char *arg[]) {

    FlamingoTest flamingo = FlamingoTest();

    return flamingo.Execute();

}

