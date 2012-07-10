
#include "FlamingoTest.h"
#include "TestComponent.h"
#include "FL/Components/PositionComp.h"
#include "FL/Components/SpriteComp.h"

#include "physfs.h"

int FlamingoTest::Init(int argc, char *argv[]) {
    
    Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new TestComponent());
    _entityManager->AddComponent(e, new PositionComp(0, 0, 256, 256));
    SpriteComp *spr = new SpriteComp(new Image("crate.jpg"));
    _entityManager->AddComponent(e, spr);
    
    return 0;
}

int main (int argc, char *argv[]) {

    FlamingoTest flamingo = FlamingoTest();

    return flamingo.Execute(argc, argv);

}

