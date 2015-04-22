#ifndef SC_3D_HPP
#define SC_3D_HPP

#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"
#include "include_gl.hpp"
#include "texture.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "vao.hpp"

#include "scene_graph.hpp"
#include "texture.hpp"

class RubixCube;
class Camera;
class Lamp;

class Sc3d : public ScVector
{
    public:
        Sc3d(GLFWwindow * window);
        void display();

		Camera * getCamera();
		std::vector <Lamp *> getLamps();
		Texture * getTexture( std::string name ) const;
        Program * getProgram( std::string name ) const;
        VAO * getVAO( std::string name) const;
        unsigned int getNextId() { return next_id_++; }

        RubixCube * get_rubix_cube() {return rubix_cube_;}

    private:
        GLFWwindow * window_;
        Camera * camera_;
        std::vector<Lamp *> lamps_;
        std::unordered_map<std::string, Texture *> textures_;
        std::unordered_map<std::string, Program *> programs_;
        std::unordered_map<std::string, VAO *> vaos_;
        RubixCube * rubix_cube_;
        unsigned int next_id_;

        void addTexture(std::string name);
        void addProgram(std::string name, GLenum mode = GL_TRIANGLES);
        void addVAO(std::string name);
		void addLamp(Lamp * lamp);
		void addLamp();
		void addLamp(glm::vec3 position,float rot_y,float rot_loc_x,glm::vec4 color);
        void initTextures();
        void initPrograms();
        void initVAOs();
        void initLamps();
};

#endif //SC3D_HPP
