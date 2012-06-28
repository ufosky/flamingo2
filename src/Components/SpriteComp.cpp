
#include "FL/Components/SpriteComp.h"

#include "IL/il.h"
#include <OpenGL/glu.h>

#include <iostream>

SpriteComp::SpriteComp() {
    _SetType();
}

SpriteComp::SpriteComp(std::string file) {

    _SetType();
    _LoadImage(file);
}

SpriteComp::~SpriteComp() {

}

void SpriteComp::_LoadImage(std::string file) {

    ILuint i;
    ilGenImages(1, &i);
    ilBindImage(i);
    if (ilLoadImage(file.c_str()) == IL_FALSE) {
        std::cout << "Cannot find image: " << file << "\n";
        return;
    }
    if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_FALSE) {
        return;
    }

    glGenTextures(1, &img);
    glBindTexture(GL_TEXTURE_2D, img);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
                      GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
}

void SpriteComp::LoadImage(std::string file) {

}

void SpriteComp::Process() {

}

