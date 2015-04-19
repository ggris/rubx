#ifndef SC_2D_PANEL_HPP
#define SC_2D_PANEL_HPP

#include "sc_3d_node.hpp"
#include <string>

class Sc2dPanel : ScNode
{
    public:
		Sc2dPanel();
		Sc2dPanel(glm::vec2 position, glm::vec2 scale, std::string textureFile, std::vector<float> tex_coord);
        void display();
    private:
		glm::vec2 position_;
		glm::vec2 scale_;

		GLuint program_;
		GLuint vao_;
		GLuint texture_;
};

#endif
