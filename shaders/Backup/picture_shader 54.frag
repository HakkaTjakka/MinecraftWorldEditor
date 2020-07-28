// 11 clouds

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 txt_correction;
uniform vec2 txt_resolution;

uniform vec2 iResolution;
uniform vec2 i;
uniform float iTime;
uniform vec2 iMouse;

#define Iterations 64

float rand(vec3 r) { return fract(sin(dot(r.xy,vec2(1.38984*sin(r.z),1.13233*cos(r.z))))*653758.5453); }

vec3 camera;

float celldist(vec3 ipos,vec3 pos)
{
	vec3 c=ipos+vec3(rand(ipos),rand(ipos+0.1),rand(ipos+0.2));
	float dist=length(c-pos);
	float radius=(rand(ipos+0.3)*0.3+0.2);
	float shrink=1.0-(1.0+cos(c.x))*(1.0+cos(c.y))*(1.0+cos(c.z))/8.0;
	float avoid=max(0.0,0.5-length(c-camera));
	return dist-radius*shrink+avoid;
}

float distfunc(vec3 pos)
{
	vec3 ipos=floor(pos)-0.5;

	float d1=celldist(ipos+vec3(0.0,0.0,0.0),pos);
	float d2=celldist(ipos+vec3(0.0,0.0,1.0),pos);
	float d3=celldist(ipos+vec3(0.0,1.0,0.0),pos);
	float d4=celldist(ipos+vec3(0.0,1.0,1.0),pos);
	float d5=celldist(ipos+vec3(1.0,0.0,0.0),pos);
	float d6=celldist(ipos+vec3(1.0,0.0,1.0),pos);
	float d7=celldist(ipos+vec3(1.0,1.0,0.0),pos);
	float d8=celldist(ipos+vec3(1.0,1.0,1.0),pos);

	return min(0.5,min(min(min(d1,d2),min(d3,d4)),min(min(d5,d6),min(d7,d8))));
}

vec3 gradient(vec3 pos)
{
	const float eps=0.001;
	float mid=distfunc(pos);
	return vec3(
	distfunc(pos+vec3(eps,0.0,0.0))-mid,
	distfunc(pos+vec3(0.0,eps,0.0))-mid,
	distfunc(pos+vec3(0.0,0.0,eps))-mid);
}


void main( )
{
	const float pi=3.141592;
	vec2 coords=(2.0*(gl_FragCoord.xy-pos_correction.xy)-iResolution.xy)/max(iResolution.x,iResolution.y);

	vec3 ray_dir=normalize(vec3(coords,1.0));
	vec3 ray_pos=vec3(0.0,-3.0*iTime,0.0);
	camera=ray_pos;

	float a=iTime/20.0;
	ray_dir=ray_dir*mat3(
		cos(a),0.0,sin(a),
		0.0,1.0,0.0,
		-sin(a),0.0,cos(a)
	);

	float i=float(Iterations);
	for(int j=0;j<Iterations;j++)
	{
		float dist=distfunc(ray_pos);
		ray_pos+=dist*ray_dir;

		if(abs(dist)<0.001) { i=float(j); break; }
	}

	vec3 normal=normalize(gradient(ray_pos));

	float ao=1.0-i/float(Iterations);
	float what=pow(max(0.0,dot(normal,-ray_dir)),0.5);
	//float vignette=pow(1.0-length(coords),0.3);
	float light=ao*what*1.0;

	float z=length(ray_pos.xz);
//	vec3 col=(sin(vec3(z,z+pi/3.0,z+pi*2.0/3.0))+2.0)/3.0;
	vec3 col=exp(-vec3(z/5.0+0.1,z/30.0,z/10.0+0.1));

	vec3 reflected=reflect(ray_dir,normal);
	vec3 env=vec3(clamp(reflected.y*4.0,0.0,1.0));

	gl_FragColor=vec4(col*light+0.1*env*ao,1.0);
}
