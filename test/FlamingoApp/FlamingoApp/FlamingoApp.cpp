//
//  FlamingoApp.cpp
//  FlamingoApp
//
//  Created by Brad. Zeis on 6/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FlamingoApp.h"

int FlamingoApp::Init() {
    
    Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new PositionComp(0, 0, 256, 256));
    _entityManager->AddComponent(e, new SpriteComp("crate.jpg"));
    
    return 0;
    
}
