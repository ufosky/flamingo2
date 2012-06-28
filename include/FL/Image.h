
#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>

#include <OpenGL/gl.h>

class Image {

    public:
        Image();
        Image(std::string filename);

        GLuint img;
        int length, width, height;

        bool LoadImage(std::string filename);
};

#endif

