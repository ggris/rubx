#ifndef SC_MESH_HPP
#define SC_MESH_HPP

#include <vector>
#include <string>

#include "include_gl.hpp"
#include "sc_3d_node.hpp"
#include "texture.hpp"

class ScMesh : public Sc3dNode
{
    public:
        ScMesh(Sc3dNode * parent,
                const std::vector<float> &points,
                const std::vector<float> &normals,
                const std::vector<float> &tex_coord,
                const std::vector<unsigned short> &index,
				unsigned int id,
				std::string filename="data/img/corners.bmp");

        void display();
		void displayWithPickingColour(glm::vec3 colour);

		unsigned int getId() const;

    private:
        GLuint program_;
		GLuint pickingProgram_;
        GLuint vao_;
        GLuint texture_;

		unsigned int id_;

		void setLamps();
};

#endif
