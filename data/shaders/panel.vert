#version 410  
uniform vec2 panel_scale; 
uniform vec2 panel_position; 

layout(location = 0) in vec2 vp;
layout(location = 1) in vec2 UV;

smooth out vec2 fragUV;

void main () 
{ 
	vec2 position = panel_position + vp;
	gl_Position = vec4 (position * panel_scale, 0.0, 1.0);
	
	fragUV=UV;	
}

