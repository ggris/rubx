#version 410
in vec2 vp;
out vec2 st;
void main() {
	st = (vp + 1.0) * 0.5;
	gl_Position = vec4 (vp.x, vp.y, 0.0, 1.0);
	gl_Position.xy *= 0.5;
}