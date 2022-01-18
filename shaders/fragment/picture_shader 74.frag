#version 130
// Fork of "[SH17A] christmas baubles" by lovelyH. https://shadertoy.com/view/4sjBW1
// Fork of "Merry Christmas!" by PauloFalcao. https://shadertoy.com/view/4dlGRn
// Happy XMas from Lynxx

//Util Start

uniform sampler2D texture_movie;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

float aTime;
float PI=3.14159265;

vec2 ObjUnion(vec2 obj0,vec2 obj1){
  if (obj0.x<obj1.x)
    return obj0;
  else
    return obj1;
}

vec3 sim(vec3 p,float s){
   vec3 ret=p;
   ret=p+s/2.0;
   ret=fract(ret/s)*s-s/2.0;
   return ret;
}

vec2 rot(vec2 p,float r){
   vec2 ret;
   ret.x=p.x*cos(r)-p.y*sin(r);
   ret.y=p.x*sin(r)+p.y*cos(r);
   return ret;
}

vec2 rotsim(vec2 p,float s){
   vec2 ret=p;
   ret=rot(p,-PI/(s*2.0));
   ret=rot(p,floor(atan(ret.x,ret.y)/PI*s)*(PI/s));
   return ret;
}

float rnd(vec2 v){
  return sin((sin(((v.y-1453.0)/(v.x+1229.0))*23232.124))*16283.223)*0.5+0.5; 
}

float noise(vec2 v){
  vec2 v1=floor(v);
  vec2 v2=smoothstep(0.0,1.0,fract(v));
  float n00=rnd(v1);
  float n01=rnd(v1+vec2(0,1));
  float n10=rnd(v1+vec2(1,0));
  float n11=rnd(v1+vec2(1,1));
  return mix(mix(n00,n01,v2.y),mix(n10,n11,v2.y),v2.x);
}

//Util End
 
//Scene Start

//Snow
float makeshowflake(vec3 p){
  return length(p)-0.03;
}

float makeShow(vec3 p,float tx,float ty,float tz){
  p.y=p.y+aTime*tx;
  p.x=p.x+aTime*ty;
  p.z=p.z+aTime*tz;
  p=sim(p,4.0);
  return makeshowflake(p);
}

vec2 obj1(vec3 p){
  float f=makeShow(p,1.11, 1.03, 1.38);
  f=min(f,makeShow(p,1.72, 0.74, 1.06));
  f=min(f,makeShow(p,1.93, 0.75, 1.35));
  f=min(f,makeShow(p,1.54, 0.94, 1.72));
  f=min(f,makeShow(p,1.35, 1.33, 1.13));
  f=min(f,makeShow(p,1.55, 0.23, 1.16));
  f=min(f,makeShow(p,1.25, 0.41, 1.04));
  f=min(f,makeShow(p,1.49, 0.29, 1.31));
  f=min(f,makeShow(p,1.31, 1.31, 1.13));  
  return vec2(f,1.0);
}
 
vec3 obj1_c(vec3 p){
    return vec3(1,1,1);
}

//Star
vec2 obj2(vec3 p){
  p.y=p.y-4.3;
  p=p*4.0;
  float l=length(p);
  if (l<2.0){
  p.xy=rotsim(p.xy,2.5);
  p.y=p.y-2.0; 
  p.z=abs(p.z);
  p.x=abs(p.x);
  return vec2(dot(p,normalize(vec3(2.0,1,3.0)))/4.0,2);
  } else return vec2((l-1.9)/4.0,2.0);
}

vec3 obj2_c(vec3 p){
  return vec3(1.0,0.5,0.2);
}
 
//Objects union
vec2 inObj(vec3 p){
  return ObjUnion(obj1(p),obj2(p));
}
 
//Scene End
vec4 main1(float off_x){
	vec2 fragCoord=gl_FragCoord.xy;
	
//	vec2 q = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;


  vec2 vPos=(-1.0+2.0*(fragCoord.xy-pos_correction.xy)/iResolution.xy)*3.0;
	vPos.x+=off_x;
//  vec2 vPos=-1.0+2.0*fragCoord.xy/iResolution.xy;
 
  //Camera animation
  vec3 vuv=normalize(vec3(sin(aTime)*0.3,1,0));
  vec3 vrp=vec3(0,cos(aTime*0.5)+2.5,0);
  vec3 prp=vec3(sin(aTime*0.5)*(sin(aTime*0.39)*2.0+3.5),sin(aTime*0.5)+3.5,cos(aTime*0.5)*(cos(aTime*0.45)*2.0+3.5));
  float vpd=1.5;  
 
  //Camera setup
  vec3 vpn=normalize(vrp-prp);
  vec3 u=normalize(cross(vuv,vpn));
  vec3 v=cross(vpn,u);
  vec3 scrCoord=prp+vpn*vpd+vPos.x*u*iResolution.x/iResolution.y+vPos.y*v;
  vec3 scp=normalize(scrCoord-prp);
 
  //lights are 2d, no raymarching
  mat4 cm=mat4(
    u.x,   u.y,   u.z,   -dot(u,prp),
    v.x,   v.y,   v.z,   -dot(v,prp),
    vpn.x, vpn.y, vpn.z, -dot(vpn,prp),
    0.0,   0.0,   0.0,   1.0);
 
  vec4 pc=vec4(0,0,0,0);
  const float maxl=80.0;
  for(float i=0.0;i<maxl;i++){
  vec4 pt=vec4(
    sin(i*PI*2.0*7.0/maxl)*2.0*(1.0-i/maxl),
    i/maxl*4.0,
    cos(i*PI*2.0*7.0/maxl)*2.0*(1.0-i/maxl),
    1.0);
  pt=pt*cm;
  vec2 xy=(pt/(-pt.z/vpd)).xy+vPos*vec2(iResolution.x/iResolution.y,1.0);
  float c;
  c=0.4/length(xy);
  pc+=vec4(
          (sin(i*5.0+aTime*10.0)*0.5+0.5)*c,
          (cos(i*3.0+aTime*8.0)*0.5+0.5)*c,
          (sin(i*6.0+aTime*9.0)*0.5+0.5)*c,0.0);
  }
  pc=pc/maxl;

  pc=smoothstep(0.0,1.0,pc);

  //Raymarching
  const vec3 e=vec3(0.1,0,0);
  const float maxd=15.0; //Max depth
 
  vec2 s=vec2(0.1,0.0);
  vec3 c,p,n;
 
  float f=1.0;
  for(int i=0;i<64;i++){
    if (abs(s.x)<.001||f>maxd) break;
    f+=s.x;
    p=prp+scp*f;
    s=inObj(p);
  }
  
  if (f<maxd){
    if (s.y==1.0)
      c=obj1_c(p);
    else
      c=obj2_c(p);

	if (s.y<=1.0) {
        pc+=vec4(c*max(1.0-f*.08,0.0),1.0);
    }
    else {
         //tetrahedron normal   
         const float n_er=0.01;
         float v1=inObj(vec3(p.x+n_er,p.y-n_er,p.z-n_er)).x;
         float v2=inObj(vec3(p.x-n_er,p.y-n_er,p.z+n_er)).x;
         float v3=inObj(vec3(p.x-n_er,p.y+n_er,p.z-n_er)).x;
         float v4=inObj(vec3(p.x+n_er,p.y+n_er,p.z+n_er)).x;
         n=normalize(vec3(v4+v1-v3-v2,v3+v4-v1-v2,v2+v4-v3-v1));
  
        float b=max(dot(n,normalize(prp-p)),0.0);
        pc+=vec4((b*c+pow(b,8.0))*(1.0-f*.01),1.0);
	}
  }

    float t= 0., q= 0., ci=aTime;

    vec3 ar1 = vec3(.2*sin(ci),ci*.7,ci);
    vec3 ar2 = vec3(0,0,ci);
    vec3 ar3 = normalize(vec3( fragCoord/iResolution.xy-.5,1.));
    for( int a=0;a<64;a++) {
        p= mod(ar1+q*ar3,1.5)-1.75;
        q+=length(p)-0.005;
        p= mod(ar2+t*ar3,2.+sin(ci/13.)*.4)-1.;
        t+=length(p)-.5;
    }

    p.x+=sin(aTime*.3)*.3;
    p.y+=sin(aTime*.7)*.4;

//    vec4 balls = texture(texture_in,p.xy) / (t / 3.5);
//    vec4 balls = texture(texture_in,vPos);
	vec4 balls=texture(texture_in,vec2(1.0,-1.0)*((gl_FragCoord.xy-pos_correction.xy)/iResolution))/3.0;
//	vec4 balls = vec4(0,0,0,1.0);
	return max(balls, pc);
}

void main() {
	aTime=iTime;
    gl_FragColor = main1(1.5);
	aTime=aTime*1.1+20.0;
	gl_FragColor+= main1(-1.5);
//	float trans=gl_FragColor.r;
//	if (gl_FragColor.g>trans) trans=gl_FragColor.g;
//	if (gl_FragColor.b>trans) trans=gl_FragColor.b;
//	if (trans>0.6) trans=1.0;
//	gl_FragColor.a=trans;
}
