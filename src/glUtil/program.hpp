#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>

#include "../util/include_gl.hpp"

#include "shader.hpp"

class Program: public std::vector<Shader>
{
    public:
        Program() : m_program(glCreateProgram()) {}

        GLuint getProgram() const {return m_program;}

        void link() const;
        void clearShaders();

    private:
        const GLuint m_program;

        void linkStatus() const;
};

#endif


