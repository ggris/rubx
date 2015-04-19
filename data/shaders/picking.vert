#version 410

layout(location = 0) in vec4 position;

uniform vec4 camera_position;
uniform mat4 projection_matrix;

void main()
{
    gl_Position = projection_matrix * position;
}
