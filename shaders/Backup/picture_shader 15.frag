//15 blob

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform int background_plot;

/**
 * Created by Kamil Kolaczynski (revers) - 2016
 *
 * Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 *
 * This shader, as always, uses a lot of code (raymarching, noise and lighting) credited to iq
 * [ https://www.shadertoy.com/view/Xds3zN ].
 * Camera path is based on Shane's "Subterranean Fly-Through" [ https://www.shadertoy.com/view/XlXXWj ].
 * Additional specular lighting trick is based on "Wet stone" by TDM [ https://www.shadertoy.com/view/ldSSzV ].
 * Thanks for sharing great code guys!
 *
 * The shader was created and exported from Synthclipse [ http://synthclipse.sourceforge.net/ ].
 */
const float FOV = 0.4;
const float MarchDumping = 0.7579;
const float Far = 150.925;
//const float Far = 38.925;
const int MaxSteps = 1024;
//const float CameraSpeed = 0.2;
const float CameraSpeed = 0.02;
//const float CameraSpeed = 1.5099998;
const float TunnelSmoothFactor = 2.0;
const float TunnelRadius = 0.85660005;
const float TunnelFreqA = 0.18003;
const float TunnelFreqB = 0.25;
const float TunnelAmpA = 3.6230998;
const float TunnelAmpB = 2.4324;
const float NoiseIsoline = 0.319;
const float NoiseScale = 0.909980001;
//const float NoiseScale = 4.1980001;
//const vec3 Color = vec3(0.085, 0.658, 1.0);

#define M_NONE -1.0
#define M_NOISE 1.0

float hash(float h) {
	return fract(sin(h) * 43758.5453123);
}

float noise(vec3 x) {
	vec3 p = floor(x);
	vec3 f = fract(x);
	f = f * f * (3.0 - 2.0 * f);

	float n = p.x + p.y * 157.0 + 113.0 * p.z;
	return mix(
			mix(mix(hash(n + 0.0), hash(n + 1.0), f.x),
					mix(hash(n + 157.0), hash(n + 158.0), f.x), f.y),
			mix(mix(hash(n + 113.0), hash(n + 114.0), f.x),
					mix(hash(n + 270.0), hash(n + 271.0), f.x), f.y), f.z);
}

float fbm(vec3 p) {
	float f = 0.0;
	f = 0.5000 * noise(p+iTime/10.0);
	p *= 2.01;
	f += 0.2500 * noise(p+iTime/10.0);
	p *= 2.02;
	f += 0.1250 * noise(p+iTime/5.0);

	return f;
}

// by iq. http://iquilezles.org/www/articles/smin/smin.htm
float smax(float a, float b, float k) {
	float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
	return mix(a, b, h) + k * h * (1.0 - h);
}

// From "Subterranean Fly-Through" by Shane https://www.shadertoy.com/view/XlXXWj
vec2 path(float z) {
	return vec2(TunnelAmpA * sin(z * TunnelFreqA), TunnelAmpB * cos(z * TunnelFreqB));
}

float noiseDist(vec3 p) {
	p = p / NoiseScale;
	return (fbm(p) - NoiseIsoline) * NoiseScale;
}

vec2 map(vec3 p) {
	float d = noiseDist(p);
	float d2 = length(p.xy - path(p.z)) - TunnelRadius ;
	d = smax(d, -d2, TunnelSmoothFactor);

	vec2 res = vec2(d, M_NOISE);
	return res;
}

vec2 castRay(vec3 ro, vec3 rd) {
	float tmin = 0.0;
	float tmax = Far;

	float precis = 0.000002;
	float t = tmin;
	float m = M_NONE;

	for (int i = 0; i < MaxSteps; i++) {
		vec2 res = map(ro + rd * t);
		if (res.x < precis || t > tmax) {
			break;
		}
		t += res.x * MarchDumping;
		m = res.y;
	}
	if (t > tmax) {
		m = M_NONE;
	}
	return vec2(t, m);
}

float softshadow(vec3 ro, vec3 rd, float mint, float tmax) {
	float res = 1.0;
	float t = mint;

	for (int i = 0; i < 32; i++) {
		float h = map(ro + rd * t).x;

		res = min(res, 8.0 * h / t);
		t += clamp(h, 0.02, 0.10);

		if (h < 0.0001 || t > tmax) {
			break;
		}
	}
	return clamp(res, 0.0, 1.0);
}

vec3 calcNormal(vec3 pos) {
	vec2 eps = vec2(0.001, 0.0);

	vec3 nor = vec3(map(pos + eps.xyy).x - map(pos - eps.xyy).x,
			map(pos + eps.yxy).x - map(pos - eps.yxy).x,
			map(pos + eps.yyx).x - map(pos - eps.yyx).x);
	return normalize(nor);
}

float calcAO(vec3 pos, vec3 nor) {
	float occ = 0.0;
	float sca = 1.0;

	for (int i = 0; i < 10; i++) {
		float hr = 0.01 + 0.12 * float(i) / 4.0;
		vec3 aopos = nor * hr + pos;
		float dd = map(aopos).x;

		occ += -(dd - hr) * sca;
		sca *= 0.95;
	}
	return clamp(1.0 - 3.0 * occ, 0.0, 1.0);
}

//const vec3 Color = vec3(0.085, 0.658, 1.0);

//vec4 render(vec3 ro, vec3 rd) {
vec3 render(vec3 ro, vec3 rd) {
	vec3 col = vec3(0.0);
	vec2 res = castRay(ro, rd);
	float t = res.x;
	float m = res.y;

	if (m > -1.5) {
		vec3 pos = ro + t * rd;
		vec3 nor = calcNormal(pos);

		// material
        vec3 Color=vec3(0.3+sin(iTime * 0.063213) * 0.3,0.5+sin(iTime * 0.0734) * 0.444,0.8+sin(iTime * 0.0812312) * 0.2);

//		col = Color + sin(t * 1.0) * 0.4;
		col = Color + sin(t * 0.8) * 0.3;
		col += 0.3 * sin(vec3(0.15, 0.02, 0.10) * iTime );
//		col.r += 0.3 * sin(1.0+0.7165 * (iTime*0.055+t) );
//		col.g += 0.3 * sin(2.0+0.8332 * (iTime*0.0193+t) );
//		col.b += 0.3 * sin(3.0+0.9521 * (iTime*0.02134+t) );

		// lighitng
		float occ = calcAO(pos, nor);
		vec3 lig = -rd;
		float amb = clamp(0.5 + 0.5 * nor.y, 0.0, 1.0);
		float dif = clamp(dot(nor, lig), 0.0, 1.0);

		float fre = pow(clamp(1.0 + dot(nor, rd), 0.0, 1.0), 2.0);

		vec3 ref = reflect(rd, nor);
		float spe = pow(clamp(dot(ref, lig), 0.0, 1.0), 100.0);

		dif *= softshadow(pos, lig, 0.02, 2.5);

		vec3 brdf = vec3(0.0);
		brdf += 1.20 * dif * vec3(1.00, 0.90, 0.60);
		brdf += 1.20 * spe * vec3(1.00, 0.90, 0.60) * dif;

		// Additional specular lighting trick,
		// taken from "Wet stone" by TDM
		// https://www.shadertoy.com/view/ldSSzV
		nor = normalize(nor - normalize(pos) * 0.2);
		ref = reflect(rd, nor);
		spe = pow(clamp(dot(ref, lig), 0.0, 1.0), 100.0);
		brdf += 2.20 * spe * vec3(1.00, 0.90, 0.60) * dif;

		brdf += 0.40 * amb * vec3(0.50, 0.70, 1.00) * occ;
		brdf += 0.40 * fre * vec3(1.00, 1.00, 1.00) * occ;

		col = col * brdf;

		col = mix(col, vec3(0.0), 1.0 - exp(-0.005 * t * t));
//        return vec4(clamp(col, 0.0, 1.0),1.0);
	}
//	return vec4(0.0,0.0,0.0,0.0);
    return clamp(col, 0.0, 1.0);
}

mat3 rotationZ(float a) {
	float sa = sin(a);
	float ca = cos(a);

	return mat3(ca, sa, 0.0, -sa, ca, 0.0, 0.0, 0.0, 1.0);
}

void main() {
	vec2 q = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy ;
	vec2 coord = 2.0 * q - 1.0;
	coord.x *= iResolution.x / iResolution.y ;
	coord *= FOV*2.0;

    float t = iTime * CameraSpeed + 4.0 * 60.0;
    vec3 ro = vec3(path(t), t);

    t += 0.5;
    vec3 target = vec3(path(t), t);
    vec3 dir = normalize(target - ro);
    vec3 up = vec3(-0.9309864, -0.33987653, 0.1332234) * rotationZ(iTime * 0.005);
    vec3 upOrtho = normalize(up - dot(dir, up) * dir);
    vec3 right = normalize(cross(dir, upOrtho));

    vec3 rd = normalize(dir + coord.x * right + coord.y * upOrtho);

//    vec4 col = render(ro, rd);
    vec3 col = render(ro, rd);

    col = pow(col, vec3(0.4545));
//    col.rgb = pow(col.rgb, vec3(0.4545));

    gl_FragColor = vec4(col, 1.0);
//    gl_FragColor = col;
//    return  vec4(col, 1.0);
}


//void main() {
//  gl_FragColor= main2(gl_FragCoord.xy);


//  float tussen=gl_FragColor.g;
//  gl_FragColor.r=1.0-gl_FragColor.b*2.0;
//  gl_FragColor.b=1.0-gl_FragColor.g;
//  gl_FragColor.r=0.5+gl_FragColor.b/2.0;
//    gl_FragColor.r=(gl_FragColor.g+gl_FragColor.b)/2.0;

//  gl_FragColor= (main2(gl_FragCoord.xy)*4 +
//                ( main2(gl_FragCoord.xy+vec2(-1,0)) + main2(gl_FragCoord.xy+vec2(0,-1)) + main2(gl_FragCoord.xy+vec2(1,0)) + main2(gl_FragCoord.xy+vec2(0,1)) ) )/8;

//                 main2(gl_FragCoord.xy+vec2(-1,-1)) + main2(gl_FragCoord.xy+vec2(-1,1)) + main2(gl_FragCoord.xy+vec2(1,-1)) + main2(gl_FragCoord.xy+vec2(1,1)) )/16  ;
//    if (background_plot==1) {
//        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
//        gl_FragColor = mix(gl_FragColor,background,background.a);
//    }
//}


