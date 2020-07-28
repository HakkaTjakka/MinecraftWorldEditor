//shader 30 Ribbon Assault

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform vec2 pos_pacman;

// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// https://www.shadertoy.com/view/MdBGDK
// By David Hoskins.

// GregRostami's version enabled (see comments....

/*
void main()
{
    float T = iTime, f = 3., g = f, d;
	vec2 r = iResolution.xy, m = iMouse.xy, p, u = (gl_FragCoord.xy-r) / r.y;
	m = (vec2(sin(T*.3)*sin(T*.17) + sin(T * .3), (1.-cos(T*.632))*sin(T*.131)*1.+cos(T* .3))+1.) * r;
//	iMouse.z < .5 ? m = (vec2(sin(T*.3)*sin(T*.17) + sin(T * .3), (1.-cos(T*.632))*sin(T*.131)*1.+cos(T* .3))+1.) * r : m;
	p = (2.+m-r) / r.y;
	for( int i = 0; i < 20;i++)
		u = vec2( u.x, -u.y ) / dot(u,u) + p,
		u.x =  abs(u.x),
		f = max( f, dot(u-p,u-p) ),
		g = min( g, sin(dot(u+p,u+p))+1.);
	f = abs(-log(f) / 3.5);
	g = abs(-log(g) / 8.);
	gl_FragColor = min(vec4(g, g*f, f, 0), 1.);
}
*/


void main()
{
    float gTime = iTime+11.0;

    float f = 3., g = 3.;
	vec2 res = iResolution.xy;
	vec2 mou = iMouse.xy;
//	if (iMouse.z < 0.5)
//	{
		mou = vec2(sin(gTime * .3)*sin(gTime * .17) * 1. + sin(gTime * .3),(1.0-cos(gTime * .632))*sin(gTime * .131)*1.0+cos(gTime * .3));
		mou = (mou+1.0) * res;
//	}
	vec2 z = ((-res+2.0 * (gl_FragCoord.xy-pos_pacman)) / res.y);
	vec2 p = ((-res+2.0+mou) / res.y);
	for( int i = 0; i < 20; i++)
	{
		float d = dot(z,z);
		z = (vec2( z.x, -z.y ) / d) + p;
		z.x =  abs(z.x);
		f = max( f, (dot(z-p,z-p) ));
		g = min( g, sin(dot(z+p,z+p))+1.0);
	}
	f = abs(-log(f) / 3.5);
	g = abs(-log(g) / 8.0);
	gl_FragColor = vec4(min(vec3(g, g*f, f), 1.0),1.0);
}

