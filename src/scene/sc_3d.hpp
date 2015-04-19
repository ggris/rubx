#ifndef SC_3D_HPP
#define SC_3D_HPP

#include "include_gl.hpp"
#include "glm/glm.hpp"

#include "scene_graph.hpp"
#include <vector>

//#include "camera.hpp"

class Camera;
class Lamp;

class Sc3d : public ScVector
{
    public:
        Sc3d(GLFWwindow * window);
        void display();

		Camera getCamera();
		std::vector <Lamp *> getLamps();
		void addLamp(Lamp * lamp);
		void addLamp(glm::vec4 light);
		void addLamp(glm::vec4 light, glm::vec4 color);

    private:
        GLFWwindow * window_;
        Camera * camera_;
        std::vector<Lamp *> lamps_;
};

#endif //SC3D_HPP
