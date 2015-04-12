#ifndef MESH_CUBE_HPP
#define MESH_CUBE_HPP

#include <vector>

class MeshCube;

#include "context.hpp"

class MeshCube
{
    public:
        MeshCube();
        void display(float time);
    private:
        GLuint m_program;
        GLuint m_vao;

        GLuint createShader(GLenum eShaderType, const char *shader_source);
        GLuint CreateProgram(const std::vector<GLuint> &shaderList);
};

#endif