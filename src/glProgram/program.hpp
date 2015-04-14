#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>

#define GL_GLEXT_PROTOTYPES
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "shader.hpp"

class Program: public std::vector<Shader>
{
    public:
        Program() : m_program(glCreateProgram()) {}

        GLuint getProgram() const {return m_program;}

        void link() const;

    private:
        const GLuint m_program;

        void linkStatus() const;
};

#endif


