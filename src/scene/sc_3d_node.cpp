#include "logger.hpp"
#include "sc_3d_node.hpp"

Sc3dNode::Sc3dNode() :
    parent_(nullptr),
    transformation_(1.0f)
{
}

Sc3dNode::Sc3dNode(Sc3dNode * parent) :
    parent_(parent),
    transformation_(1.0f)
{
}

glm::mat4 Sc3dNode::getTransformation() const
{
    if (parent_ == nullptr)
        return transformation_;

    return parent_->getTransformation() * transformation_;
}



