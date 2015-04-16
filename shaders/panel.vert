#version 410
in vec2 vp;
out vec2 st;
void main() {
	gl_Position = vec4 (vp.x, vp.y, 0.0, 1.0);
}