#version 410

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
uniform mat4 projection_matrix;
uniform mat4 transformation_matrix;
out vec4 frag_normal;
void main()
{
    gl_Position = projection_matrix *transformation_matrix* position;
    frag_normal=normal;
}
