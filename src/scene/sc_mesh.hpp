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
                const std::string & vao_name = "default",
				const std::string & program_name = "default",
                const std::string & texture_name = "default",
                const std::string & normal_map_name = "default",
                const std::string & bump_map_name = "default",
                Sc3dNode * parent = nullptr);

        void display();
        void display(DisplayMode display_mode);

		unsigned int getId() const;

		void setPickingDisplay(bool color_picking_mode);

    private:
        VAO * vao_;
        Program * program_;
        Program * shadowmap_program_;
        Texture * texture_;

        Texture * normal_map_;
        Texture * bump_map_;
        Program * pickingProgram_;
		unsigned int id_;

		bool color_picking_mode_ = false;

		void setLamps();
};

#endif
