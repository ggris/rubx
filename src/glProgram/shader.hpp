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
        GLint getShader() {return m_shader;}

    private:
        const std::string m_filename;
        const GLenum m_shader_type;
        const GLint m_shader;

        void sourceShader() const;
        void createShader() const;
};

#endif


