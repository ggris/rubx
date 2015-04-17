#version 410
uniform mat4 u_projection;
in vec2 vp; 
out vec2 st; 
void main () { 
	//st = (vp + 1.0) * 0.5; 
	gl_Position = u_projection * vec4(vp.x, vp.y, 1.0, 1.0);
	//gl_Position = vec4 (vp.x, vp.y, 0.0, 1.0);
}
