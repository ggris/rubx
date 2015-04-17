#ifndef SC_3D_NODE_HPP
#define SC_3D_NODE_HPP

#include "scene_graph.hpp"
#include "glm/glm.hpp"

class Sc3dNode : public ScNode
{
    public:
        Sc3dNode();
        Sc3dNode(Sc3dNode * parent);

        void set_parent(Sc3dNode * parent) {parent_ = parent;}
        void clear_parent() {parent_ = nullptr;}

        glm::mat4 getTransformation() const;

    protected:
        Sc3dNode * parent_;
        glm::mat4 transformation_;
};


#endif


