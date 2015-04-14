#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#define GL_GLEXT_PROTOTYPES
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Shader
{
    public:
        Shader(const std::string &filename, GLenum shader_type);
        GLuint getShader() const {return m_shader;}

    private:
        const std::string m_filename;
        const GLenum m_shader_type;
        const GLuint m_shader;

        void sourceShader() const;
        void compileStatus() const;
        void createShader() const;
};

#endif


