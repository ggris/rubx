#ifndef SC_3D_NODE_HPP
#define SC_3D_NODE_HPP

#include "scene_graph.hpp"
#include "glm/glm.hpp"

class Sc3d;

class Sc3dNode : public ScNode
{
    public:
        enum RenderLayer {ALL, LIGHTING, ZBUFFER, SELECT};
        Sc3dNode();
        Sc3dNode(Sc3dNode * parent);
        Sc3dNode(Sc3dNode * parent, Sc3d* scene);

        void set_parent(Sc3dNode * parent) {parent_ = parent;}
        void setScene(Sc3d * scene){scene_=scene;}
        void clear_parent() {parent_ = nullptr;}
        Sc3d * getScene(){return scene_;}

        void multTransformation( const glm::mat4 & transformation );
        void clearTransformation();

        void nodRotate( glm::vec2 pos );
        void nodRotateZ(float rz);
        void nodRotateX(float rx);
        glm::mat4 getTransformation() const;

        void display();

    protected:
        Sc3dNode * parent_;
        Sc3d * scene_;
        glm::mat4 pre_transformation_;
        glm::mat4 transformation_;
        glm::vec2 speed_;
};


#endif


