#version 410

layout(location = 0) in vec4 position_vs_in;
layout(location = 1) in vec4 normal_vs_in;
layout(location = 2) in vec2 uv_vs_in;

uniform mat4 transformation_matrix;

out vec3 position_cs_in;
out vec3 normal_cs_in;
out vec2 uv_cs_in;

void main()
{
    position_cs_in = ( transformation_matrix * position_vs_in).xyz;
    normal_cs_in = ( transformation_matrix * normal_vs_in ).xyz;
    uv_cs_in = uv_vs_in;
}
