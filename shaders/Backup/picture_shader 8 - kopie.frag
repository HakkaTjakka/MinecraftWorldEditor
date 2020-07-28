//copy
precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform int background_plot;
#define PI 3.141592653589793

vec2 uv2;
vec3 extra;
float diff2;


mat2 rotate(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat2(c, s, -s, c);
}

float disp(vec3 p) {
	float f = 16.;
	float t = iTime/3.0;
	return .08 * cos( p.x * f  + t ) * cos(p.z * f + t ) * cos( p.y * f + t ) ;
}

float map(vec3 p) {
	float d = 0.;
	float k = disp(p);
//	d = length(p) - .5;
    d = distance(p, vec3(0.0,0.0,0.0) ) - 0.5 ;
	return (d + k );
}

vec3 normal(vec3 p) {
	vec3 n, E = vec3(.005, 0., 0.);
	n.x = map(p + E.xyy) - map(p - E.xyy);
	n.y = map(p + E.yxy) - map(p - E.yxy);
	n.z = map(p + E.yyx) - map(p - E.yyx);
	return normalize(n);
}


float getVal(vec2 uv)
{
    return length( texture(texture_buffer,uv).xyz);
}

vec2 getGrad(vec2 uv,vec2 delta) {

     return vec2( getVal(uv+vec2(delta.x,0))-getVal(uv-vec2(delta.x,0)) , getVal(uv+vec2(0,delta.y))-getVal(uv-vec2(0,delta.y)) )/delta;
}

vec4 getpaint( vec2 gl_FragCoord,vec2 uv)
{
//	uv = (gl_FragCoord.xy) / iResolution.xy;
//	uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
    vec3 light = normalize(vec3(1,1,2));

    vec3 n = vec3(getGrad(uv,1.0/iResolution.xy),150.0);
    n=normalize(n);
    float diff=clamp(dot(n,light),0.5,1.0);
    float spec=clamp(dot(reflect(light,n),vec3(0,0,-1)),0.0,1.0);
    spec=pow(spec,36.0)*2.5;

//	vec4 col=texture(texture_buffer,uv);
	vec4 col=texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);
    return col;
}

void main() {
	vec3 kS = vec3(.7, .5, .9);
	float T = iTime/10.0;
	vec2 uv = 2.0*(gl_FragCoord.xy - pos_correction.xy - .5 * iResolution) / iResolution.y;
	vec3 kA = vec3(.0, .0, .0);
	vec3 kD = vec3(.4,
		       .15+cos(iTime*4.0+uv.y*25.0+cos(iTime*0.4+uv.x*10.0-uv.y*15.0))*0.45,
		       0.1+cos(iTime*5.1+uv.y*5.0+cos(iTime*0.33+uv.x*15.0-uv.y*25.0))*0.8);

	float ppy = .0+sin(T*.3+cos(T*0.3)*3.14)*.1;
	float ppx = .0+cos(T*.4+sin(T*0.5)*3.14)*.1;
	/*ray origin*/ vec3 ro = vec3(0.0,0.0, -1.0);
	/*ray direction*/vec3 rd = vec3(uv+vec2(ppx,ppy), 1.);
	float TT = T * 0.2 + sin(T*0.4)*3.14;
	vec3 light=vec3(-cos(TT)*1.7+3.14/4.0, 1., 3.14*-0.5+0.2*cos(TT)*1.4);

    uv2=rotate(iTime/9.0) * ( (  vec2(ppx,ppy) +  ( (gl_FragCoord.xy - pos_correction.xy ) / iResolution.xy) ) -0.5)+0.5;

//	vec2 uv3 = (gl_FragCoord.xy - pos_correction.xy) / iResolution.xy;
//    extra = normal(vec3(getGrad(uv3,1.0/iResolution.xy),150.0));

//    extra = length(texture(texture_buffer,uv2));
	float t = 0.;
    float m;
	for (int i = 0; i < 256; i++) {
		vec3 p = ro + rd * t;
        m=map(p);
		t += 0.9 * m;
 		if (m<0.0005) break;
	}
	vec3 p = ro + rd * t;
//	vec3 n = normal(p);
	vec3 n = normal(p);
	vec3 lp = normalize(light - p);
	float diff = 1.75 * clamp(dot(lp, n), 0., 1.);
	float spec = 9.5 * pow(max(dot(reflect(-lp, n), ro), 0.), 120.);

	if (m < 0.0005) {// my raymarch function must be messed?
        vec4 kD2;
//        vec2 uv=rotate(iTime/3.0) * ( (  vec2(ppx,ppy) +  ( (gl_FragCoord.xy - pos_correction.xy ) / iResolution.xy) ) -0.5)+0.5;
//        vec2 uv=rotate(iTime/3.0) * ( (  vec2(ppx,ppy) +  ( (gl_FragCoord.xy ) / iResolution.xy) ) -0.5)+0.5;

        if (background_plot==1) kD2 = getpaint(gl_FragCoord.xy,uv2);
//        if (background_plot==1) kD2 = texture(texture_buffer,uv2);
        else kD2 = getpaint(gl_FragCoord.xy,uv2.xy);
//        else kD2 = texture(texture_buffer,fract(uv2));
//        else kD2 = texture(texture_in,fract(uv));

		gl_FragColor = clamp(vec4(kA + kD2.xyz * diff + kS * spec, 1.), 0.0,1.0);
	} else {
		gl_FragColor = vec4(0.);
	}

    if (background_plot==1) {
        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
        gl_FragColor = mix(gl_FragColor,background,background.a);
    }
}
