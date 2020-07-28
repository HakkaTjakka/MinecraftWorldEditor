// 11 clouds

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 txt_correction;
uniform vec2 txt_resolution;

uniform vec2 iResolution;
uniform vec2 i;
uniform float iTime;
uniform vec2 iMouse;

// Rendezvous. By David Hoskins. Jan 2014.
// A Kleinian thingy, breathing, and with pumping arteries!
// https://www.shadertoy.com/view/ldjGDw

// Add crude reflections..
 #define REFLECTIONS

// For red/cyan 3D. Red on the left.
// #define STEREO


#define CSize  vec3(.808, .8, 1.137)
#define FogColour vec3(.05, .05, .05)

vec3  lightPos;
float intensity;

//----------------------------------------------------------------------------------------
float Hash( float n )
{
    return fract(sin(n)*43758.5453123);
}

//----------------------------------------------------------------------------------------
float Noise( in float x )
{
    float p = floor(x);
    float f = fract(x);
    f = f*f*(3.0-2.0*f);
    return mix(Hash(p), Hash(p+1.0), f);
}

//----------------------------------------------------------------------------------------
float Map( vec3 p )
{
	float scale = 1.0;
	float add = sin(iTime)*.2+.1;

	for( int i=0; i < 9;i++ )
	{
		p = 2.0*clamp(p, -CSize, CSize) - p;
		float r2 = dot(p,p);
		float k = max((1.15)/r2, 1.);
		p     *= k;
		scale *= k;
	}
	float l = length(p.xy);
	float rxy = l - 4.0;
	float n = l * p.z;
	rxy = max(rxy, -(n) / (length(p))-.07+sin(iTime*2.0+p.x+p.y+23.5*p.z)*.02);
    float x = (1.+sin(iTime*2.));x =x*x*x*x*.5;
    float h = dot(sin(p*.013),(cos(p.zxy*.191)))*x;
	return ((rxy+h) / abs(scale));

}
vec3 pal( in float t, in vec3 a, in vec3 b, in vec3 c, in vec3 d )
{
    return a + b*cos( 6.28318*(c*t+d) );
}

//----------------------------------------------------------------------------------------
vec3 Colour( vec3 p)
{
	float col	= 0.0;
	float r2	= dot(p,p);
	float add = sin(iTime)*.2+.1;

	for( int i=0; i < 10;i++ )
	{
		vec3 p1= 2.0 * clamp(p, -CSize, CSize)-p;
		col += abs(p.z-p1.z);
		p = p1;
		r2 = dot(p,p);
		float k = max((1.15)/r2, 1.0);
		p *= k;
	}
	return (0.5+0.5*sin(col*vec3(.6 ,-.9 ,4.9)))*.75 + .15;
    //return pal(0.5+0.5*sin(col), vec3(0.5,0.5,0.5),vec3(0.5,0.5,0.5),vec3(1.0,1.0,1.0),vec3(0.0,0.33,0.67) );
    //return pal(0.5+0.5*cos(col), vec3(0.8,0.5,0.4),vec3(0.2,0.4,0.2),vec3(2.0,1.0,1.0),vec3(0.0,0.25,0.25) );
}

//----------------------------------------------------------------------------------------
float RayMarch( in vec3 ro, in vec3 rd )
{
	float precis = 0.001;
    float h		 = 0.0;
    float t		 = .0;
	float res	 = 200.0;
	bool hit	 = false;
	// If I rearrange the loop in a more logical way,
	// I get a black screen on Windows.
    for( int i = 0; i < 120; i++ )
    {
		if (!hit && t < 12.0)
		{
			h = Map(ro + rd * t);
			if (h < precis)
			{
				res = t;
				hit = true;
			}
			t += h * .83;
		}
    }

    return res;
}

//----------------------------------------------------------------------------------------
float Shadow(in vec3 ro, in vec3 rd, float dist)
{
	float res = 1.0;
    float t = 0.02;
	float h = 0.0;

	for (int i = 0; i < 14; i++)
	{
		// Don't run past the point light source...
		if(t < dist)
		{
			h = Map(ro + rd * t);
			res = min(4.*h / t, res);
			t += 0.0 + h*.4;
		}
	}
    return clamp(res, 0.0, 1.0);
}

//----------------------------------------------------------------------------------------
vec3 Normal(in vec3 pos, in float t)
{
	vec2  eps = vec2(t*t*.0075,0.0);
	vec3 nor = vec3(Map(pos+eps.xyy) - Map(pos-eps.xyy),
					Map(pos+eps.yxy) - Map(pos-eps.yxy),
					Map(pos+eps.yyx) - Map(pos-eps.yyx));
	return normalize(nor);
}

//----------------------------------------------------------------------------------------
float LightGlow(vec3 light, vec3 ray, float t)
{
	float ret = 0.0;
	if (length(light) < t)
	{
		light = normalize(light);
		ret = pow(max(dot(light, ray), 0.0), 2000.0)*.5;
		float a = atan(light.x - ray.x, light.z - ray.z);
		ret = (1.0+(sin(a*10.0-iTime*4.3)+sin(a*13.141+iTime*3.141)))*(sqrt(ret))*.05+ret;
		ret *= 3.0;
	}

	return ret;
}

//----------------------------------------------------------------------------------------
vec3 RenderPosition(vec3 pos, vec3 ray, vec3 nor, float t)
{
	vec3 col = vec3(0.0);
	vec3 lPos  = lightPos-pos;
	float lightDist = length(lPos);
	vec3 lightDir  = normalize(lPos);

	float bri = max( dot( lightDir, nor ), 0.0) * intensity;
	float spe = max(dot(reflect(ray, nor), lightDir), 0.0);
	float amb = max(abs(nor.z)*.04, 0.025);
	float sha = Shadow(pos, lightDir, lightDist);
	col = Colour(pos);
	col = col * bri *sha+ pow(spe, 15.0) *sha*.7 +amb*col;

	return col;
}

//----------------------------------------------------------------------------------------
void main()
{
	vec2 q = (gl_FragCoord.xy-pos_correction.xy)/iResolution.xy;
    vec2 p = -1.0+2.0*q;
	p.x *= iResolution.x/iResolution.y;

	#ifdef STEREO
	float isRed = mod(gl_FragCoord.x + mod(fragCoord.y,2.0),2.0);
	#endif

	float time = sin(1.6+iTime*.05 + iMouse.x*.005)*12.5;
    // camera
	float height = (smoothstep(9.4, 11.5, abs(time))*.5);
	vec3 origin = vec3( 1.2, time+1.0, 2.5+height);
	vec3 target = vec3(.0+sin(time)+sin(time*5)*0.2, 0.0, 2.5-height*4.0);
	lightPos = origin+vec3(-0.56-cos(time*2.0+2.8)*.3, -1.4, .24+cos(time*2.0+1.5)*.3);
	intensity = .8+.3*Noise(iTime*5.0);

	vec3 cw = normalize( target-origin);
	vec3 cp = normalize(vec3(0.0, sin(iTime*.25 + iMouse.x*.005), 1.80));
	vec3 cu = normalize( cross(cw,cp) );
	vec3 cv = cross(cu,cw);
	vec3 ray = normalize( p.x*cu + p.y*cv + 2.6*cw );
	#ifdef STEREO
	origin += .008*cu*isRed; // move camera to the right - the rd vector is still good
	#endif

	vec3 col = vec3(0.0);
	float t = 0.0;
	t = RayMarch(origin, ray);

	if(t < 199.0)
	{
		vec3 pos = origin + t * ray;
		vec3 nor = Normal(pos, t);
		col = RenderPosition(pos, ray, nor, t);

		#ifdef REFLECTIONS
		vec3 ray2    = reflect(ray, nor);
		vec3 origin2 = pos + nor*.01;
		float d = RayMarch(origin2, ray2);
		if(d < 199.0)
		{
			pos = origin2 + d * ray2;
			nor = Normal(pos, d);
			col += RenderPosition(pos, ray, nor, d) * .2;
		}
		#endif
	}

	// Effects...
	col = mix(FogColour, col, exp(-.6*max(t-3.0, 0.0)));
    col = clamp(mix(col, vec3(.333), -.07), 0.0, 1.0);
	col = pow(col, vec3(.45));
	//col *= pow(20.0*q.x*q.y*(1.0-q.x)*(1.0-q.y), 0.2);
	col += LightGlow(lightPos-origin, ray, t) * intensity;

	#ifdef STEREO
	col *= vec3( isRed, 1.0-isRed, 1.0-isRed );
	#endif

	gl_FragColor=vec4(clamp(col, 0.0, 1.0),1.0);
}
