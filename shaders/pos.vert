#version 410

layout(location = 0) in vec4 position;

uniform vec4 camera_position;
uniform mat4 projection_matrix;

smooth out vec4 color;

void main()
{
    float s = 0.2f;
    vec4 base_position = position * vec4(s, s, s, 1.0f) + camera_position;
    gl_Position = projection_matrix * base_position;
    color = position;
}
