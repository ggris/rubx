#version 410
smooth in vec4 color;
smooth in vec4 fragPosition;
smooth in vec4 fragNormal;

uniform vec4 camera_position;
//uniform mat4 projection_matrix;

out vec4 fragColor;


const float M_PI=3.14;
const vec4 lightPos = vec4 (10.0, 5.0, 7.0,1.0);
const vec4 matAlbedo = vec4 (0.6, 0.6, 0.6,1.0);


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
  
  vec4 h = normalize(l+v);
  
  float res=D_GGX(h,n,alpha)*Fresnel(l,h,alpha)*G_GGX(l,v,h,n,alpha);
  res/=4.0*dot(n,l)*dot(n,v);
  return 10.0*res*dot(n,l);
}

void main()
{	
	vec4 normal = normalize (fragNormal);
    	vec4 light = normalize (lightPos-fragPosition);
    	vec4 camera = normalize (camera_position);

	fragColor = GGX(normal,light,camera,0.5)*color;
//
}
