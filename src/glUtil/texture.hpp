#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "util/include_gl.hpp"

class Texture
{
    public:
        Texture(const std::string &filename);
        GLuint getTexture() const {return texture_;}

    private:
        const std::string filename_;
        const GLuint texture_;
};

#endif // TEXTURE_H
