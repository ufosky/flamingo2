//
//  FlamingoApp.cpp
//  FlamingoApp
//
//  Created by Brad. Zeis on 6/28/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FlamingoApp.h"
#include "physfs.h"

#include <iostream>
#include <string>

int FlamingoApp::Init(int argc, char *argv[]) {
    
    PHYSFS_init(argv[0]);
    PHYSFS_mount("FlamingoApp.app/Contents/Resources/", "/", 1);
    
    Entity *e = _entityManager->CreateEntity();
    _entityManager->AddComponent(e, new PositionComp(0, 0, 256, 256));
    _entityManager->AddComponent(e, new SpriteComp(new Image("crate.jpg")));
    
    return 0;
}
