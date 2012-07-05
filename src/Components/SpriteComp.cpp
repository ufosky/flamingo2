
#include "FL/Components/SpriteComp.h"

#include "IL/il.h"
#include <OpenGL/glu.h>

#include <iostream>

SpriteComp::SpriteComp() : Component(FL_COMPTYPE_SPRITE) {

}

SpriteComp::SpriteComp(Image *image) : Component(FL_COMPTYPE_SPRITE) {
    img = image;
}

SpriteComp::~SpriteComp() {

}

void SpriteComp::LoadImage(std::string file) {

}

