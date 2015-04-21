#version 410
out vec4 frag_colour;
uniform vec4 colour;
in vec4 frag_normal;
void main() {
	frag_colour = colour;
	if (frag_normal==vec4(1.0,0.0,0.0,0.0)){
		frag_colour[3]=0;
	}
	if (frag_normal==vec4(0.0,1.0,0.0,0.0)){
		frag_colour[3]=1;
	}
	if (frag_normal==vec4(0.0,0.0,1.0,0.0)){
		frag_colour[3]=2;
	}
	if (frag_normal==vec4(-1.0,0.0,0.0,0.0)){
		frag_colour[3]=3;
	}
	if (frag_normal==vec4(0.0,-1.0,0.0,0.0)){
		frag_colour[3]=4;
	}
	if (frag_normal==vec4(0.0,0.0,-1.0,0.0)){
		frag_colour[3]=5;
	}
	//frag_colour[3] est la normale (entre 0 et 5)
}
