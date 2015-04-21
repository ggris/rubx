#version 410

layout(location = 0) in vec4 position_vs_in;

uniform mat4 transformation_matrix;
uniform mat4 projection_matrix;

void main(){
    gl_Position = projection_matrix * transformation_matrix * position_vs_in;
}
