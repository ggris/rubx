#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "../util/include_gl.hpp"

class Texture
{
    public:
        Texture();
        Texture(const std::string &filename);
        GLuint getTexture() const {return texture_;}
        void bindToSampler(GLuint textureSampler);
        static void bindTextureToSampler(GLuint texture,GLuint textureSampler,GLuint textureUnitIndex=0);
        static void bindTexturesToSamplers(GLsizei numTextures, GLuint * textures, GLuint * textureSamplers,GLuint first=0);
        static void resetTextureUnitIndex(){TEXTURE_UNIT_INDEX=0;}

    protected:
        const std::string filename_;
        const GLuint texture_;
		GLuint createTexture();

	private:
        static GLuint TEXTURE_UNIT_INDEX;
		void loadTexture();

};

#endif // TEXTURE_H
