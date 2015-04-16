#ifndef UI_HPP
#define UI_HPP

#include <vector>

class UI;

#include "util/include_gl.hpp"

class UI
{
    public:
		UI();
        void display();
    private:
        GLuint m_program;
        GLuint m_vao;
};

#endif
