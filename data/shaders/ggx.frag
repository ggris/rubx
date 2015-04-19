#version 410
#define MAX_NB_LAMPS 20 //Absolute max number of lights

smooth in vec4 fragPosition;
smooth in vec4 fragNormal;
smooth in vec2 fragUV;

uniform vec4 camera_position;
uniform sampler2D texture_Sampler;
uniform int numLamps; //actual number of lights used
struct Lamp{
    vec4 light;
    vec4 color;
};
uniform Lamp allLamps[MAX_NB_LAMPS];

out vec4 fragColor;

const float M_PI = 3.1415;
//const vec4 lightPos1 = vec4 (10.0, 5.0, 7.0,1.0);
//const vec4 lightPos2 = vec4 (10.0, 1.0, 0.0,1.0);




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
    float F0 = .4;
    float max=dot(wi,wh)>0.0?dot(wi,wh):0.0;
    return F0+(1.0-F0)*pow((1.0-max),5.0);
}

float GGX(vec4 n, vec4 l, vec4 v ,float alpha){

    //if(dot(n,l)*dot(n,v)==0) return 0.0;

    vec4 h = normalize(l+v);

    float res=D_GGX(h,n,alpha)*Fresnel(l,h,alpha)*G_GGX(l,v,h,n,alpha);
    res/=4.0*dot(n,l)*dot(n,v);
    if (res*dot(n,l)>0)return res*dot(n,l);
    return 0.0;
}

vec4 applyLamp(Lamp lamp, vec4 surfaceColor, vec4 normal, vec4 position, vec4 toCamera){
    vec4 toLamp;
    float attenuation=1.0;
    if(lamp.light.w==0.0){ //directional light
        toLamp=normalize(lamp.light);
    }
    else { //punctual light
        toLamp = normalize(lamp.light-position);
        float dist= length(lamp.light-position);
        attenuation = 1.0/(1.0+0.01*pow(dist,2)); //quadratic attenuation
    }
    //if (GGX(normal,toLamp,toCamera,0.7)<0.0) return vec4(1.0,1.0,0.0,1.0);
    return GGX(normal,toLamp,toCamera,0.8)*surfaceColor*lamp.color;

    //return vec4(1.0,1.0,0.0,1.0);
}

void main()
{
	vec4 totalColor=vec4(0.0,0.0,0.0,0.0);
	vec4 color = vec4(texture(texture_Sampler,fragUV).rgb,1.0);
    //vec4 light1 = normalize (lightPos1-fragPosition);
    //vec4 light2 = normalize (lightPos2-fragPosition);
    vec4 camera = normalize(camera_position-fragPosition);

    for(int i=0;i<numLamps;i++){ //loop over all lights
        totalColor+= applyLamp(allLamps[i],color,fragNormal,fragPosition,camera);
    }
    fragColor = totalColor;
    //fragColor = allLamps[0].light;

	//fragColor = (GGX(fragNormal,light1,camera,0.8)+GGX(fragNormal,light2,camera,0.8))*vec4(texture(texture_Sampler,fragUV).rgb,1.0);
}
