
#include "FL/Image.h"

#include <OpenGL/glu.h>
#include "IL/il.h"

#include <iostream>

Image::Image() {

    length = 0;
    width = 0;
    height = 0;
    img = 0;
}

Image::Image(std::string filename) {

    if (!LoadImage(filename)) {
        length = 0;
        width = 0;
        height = 0;
        img = 0;
    }
}

bool Image::LoadImage(std::string filename) {
    ILuint i;
    ilGenImages(1, &i);
    ilBindImage(i);
    if (ilLoadImage(filename.c_str()) == IL_FALSE) {
        
        ILenum err = IL_NO_ERROR, temp;

        while (1) {
            temp = ilGetError();
            if (temp == IL_NO_ERROR)
                break;
            err = temp;
        }
        
        std::cout << "Cannot find image: " << filename << "\n";
        return false;
    }
    if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_FALSE) {
        return false;
    }

    length = 1;
    width = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);

    // Need to allocate space for larger numbers of images
    glGenTextures(1, &img);
    glBindTexture(GL_TEXTURE_2D, img);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height,
                      GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

    return true;
}

