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
		void addLamp(Lamp * lamp);
		void addLamp();
		void addLamp(glm::vec3 position,float rot_y,float rot_loc_x,glm::vec4 color);
		Texture * getTexture(std::string objectID);
        RubixCube * get_rubix_cube() {return rubix_cube_;}

    private:
        GLFWwindow * window_;
        Camera * camera_;
        std::vector<Lamp *> lamps_;
        std::unordered_map<std::string, Texture *> textures_;
        std::unordered_map<std::string, Program *> programs_;
        std::unordered_map<std::string, VAO *> vaos_;
        RubixCube * rubix_cube_;

        void initTextures();
        void initPrograms();
        void initVAOs();
};

#endif //SC3D_HPP
