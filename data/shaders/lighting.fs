#version 410
#define MAX_NB_LAMPS 20 //Absolute max number of lights

smooth in vec3 position_fs_in;
smooth in vec3 normal_fs_in;
smooth in vec2 uv_fs_in;

uniform sampler2D texture_Sampler;
uniform sampler2D normalmap_Sampler;
uniform int numLamps; //actual number of lights used
struct Lamp{
    mat4 transformation;
    mat4 view_matrix;
    vec4 color;
};
uniform Lamp allLamps[MAX_NB_LAMPS];
uniform sampler2D shadowmaps[MAX_NB_LAMPS];

out vec4 fragColor;

const float M_PI = 3.1415;

float D_GGX(vec4 wh, vec4 n, float alpha){
    return alpha*alpha/(M_PI*pow((1.0+(alpha*alpha-1.0)*pow(dot(n,wh),2.0)),2.0));
}

float G1(vec4 w, vec4 n, float alpha){
    float res = 2.0*dot(n,w);
    res/=dot(n,w)+sqrt(alpha*alpha+(1.0-alpha*alpha)*dot(n,w)*dot(n,w));
    return res;
}

float G_GGX( vec4 wi,  vec4 wo, vec4  wh,  vec4  n,float alpha){
    return G1(wi,n,alpha)*G1(wo,n,alpha);
}

float Fresnel( vec4  wi,  vec4  wh,float alpha){
    float F0 = .03;
    float max=dot(wi,wh)>0.0?dot(wi,wh):0.0;
    return F0+(1.0-F0)*pow((1.0-max),5.0);
}

float GGX(vec4 n, vec4 l, vec4 v ,float alpha){

    vec4 h = normalize(l+v);

    float res=D_GGX(h,n,alpha)*Fresnel(l,h,alpha)*G_GGX(l,v,h,n,alpha);
    res/=4.0*dot(n,l)*dot(n,v);
    if (res*dot(n,l)>0)return 5.0*res*dot(n,l);
    return 0.0;
}

vec4 applyLamp(int i, vec4 diffuseColor, vec4 normal, vec4 position, vec4 toCamera){
    Lamp lamp = allLamps[i];
    vec4 toLamp = lamp.transformation[3]-position;
    vec4 shadow_coord = lamp.view_matrix*vec4(position_fs_in,1.0);
    float visibility=1.0;
    if ( texture( shadowmaps[i], shadow_coord.xy ).z  <  shadow_coord.z){
        visibility=1.0;
    }
    float attenuation=visibility;
    float dist= length(toLamp);
    toLamp = normalize(toLamp);
    attenuation /=(1.0+0.001*pow(dist,2));

    float alpha = 0.15;

    return attenuation*(GGX(normal,toLamp,toCamera,alpha)*lamp.color+0.7*dot(normal,toLamp)*diffuseColor);
}

void main()
{
	vec4 totalColor=vec4(0.0,0.0,0.0,0.0);
	vec4 diffuseColor = vec4(texture(texture_Sampler, uv_fs_in).rgb,1.0);
    vec4 camera = normalize(vec4(-position_fs_in, 0.0));
    vec4 normal = normalize(vec4(normal_fs_in, 0.0));
    vec4 n = vec4(texture(normalmap_Sampler, uv_fs_in).rgb,0.0);

    normal = normalize(normal + 0.2 *n);
    for(int i=0;i<numLamps;i++){ //loop over all lights
        totalColor+= applyLamp(i, diffuseColor, normal, vec4(position_fs_in, 1.0), camera);
    }
    fragColor = totalColor;
}
