#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "../util/include_gl.hpp"

class Texture
{
    public:
        Texture(const std::string &filename);
        GLuint getTexture() const {return texture_;}
        void bindToSampler(GLuint textureSampler, GLuint textureUnitIndex=0);
        static void bindTextureToSampler(GLuint texture,GLuint textureSampler,GLuint textureUnitIndex=0);
        static void bindTexturesToSamplers(GLsizei numTextures, GLuint * textures, GLuint * textureSamplers,GLuint first=0);

    private:
        const std::string filename_;
        const GLuint texture_;
		GLuint createTexture();
		void loadTexture();

};

#endif // TEXTURE_H
