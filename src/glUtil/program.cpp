#include "util/logger.hpp"

#include "program.hpp"

Program::Program(GLenum mode, const std::string & name) :
    program_(glCreateProgram()),
    mode_(mode)
{
    if (name == "")
        return;

    switch (mode)
    {
        case GL_PATCHES:
            emplace_back( name + ".cs", GL_TESS_CONTROL_SHADER );
            emplace_back( name + ".es", GL_TESS_EVALUATION_SHADER );
            break;
        case GL_TRIANGLES:
            break;
        default:
            return;
    }
    emplace_back( name + ".vs", GL_VERTEX_SHADER );
    emplace_back( name + ".fs", GL_FRAGMENT_SHADER );

    link();

    clearShaders();
}

void Program::link() const
{
    // Attaching shaders
    for(unsigned int l_i = 0; l_i < size(); l_i++)
        glAttachShader(program_, at(l_i).getShader());

    glLinkProgram(program_);
    linkStatus();

    // Detaching shaders
    for(unsigned int l_i = 0; l_i < size(); l_i++)
        glDetachShader(program_, at(l_i).getShader());
}

void Program::linkStatus() const
{
    GLint status;
    glGetProgramiv (program_, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint info_log_length;
        glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar *str_info_log = new GLchar[info_log_length + 1];
        glGetProgramInfoLog(program_, info_log_length, NULL, str_info_log);

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


