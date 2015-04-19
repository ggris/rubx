#include "logger.hpp"
#include "sc_3d_node.hpp"
#include "sc_3d.hpp"

Sc3dNode::Sc3dNode() :
    parent_(nullptr),
    scene_(nullptr),
    transformation_(1.0f)
{
}

Sc3dNode::Sc3dNode(Sc3dNode * parent) :
    parent_(parent),
    scene_(parent->scene_),
    transformation_(1.0f)
{
}

Sc3dNode::Sc3dNode(Sc3dNode * parent, Sc3d* scene) :
    parent_(parent),
    scene_(scene),
    transformation_(1.0f)
{
}

glm::mat4 Sc3dNode::getTransformation() const
{
    if (parent_ == nullptr)
        return transformation_;

    return parent_->getTransformation() * transformation_;
}



