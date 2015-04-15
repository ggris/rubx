// ----------------------------------------------
// Informatique Graphique 3D & Réalité Virtuelle.
// Travaux Pratiques
// Shaders
// Copyright (C) 2015 Tamy Boubekeur
// All rights reserved.
// ----------------------------------------------

// Add here all the value you need to describe the light or the material. 
// At first used const values. 
// Then, use uniform variables and set them from the CPU program.

const vec3 lightPos = vec3 (5.0, 5.0, 5.0);
const vec3 matAlbedo = vec3 (0.6, 0.6, 0.6);

varying vec4 P; // fragment-wise position
varying vec3 N; // fragment-wise normal

uniform float ALPHA;

float M_PI=3.14;

float brdf( vec3 n,vec3 l,vec3 v){
   return pow(dot(v,n),50.0)*dot(n,l)+dot(n,l);
}

float D_GGX(vec3 wh, vec3 n, float alpha){
  return alpha*alpha/(M_PI*pow((1.0+(alpha*alpha-1.0)*pow(dot(n,wh),2.0)),2.0));
}

float G1(vec3 w, vec3 n, float alpha){
  float res = 2.0*dot(n,w);
  res/=dot(n,w)+sqrt(alpha*alpha+(1.0-alpha*alpha)*dot(n,w)*dot(n,w));
  return res;
}

float G_GGX( vec3 wi,  vec3 wo, vec3  wh,  vec3  n,float alpha){
  return G1(wi,n,alpha)*G1(wo,n,alpha);
}

float Fresnel( vec3  wi,  vec3  wh,float alpha){
  float F0 = .4;
  float max=dot(wi,wh)>0.0?dot(wi,wh):0.0;
  return F0+(1.0-F0)*pow((1.0-max),5.0);
}

float GGX(vec3 n, vec3 l, vec3 v ,float alpha){
  
  vec3 h = normalize(l+v);
  
  float res=D_GGX(h,n,alpha)*Fresnel(l,h,alpha)*G_GGX(l,v,h,n,alpha);
  res/=4.0*dot(n,l)*dot(n,v);
  return 10.0*res*dot(n,l);
}

void main (void) {
    gl_FragColor = vec4 (0.0, 0.0, 0.0, 1.0);
    
    vec3 p = vec3 (gl_ModelViewMatrix * P);
    vec3 n = normalize (gl_NormalMatrix * N);
    vec3 l = normalize (lightPos - p);
    vec3 v = normalize (-p);
    

    // ---------- Code to change -------------
//     float spec=GGX(n,l,v,ALPHA);
//     vec4 color;
//     if(dot(v,n)<.3*length(v)){color = vec4(0.0,0.0,0.0,1.0);} //bords
//     else if (spec>.5){ color = vec4(1.0,1.0,1.0,1.0);} //tache speculaire
//     else{color=vec4(1.0,.5,.3,1.0);}
    
    
    vec4 color = vec4 (GGX(n,l,v,ALPHA)*matAlbedo, 1.0);
    // ----------------------------------------
    
    gl_FragColor += color;
}
 
