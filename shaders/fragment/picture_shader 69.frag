// 11 clouds

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 pos_correction2;

uniform vec2 pos_abs;
uniform vec2 iResolution;
uniform vec2 i;
uniform float iTime;

const float cloudscale = 1.1;
const float speed = 0.01;
float clouddark = 0.5;
const float cloudlight = 0.6 ;
const float cloudcover = 0.2;
const float cloudalpha = 8.0;
const float skytint = 0.5;
const vec3 skycolour1 = vec3(0.2, 0.4, 0.8);
const vec3 skycolour2 = vec3(0.5, 0.6, 0.9);
//const vec3 skycolour2 = vec3(0.4, 0.7, 1.0);

const mat2 m = mat2( 1.6,  1.2, -1.2,  1.6 );

vec2 hash( vec2 p ) {
	p = vec2(dot(p,vec2(127.1,311.7)), dot(p,vec2(269.5,183.3)));
	return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}

float noise( in vec2 p ) {
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;
	vec2 i = floor(p + (p.x+p.y)*K1);
    vec2 a = p - i + (i.x+i.y)*K2;
    vec2 o = (a.x>a.y) ? vec2(1.0,0.0) : vec2(0.0,1.0); //vec2 of = 0.5 + 0.5*vec2(sign(a.x-a.y), sign(a.y-a.x));
    vec2 b = a - o + K2;
	vec2 c = a - 1.0 + 2.0*K2;
    vec3 h = max(0.5-vec3(dot(a,a), dot(b,b), dot(c,c) ), 0.0 );
	vec3 n = h*h*h*h*vec3( dot(a,hash(i+0.0)), dot(b,hash(i+o)), dot(c,hash(i+1.0)));
    return dot(n, vec3(70.0));
}

float fbm(vec2 n) {
	float total = 0.0, amplitude = 0.1;
	for (int i = 0; i < 7; i++) {
		total += noise(n) * amplitude;
		n = m * n;
		amplitude *= 0.4;
	}
	return total;
}

// -----------------------------------------------



#define PI 3.14159265358979

// Convert HSL colorspace to RGB. http://en.wikipedia.org/wiki/HSL_and_HSV
vec3 HSLtoRGB(in vec3 c)
{
	vec3 rgb = clamp(abs(mod(c.x+vec3(0.,4.,2.),6.)-3.)-1.,0.,1.);
	return c.z+c.y*(rgb-0.5)*(1.-abs(2.*c.z-1.));
}

vec3 HSL2RGB_CubicSmooth(in vec3 c)
{
    vec3 rgb = clamp(abs(mod(c.x+vec3(0.,4.,2.),6.)-3.)-1.,0.,1.);
    rgb = rgb*rgb*(3.0-2.0*rgb); // iq's cubic smoothing.
    return c.z+ c.y*(rgb-0.5)*(1.-abs(2.*c.z-1.));
}

vec3 getcolor( vec2 fragCoord )
{
	vec2 uv = (-1.+2.*fragCoord.xy/iResolution.xy)*vec2(iResolution.x/iResolution.y,1.)/8.0;
	float fAngle = iTime*0.4+length(uv)*5.0;
	float h = atan(uv.x,uv.y) - fAngle;
	float x = 0.50;
//	float x = length(uv);
//    iTime=2.14;
    iTime=length(uv)*3.0;
	float a = -(0.6+0.2*sin(iTime*3.1+sin((iTime*0.8+h*2.0)*3.0))*sin(iTime+h));
	float b = -(0.8+0.3*sin(iTime*1.7+sin((iTime+h*4.0))));
	float c = 1.25+sin((iTime+sin((iTime+h)*3.0))*1.3)*0.15;
	float l = a*x*x + b*x + c;
	//vec3 hsl_standard = HSLtoRGB(vec3(h*3./PI,1.,l));
	return HSL2RGB_CubicSmooth(vec3(h*3.0/PI,1.,l));
}

void main() {
//    pos_correction.xy=(vec2(1.0,-1.0)*pos_correction2.xy + vec2(-960.0,560.0));

    vec2 p = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
//    vec2 p = (gl_FragCoord.xy-pos_correction.xy+pos_abs.xy*vec2(8.0,-8.0)*iResolution.xy) / iResolution.xy;
	vec2 uv = -p*vec2(iResolution.x/iResolution.y,1.0);



    float time = iTime * speed;
    float q = fbm(uv * cloudscale * 0.5);

    //ridged noise shape
	float r = 0.0;
	uv *= cloudscale;
    uv -= q - time;
    float weight = 0.8;
    for (int i=0; i<8; i++){
		r += abs(weight*noise( uv ));
        uv = m*uv + time;
		weight *= 0.7;
    }

    //noise shape
	float f = 0.0;
    uv = p*vec2(iResolution.x/iResolution.y,1.0);
	uv *= cloudscale;
    uv -= q - time;
    weight = 0.7;
    for (int i=0; i<8; i++){
		f += weight*noise( uv );
        uv = m*uv + time;
		weight *= 0.6;
    }

    f *= r + f;

    //noise colour
    float c = 0.0;
    time = iTime * speed * 2.0;
    uv = p*vec2(iResolution.x/iResolution.y,1.0);
	uv *= cloudscale*2.0;
    uv -= q - time;
    weight = 0.4;
    for (int i=0; i<7; i++){
		c += weight*noise( uv );
        uv = m*uv + time;
		weight *= 0.6;
    }

    //noise ridge colour
    float c1 = 0.0;
    time = iTime * speed * 3.0;
    uv = p*vec2(iResolution.x/iResolution.y,1.0);
	uv *= cloudscale*3.0;
    uv -= q - time;
    weight = 0.4;
    for (int i=0; i<7; i++){
		c1 += abs(weight*noise( uv ));
        uv = m*uv + time;
		weight *= 0.6;
    }

    c += c1;
//    vec3 skycolour = mix(skycolour2, skycolour1, 0.6/8.0);


    vec3 skycolour = getcolor(gl_FragCoord.xy-pos_correction.xy);
    skycolour = mix(skycolour, skycolour1, 0.3);

//    vec3 skycolour = mix(skycolour2, skycolour1, p.y/8.0);

    vec3 cloudcolour = vec3(1.1, 1.1, 0.9) * clamp((clouddark + cloudlight*c), 0.0, 1.0);
//    vec3 cloudcolour = vec3(1.1, 1.1, 0.9) * clamp((clouddark + cloudlight*c), 0.0, 1.0);
//    vec3 cloudcolour = vec3(1.1, 1.1, 0.9) * clamp((clouddark + cloudlight*c), 0.0, 1.0);

//    vec3 cloudcolour = getcolor(gl_FragCoord.xy-pos_correction.xy) * clamp((clouddark + cloudlight*c), 0.0, 1.0);

//    vec3 cloudcolour = getcolor(gl_FragCoord.xy-pos_correction.xy);


    f = cloudcover + cloudalpha*f*r;

    vec3 result = mix(skycolour, clamp(skytint * skycolour + cloudcolour, 0.0, 1.0), clamp(f + c, 0.0, 1.0));

	gl_FragColor = vec4( result, 1.0 );
}
