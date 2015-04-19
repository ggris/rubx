#version 410

smooth in vec2 fragUV;

uniform sampler2D texture_Sampler;

out vec4 fragColor;

void main(){
    fragColor=vec4(texture(texture_Sampler,fragUV).rgb,1.0);
}
