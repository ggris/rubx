#version 410
smooth in vec4 frag_normal;
out vec4 frag_colour;
uniform uvec4 colour;
void main() {
	frag_colour = vec4(colour)/255.0;
	vec4 normal = normalize(frag_normal);
	float w=0.6;
	if (normal.x >=0.9){
		w=0.0;
	}
	if (normal.y >=0.9){
		w=1.0;
	}
	if (normal.z >=0.9){
		w=2.0;
	}
	if (normal.x <=-0.9){
		w=3.0;
	}
	if (normal.y <=-0.9){
		w=4.0;
	}
	if ( normal.z <=-0.9){
		w=5.0;
	}
	frag_colour.w=w/255.0;
	//frag_colour.w=normal.x;
	//frag_colour.w=0.5;
	//frag_colour[3] est la normale (entre 0 et 5)
}
