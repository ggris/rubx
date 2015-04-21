#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include <string>

#include "../util/include_gl.hpp"

#include "shader.hpp"

class Program: public std::vector<Shader>
{
    public:
        Program(GLenum mode = GL_TRIANGLES, const std::string & name = "");

        GLuint get_program() const {return program_;}

        void link() const;
        void clearShaders();

        void use() const {glUseProgram(program_);}
        GLuint get_mode() const {return mode_;}
        GLuint getUniformLocation(const std::string & name) const {return glGetUniformLocation( program_, name.c_str() );}

    private:
        const GLuint program_;
        const GLenum mode_;

        void linkStatus() const;
};

#endif


