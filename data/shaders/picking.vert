#version 410

layout(location = 0) in vec4 position;

uniform mat4 projection_matrix;

void main()
{
    gl_Position = projection_matrix * position;
}
