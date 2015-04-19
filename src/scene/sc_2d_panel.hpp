#ifndef SC_2D_PANEL_HPP
#define SC_2D_PANEL_HPP

#include <string>
#include "glm/glm.hpp"
#include "include_gl.hpp"
#include "scene_graph.hpp"

class Sc2dPanel : ScNode
{
    public:
		Sc2dPanel();
		Sc2dPanel(glm::vec2 position, glm::vec2 scale, std::string textureFile, std::vector<float> tex_coord);

		void update(std::vector<float> points, std::vector<float> tex_coord);
		std::vector<float> getPoints() const;
		std::vector<float> getTexCoords() const;

        void display();
    private:
		glm::vec2 position_;
		glm::vec2 scale_;

		GLuint program_;
		GLuint vao_;
		GLuint vbo_;
		GLuint tex_vbo_;
		GLuint texture_;

		std::vector<float> points_;
		std::vector<float> tex_coords_;
};

#endif
