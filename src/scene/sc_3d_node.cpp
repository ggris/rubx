
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "logger.hpp"
#include "sc_3d_node.hpp"
#include "sc_3d.hpp"

Sc3dNode::Sc3dNode() :
    parent_(nullptr),
    scene_(nullptr),
    pre_transformation_(1.0f),
    transformation_(1.0f)
{
}

Sc3dNode::Sc3dNode(Sc3dNode * parent) :
    parent_(parent),
    scene_(parent->scene_),
    pre_transformation_(1.0f),
    transformation_(1.0f)
{
}

Sc3dNode::Sc3dNode(Sc3dNode * parent, Sc3d* scene) :
    parent_(parent),
    scene_(scene),
    pre_transformation_(1.0f),
    transformation_(1.0f)
{
}

glm::mat4 Sc3dNode::getTransformation() const
{
    if (parent_ == nullptr)
        return transformation_ * pre_transformation_;

    return parent_->getTransformation() * transformation_ * pre_transformation_;
}

void Sc3dNode::nodRotate( glm::vec2 pos)
{
    float r = 3.0f;
    speed_ += r * pos ;
    speed_ /= r + 1.0f;
}

void Sc3dNode::display()
{
    speed_ *= 0.8f;
    nodRotateZ(speed_.x);
    nodRotateX(-speed_.y);
}

float mapMouseToRot(float r)
{
    return r * (float) sqrt(fabs( r )) * 0.002f;
}

void Sc3dNode::nodRotateZ(float rz)
{
    pre_transformation_ = glm::rotate( mapMouseToRot(rz), glm::vec3( 0.0f, 1.0f, 0.0f ) ) * pre_transformation_;
}

void Sc3dNode::nodRotateX(float rx)
{
    pre_transformation_ = glm::rotate( mapMouseToRot(rx), glm::vec3( 1.0f, 0.0f, 0.0f ) ) * pre_transformation_;
}

