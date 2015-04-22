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
                const std::string & vao_name,
				const std::string & program_name,
                const std::string & texture_name,
                Sc3dNode * parent = nullptr);

        void display();
		void displayWithPickingColour(glm::vec3 colour);

		unsigned int getId() const;

    private:
        VAO * vao_;
        Program * program_;
        Texture * texture_;

        Program * pickingProgram_;
		unsigned int id_;

		void setLamps();
};

#endif
