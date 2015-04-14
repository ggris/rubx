#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#define GL_GLEXT_PROTOTYPES
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Shader
{
    public:
        Shader(std::string filename, GLenum shader_type);

    private:
        const std::string m_filename;
        const GLenum m_shader_type;
        const GLint m_shader;

        std::string getShaderSource() const;
        void createShader() const;
};

#endif


