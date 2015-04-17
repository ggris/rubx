#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

class ScNode
{
    public:
        virtual void display() = 0;
};

class ScVector : public std::vector<ScNode*>, ScNode
{
    public:
        void display();
};
/*
class Scene
{
    public:
        Scene();

    private:
        Context context_;
        Camera camera_;
        MeshCube mesh_cube_;
};
*/

#endif

