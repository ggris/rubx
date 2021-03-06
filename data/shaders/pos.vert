#version 410

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 UV;

uniform mat4 projection_matrix;
uniform mat4 transformation_matrix;

smooth out vec4 color;
smooth out vec4 fragPosition;
smooth out vec4 fragNormal;
smooth out vec2 fragUV;


void main()
{
    gl_Position = projection_matrix *transformation_matrix* position;
    color = (normal + vec4(1.0f)) / 2.0f;
    fragPosition=transformation_matrix * position;
    fragNormal=transformation_matrix*normal;
    fragUV=UV;
}
