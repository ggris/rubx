#include "texture.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

Texture::Texture():
    filename_(""),
    texture_(createTexture())
{
}

Texture::Texture(const string &filename):
    filename_(filename),
    texture_(createTexture())
{
    loadTexture();
}

GLuint Texture::createTexture()
{
    GLuint res;

    glGenTextures(1, &res);
    return res;
}

void Texture::loadTexture()
{
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char * data;

    FILE * file = fopen(filename_.c_str(),"rb");
    if(!file){
        cout<<"ERROR : Texture::loadTexture() : could not open file"<<endl;
        return;
    }
    if(fread(header, 1, 54, file)!=54 ){ //reading header
        cout<<"ERROR : Texture::loadTexture() : incorrect file format"<<endl;
        return;
    }
    if(header[0]!='B' || header[1]!='M'){ //check first two bytes
        cout<<"ERROR : Texture::loadTexture() : incorrect file format"<<endl;
        return;
    }

    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    width      = *(int*)&(header[0x12]);
    height     = *(int*)&(header[0x16]);
    //complete missing info
    imageSize=(imageSize==0)?width*height*3:imageSize;
    dataPos=(dataPos==0)?54:dataPos;

    data = new unsigned char [imageSize];
    fread(data,1,imageSize,file);
    fclose(file);

    //binding texture in openGL

    glBindTexture(GL_TEXTURE_2D, texture_);

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}
///Binding the texture and textureSampler to texture unit textureUnitIndex (default value : 0)
void Texture::bindToSampler(GLuint textureSampler,GLuint textureUnitIndex)
{
    glActiveTexture(GL_TEXTURE0+textureUnitIndex);
    glBindTexture(GL_TEXTURE_2D,texture_);
    glUniform1i(textureSampler,textureUnitIndex);
}

///static version of bindToSampler
void Texture::bindTextureToSampler(GLuint texture, GLuint textureSampler, GLuint textureUnitIndex)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);
    glUniform1i(textureSampler,0);
}

///Binding several textures at once, starting from texture unit first (default value : 0)
void Texture::bindTexturesToSamplers(GLsizei numTextures, GLuint* textures, GLuint* textureSamplers,GLuint first)
{
    glBindTextures(first, numTextures,textures);
    for(int i=0;i<numTextures;i++){
        glUniform1i(textureSamplers[i],first+i);
    }
}
