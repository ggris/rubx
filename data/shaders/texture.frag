#version 410

smooth in vec2 fragUV;

uniform sampler2D texture_Sampler;

out vec4 color;

void main(){
    color=vec4(texture(texture_Sampler,fragUV).rgb,1.0);
    //color=vec4(fragUV,1.0,1.0);
}
