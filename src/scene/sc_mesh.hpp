#ifndef SC_MESH_HPP
#define SC_MESH_HPP

#include <vector>
#include <string>

#include "include_gl.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include "sc_3d_node.hpp"

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
        Program * program_;
		Program * pickingProgram_;
        VAO * vao_;
        Texture * texture_;

		unsigned int id_;

		void setLamps();
};

#endif
