#include <fstream>
#include <sstream>
#include <iostream>
#include <cassert>

#include "util/logger.hpp"

#include "shader.hpp"

#ifndef SHADERS_DIRECTORY
#define SHADERS_DIRECTORY "data/shaders/"
#endif

Shader::Shader(const std::string &filename, GLenum shader_type) :
    m_filename(SHADERS_DIRECTORY + filename),
    m_shader_type(shader_type),
    m_shader(glCreateShader(m_shader_type))
{
    createShader();
}

void Shader::sourceShader() const
{
    std::ifstream source_ifs(m_filename, std::ifstream::in);

    assert (source_ifs.is_open());

    std::stringstream source_ss;
    source_ss << source_ifs.rdbuf();

    std::string source_s = source_ss.str();
    const char * shader_source = source_s.c_str();

    glShaderSource(m_shader, 1, &shader_source, 0);
}

void Shader::compileStatus() const {
    GLint status;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(m_shader, infoLogLength, NULL, strInfoLog);

        LOG_ERROR << "Compile failure in " << m_filename << " shader :\n" << strInfoLog;

        delete[] strInfoLog;
    }
}

void Shader::createShader() const
{
    LOG_TRACE << "Shader : " << m_filename;

    sourceShader();
    glCompileShader(m_shader);

    compileStatus();

}
