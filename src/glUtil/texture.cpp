#include "texture.hpp"
#include <stdio.h>

using namespace std;

Texture::Texture(const string &filename):
    filename_(filename),
    texture_(createTexture()
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

    FILE * file = fopen(filename_,"rb");
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


    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}
