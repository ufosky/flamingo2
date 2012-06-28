
#include "FL/Components/SpriteComp.h"

#include "IL/il.h"
#include <OpenGL/glu.h>

#include <iostream>

SpriteComp::SpriteComp() {
    _SetType();
}

SpriteComp::SpriteComp(Image *image) {

    _SetType();
    img = image;
}

SpriteComp::~SpriteComp() {

}

void SpriteComp::LoadImage(std::string file) {

}

void SpriteComp::Process() {

}

