#include "util/logger.hpp"

#include "program.hpp"

void Program::link() const
{
    // Attaching shaders
    for(unsigned int l_i = 0; l_i < size(); l_i++)
        glAttachShader(m_program, at(l_i).getShader());

    glLinkProgram(m_program);
    linkStatus();

    // Detaching shaders
    for(unsigned int l_i = 0; l_i < size(); l_i++)
        glDetachShader(m_program, at(l_i).getShader());
}

void Program::linkStatus() const
{
    GLint status;
    glGetProgramiv (m_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint info_log_length;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar *str_info_log = new GLchar[info_log_length + 1];
        glGetProgramInfoLog(m_program, info_log_length, NULL, str_info_log);

        LOG_ERROR << "Linker failure :\n" << str_info_log;

        delete[] str_info_log;
    }

}

void Program::clearShaders()
{
    for(unsigned int l_i = 0; l_i < size(); l_i++)
        glDeleteShader(at(l_i).getShader());

    clear();
}


