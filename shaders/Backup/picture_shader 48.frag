// 48 

uniform sampler2D texture_in;
uniform float float_param1;
uniform float float_param2;
uniform vec2 pos_correction;

uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

//#ifdef GL_ES
//precision highp float;
//#endif

#ifdef GL_ES
precision highp float;
#endif

//uniform float time;
//uniform vec2 mouse;
//uniform vec2 resolution;

// Some updates by vlt/dfm
// Added lighting and materials

//Original code from an unknown p	erson
//Heavily expanded upon by Citiral

//I finally understand raymarching ;)

vec3 rotXaxis(vec3 p, float rad) {
	float z2 = cos(rad) * p.z - sin(rad) * p.y;
	float y2 = sin(rad) * p.z + cos(rad) * p.y;
	p.z = z2;
	p.y = y2;
	return p;
}

vec3 rotYaxis(vec3 p, float rad) {
	float x2 = cos(rad) * p.x - sin(rad) * p.z;
	float z2 = sin(rad) * p.x + cos(rad) * p.z;
	p.x = x2;
	p.z = z2;
	return p;
}
vec3 rotZaxis(vec3 p, float rad) {
	float x2 = cos(rad) * p.x - sin(rad) * p.y;
	float y2 = sin(rad) * p.x + cos(rad) * p.y;
	p.x = x2;
	p.y = y2;
	return p;
}

//t.x = torus center size, t.y = torus volume size
float Torus(vec3 p, vec2 t)
{
	vec2 q = vec2(length(p.xz)-t.x, p.y);
    	return length(q)-t.y;
}

float Box(vec3 p, vec3 b)
{
	return length(max(abs(p) - b, 0.));
}

float Hexagon( vec3 p, vec2 h )
{
    vec3 q = abs(p);
    return max(q.z-h.y,max(q.x+q.y*0.157735,q.y*1.1547)-h.x);
}

vec2 map( vec3 p ){

	vec3 p1 = p;
	p1.x += 0.02;
	p1 = rotXaxis(p1,iTime - 3.1415/2. + p.x * 35. * cos(iTime));
	float tor1 = Torus(p1, vec2(0.022, 0.008));
	vec3 p2 = p;
	p2 = rotXaxis(p2,iTime);
	float tor2 = Torus(p2, vec2(0.02, 0.008));

	vec3 p3 = p;
	p3.x -= 0.05;
	p3 = rotZaxis(p3, p.z * 20. + iTime);
	p3 = rotYaxis(p3, iTime * 1.2);
	p3 = rotZaxis(p3, iTime * 1.4);
	float box1 = Hexagon(p3, vec2(0.02,0.03));
	box1 = max(box1, -tor2+0.004);

	float d = min(tor1, min(tor2, box1));

	// Which obj is are we returning
	float th = 0.000001;
	float o = float(abs(tor2-d)<=th)+float(abs(box1-d)<=th)*2.;

	return vec2(d,o);
}

void main( void )
{
    	vec2 pos = ((gl_FragCoord.xy-pos_correction)*2.0 - iResolution.xy) / iResolution.y;
    	vec3 camPos = vec3(0., 0., 0.1);
    	vec3 camTarget = vec3(0.0, 0.0, 0.0);

    	vec3 camDir = normalize(camTarget-camPos);
    	vec3 camUp  = normalize(vec3(0.0, 1.0, 0.0));
    	vec3 camSide = cross(camDir, camUp);
    	float focus = 2.0;

	vec3 rayDir = normalize(camSide*pos.x + camUp*pos.y + camDir*focus);
    	vec3 ray = camPos;
    	float d = 0.0, total_d = 0.0;
 	vec2 r;
	const int MAX_MARCH = 64;
 	const float MAX_DIST = 0.45;
	vec4 result;
	int steps = 0;

    	for(int i=0; i<MAX_MARCH; ++i) {
		r = map(ray);
        	d = r.x;
        	total_d += d;
        	ray += rayDir * d;
		if(abs(d)<0.000001) {
			steps = i;
			break;
		}
		if(total_d >= MAX_DIST) {
			total_d = MAX_DIST;
			steps = MAX_MARCH;
			break;
		}
    	}

	// lighting
	float c = 0.75 - (float(total_d) / float(MAX_DIST));
	vec2 e=vec2(.00125,0);
	vec3 n=normalize(vec3(d-map(ray-e.xyy).x,d-map(ray-e.yxy).x,d-map(ray-e.yyx).x));
	float b=max(dot(n,normalize(camPos-ray)),0.);
	float light = b*c+pow(b,118.)*113.;

	vec3 col = vec3(1.0*r.y,0.8-0.2*r.y,1.3);

	result = vec4(light*col,1.);

	gl_FragColor = mix(result, vec4(1.,1.,1.,1.),min(d,-.1));
}
