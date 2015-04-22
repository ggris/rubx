#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

class ScNode
{
    public:
        enum DisplayMode {RENDER_IMAGE, SHADOWMAP, PICKING};
        virtual void display() = 0;
};

class ScVector : public std::vector<ScNode*>, public ScNode
{
    public:
        void display();
};

#endif

