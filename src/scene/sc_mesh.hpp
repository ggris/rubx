#ifndef SC_MESH_HPP
#define SC_MESH_HPP

#include <vector>
#include <string>

#include "include_gl.hpp"
#include "sc_3d_node.hpp"
#include "texture.hpp"
#include "vao.hpp"

class ScMesh : public Sc3dNode
{
    public:
        ScMesh(Sc3d * scene,
                VAO * vao,
				Texture * texture,
				unsigned int id,
                Sc3dNode * parent = nullptr);

        void display();
		void displayWithPickingColour(glm::vec3 colour);

		unsigned int getId() const;

    private:
        GLuint program_;
		GLuint pickingProgram_;
        VAO * vao_;
        Texture * texture_;

		unsigned int id_;

		void setLamps();
};

#endif
