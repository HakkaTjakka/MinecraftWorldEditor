//cubes

uniform sampler2D texture;
uniform float float_param1;
uniform float float_param2;
uniform vec2 pos_correction;


uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

const float PI = 3.14;

float mapSphere(vec3 p) {
	return length(p) - 1.0;
}

float mapCube(vec3 p) {
 	return length(max(abs(p)- vec3(0.5, 0.5, 0.5), 0.0));
}

float mapTorus(vec3 p) {
	vec2 q = vec2(length(p.xz) - 0.9, p.y);
 	return length(q) - 0.1;
}

float mapPlane(vec3 p) {
	vec4 n = vec4(0.1, 0.0, 0.0, 1.0);
    return dot(p, n.xyz) + n.w;
}

float repeat(vec3 p, vec3 c) {
    vec3 q = mod(p, c) - 0.5 * c;
    return mapCube(q);
}

float trace(vec4 o, vec4 r, mat4 transforms) {
	float t = 0.0;
    for (int i = 0; i < 32; i++) {

        vec4 p = o + r * t;

        /*
			Repeatition code
		*/
        p.x = mod(p.x + 1.0, 2.0) - 1.;
        p.y = mod(p.y + 1.0, 2.0) - 1.;
        p.z = mod(p.z + 1.0, 2.0) - 1.;


        float d = mapCube((transforms * p).xyz);
        t += d * 0.5;

    }
    return t;
}

mat4 rotateX(float a) {
	return mat4(
    	1.0, 0.0, 0.0, 0.0,
        0.0, cos(a), sin(a), 0.0,
        0.0, -sin(a), cos(a), 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 rotateY(float a) {
	return mat4(
    	cos(a), 0.0, sin(a), 0.0,
        0.0, 1.0, 0.0, 0.0,
        -sin(a), 0.0, cos(a), 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 rotateZ(float a) {
	return mat4(
    	cos(a), sin(a), 0.0, 0.0,
        -sin(a), cos(a), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
}

mat4 translate(float x, float y, float z) {
	return mat4(
    	1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        x, y, z, 1.0
    );
}

void main() {

    float time = iTime;

    /*
    vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
    uv = uv * 2.0 - 1.0;
    uv *= vec2(iResolution.x / iResolution.y, 1.0);
	*/

    // as suggested :3
   	vec2 uv = (2.0 * (gl_FragCoord.xy-pos_correction.xy) - iResolution.xy) / iResolution.y;

    vec4 p = vec4(uv, 1.0, 1.0);

    vec3 l = vec3(p.xyz - vec3(0.0, 0.0, -3.));
   	vec3 n = normalize(p.xyz);

    vec3 lp = normalize(l - p.xyz);
    vec3 lc = vec3(dot(lp, n));
    vec3 color = vec3(1.0, 0.0, 0.0);

    vec4 r = normalize(p);
    vec4 o = vec4(
       	-1.0,
        2. * cos(iTime / 2.),
       	iTime,
        1.0
    );

    float t = trace(o, r, rotateX(iTime) * rotateY(iTime));

    float fog = 1.0 / (1.0 + t * t * 0.1);

    vec3 fc = vec3(fog * lc * color);

    gl_FragColor = vec4(fc, 1.0);

}
