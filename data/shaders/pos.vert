#version 410

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 UV;

uniform vec4 camera_position;
uniform mat4 projection_matrix;

smooth out vec4 color;
smooth out vec4 fragPosition;
smooth out vec4 fragNormal;
smooth out vec2 fragUV;


void main()
{
    float s = 0.2f;
    vec4 base_position = position * vec4(s, s, s, 1.0f) + camera_position;
    gl_Position = projection_matrix * base_position;
    color = (normal + vec4(1.0f)) / 2.0f;
    fragPosition=position;
    fragNormal=normal;
    fragUV=UV;
}
