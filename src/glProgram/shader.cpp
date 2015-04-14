#include <fstream>
#include <sstream>
#include <iostream>

#include "util/logger.hpp"

#include "shader.hpp"

Shader::Shader(std::string filename, GLenum shader_type) :
    m_filename(filename),
    m_shader_type(shader_type),
    m_shader(glCreateShader(m_shader_type))
{
    createShader();
}

std::string Shader::getShaderSource() const
{
    std::ifstream source_ifs(m_filename);
    std::stringstream source_ss;
    source_ss << source_ifs.rdbuf();

    return source_ss.str();
}

void Shader::createShader() const
{
const char * shader_source = getShaderSource().c_str();
    glShaderSource(m_shader, 1, &shader_source, 0);
    glCompileShader(m_shader);

    GLint status;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(m_shader, infoLogLength, NULL, strInfoLog);
        const char *strShaderType = NULL;
        switch(m_shader_type)
        {
            case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
            case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
            case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        }
        LOG_ERROR << "Compile failure in " << strShaderType << " shader :\n"
            << strInfoLog;
        delete[] strInfoLog;
    }
}
