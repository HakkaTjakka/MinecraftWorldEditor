// 11 clouds

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 txt_correction;
uniform vec2 txt_resolution;

uniform vec2 iResolution;
uniform vec2 i;
uniform float iTime;
uniform vec2 iMouse;

const float cloudscale = 1.1;
const float speed = 0.015;
const float clouddark = 0.5;
const float cloudlight = 0.3;
const float cloudcover = 0.2;
const float cloudalpha = 8.0;
const float skytint = 0.5;
const vec3 skycolour1 = vec3(0.2, 0.4, 0.6);
const vec3 skycolour2 = vec3(0.4, 0.7, 1.0);

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

void main() {

//    float resolution = 5. * exp2(-3.*iMouse.x/txt_resolution.x);
//	vec2 uv =(gl_FragCoord.xy-txt_correction.xy) / txt_resolution.xy * resolution;
//	uv.x=-uv.x;

//    vec2 p = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
//    vec2 p2 = (gl_FragCoord.xy-txt_correction.xy) / iResolution.xy;
//    vec2 p2 =  (gl_FragCoord.xy-txt_correction.xy*vec2(-1.5,1.5)) / iResolution.xy;
//    vec2 p2 =  (gl_FragCoord.xy-txt_correction.xy*vec2(-1.5,1.5)/13.0) / iResolution.xy;
    vec2 p2 =  (gl_FragCoord.xy-iTime*vec2(-1.5,1.5)/13.0) / iResolution.xy;

//	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.x * resolution;

//	vec2 uv = (gl_FragCoord.xy-pos_correction.xy)/iResolution.xy;

//    vec2 uv = p*vec2(iResolution.x/iResolution.y,1.0);
    float time = iTime * speed*2.0;
//    float q = fbm(uv * cloudscale * 0.5);

	vec2 uv2 = p2*vec2(iResolution.x/iResolution.y,1.0);
    float q2 = fbm(uv2 * cloudscale * 0.5);

    //ridged noise shape
	float r = 0.0;
	uv2 *= cloudscale;
    uv2 -= q2 - time;
    float weight = 0.8;
    for (int i=0; i<18; i++){
		r += abs(weight*noise( uv2 ));
        uv2 = m*uv2 + time;
		weight *= 0.7;
    }

    //noise shape
	float f = 0.0;
    uv2 = p2*vec2(iResolution.x/iResolution.y,1.0);
	uv2 *= cloudscale;
    uv2 -= q2 - time/10.0;
    weight = 0.7;
    for (int i=0; i<8; i++){
		f += weight*noise( uv2 );
        uv2 = m*uv2 + time;
		weight *= 0.6;
    }

    f *= r + f;

    //noise colour
    float c = 0.0;
    time = iTime * speed * 2.0;
    uv2 = p2*vec2(iResolution.x/iResolution.y,1.0);
	uv2 *= cloudscale*2.0;
    uv2 -= q2 - time;
    weight = 0.4;
    for (int i=0; i<7; i++){
		c += weight*noise( uv2 );
        uv2 = m*uv2 + time/10.0;
		weight *= 0.6;
    }

    //noise ridge colour
    float c1 = 0.0;
    time = iTime * speed * 3.0;
    uv2 = p2*vec2(iResolution.x/iResolution.y,1.0);
	uv2 *= cloudscale*3.0;
    uv2 -= q2 - time;
    weight = 0.4;
    for (int i=0; i<7; i++){
		c1 += abs(weight*noise( uv2 ));
        uv2 = m*uv2 + time;
		weight *= 0.6;
    }

    c += c1;

//    vec3 skycolour = mix(skycolour2, skycolour1, p.y/8.0);
    vec3 skycolour = vec3(0.5,0.5,0.6);
//    vec3 cloudcolour = vec3(1.3, 1.4, 1.2) * clamp((1.0-(clouddark + cloudlight*c)), 0.0, 1.0);
    vec3 cloudcolour = vec3(1.1, 1.1, 0.9) * clamp((clouddark + cloudlight*c), 0.0, 1.0);
    float alpha=(cloudcolour.r+cloudcolour.g+cloudcolour.b)/3.0;

    f = cloudcover + cloudalpha*f*r;

//    vec3 color = texture(texture_in, uv/resolution ).rgb;

//    vec3 result = mix(color, clamp(cloudcolour, 0.0, 1.0), clamp(f + c, 0.0, 1.0));
    vec3 result = mix(skycolour, clamp(skytint * skycolour + cloudcolour, 0.0, 1.4), clamp(f + c, 0.0, 1.2));

//	gl_FragColor = vec4( mix(color,result),1.0);
//	gl_FragColor = vec4( color,1.0);
	gl_FragColor = vec4( result, f );
}
