#ifndef SHADOWMAP_HPP
#define SHADOWMAP_HPP

#include "texture.hpp"


class ShadowMap : public Texture
{
    public:
        ShadowMap();
        GLuint getFramebuffer() {return framebuffer_;}
        bool bind();
    protected:
        const GLuint framebuffer_;
        GLuint createFramebuffer();
};

#endif // SHADOWMAP_HPP
