#include "shadowmap.hpp"

ShadowMap::ShadowMap():
    Texture(),
    framebuffer_(createFramebuffer())
{

}

GLuint ShadowMap::createFramebuffer()
{
    GLuint framebuffer_name = 0;
    glGenFramebuffers(1, &framebuffer_name);
    return framebuffer_name;
}

bool ShadowMap::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture_, 0);

    glDrawBuffer(GL_NONE); // No color buffer is drawn to.

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        return false;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);

    return true;
}
