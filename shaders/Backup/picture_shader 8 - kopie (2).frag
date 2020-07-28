//copy
precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 iResolution_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform int iFrame;
uniform int background_plot;
uniform vec2 pos_abs;
#define PI 3.141592653589793

const float camera_pos=-5.0;
vec2 uv2;
float extra=0.0;
float diff2;
const vec2 delta_buffer=1.0/iResolution_buffer.xy;
float T = iTime/3.0;

//https://www.johndcook.com/blog/2010/01/20/how-to-compute-the-soft-maximum/
float SoftMaximum(float x, float y)
{
	float maximum = max(x, y);
	float minimum = min(x, y);
	return maximum + log( 1.0 + exp(minimum - maximum) );
}

//https://www.johndcook.com/blog/2010/01/13/soft-maximum/
float smax( float a, float b, float k )
{
    return log( exp(a*k) + exp(b*k) ) / k;
}

//http://iquilezles.org/www/articles/smin/smin.htm
// polynomial smooth min (k = 0.1);
float sminCubic( float a, float b, float k )
{
    float h = max( k-abs(a-b), 0.0 );
    return min( a, b ) - h*h*h/(6.0*k*k);
}
// polynomial smooth min (k = 0.1);
float smin( float a, float b, float k )
{
    float h = max( k-abs(a-b), 0.0 );
    return min( a, b ) - h*h*0.25/k;
}
// power smooth min (k = 8);
float smin3( float a, float b, float k )
{
    a = pow( a, k ); b = pow( b, k );
    return pow( (a*b)/(a+b), 1.0/k );
}

// polynomial smooth min (k = 0.1);
float smin2( float a, float b, float k )
{
    float h = clamp( 0.5+0.5*(b-a)/k, 0.0, 1.0 );
    return mix( b, a, h ) - k*h*(1.0-h);
}

// exponential smooth min (k = 32);
float smin1( float a, float b, float k )
{
    float res = exp2( -k*a ) + exp2( -k*b );
    return -log2( res )/k;
}


float getVal(vec2 uv, vec2 delta)
{
    vec3 col=vec3(0.0);
    col+=texture(texture_buffer,uv).xyz*4.0;
    col+=texture(texture_buffer,uv+vec2(delta.x,0.0)        ).xyz*2.0;
    col+=texture(texture_buffer,uv+vec2(-delta.x,0.0)       ).xyz*2.0;
    col+=texture(texture_buffer,uv+vec2(0.0,delta.y)        ).xyz*2.0;
    col+=texture(texture_buffer,uv+vec2(0.0,-delta.y)       ).xyz*2.0;
    col+=texture(texture_buffer,uv+vec2(delta.x,delta.y)    ).xyz;
    col+=texture(texture_buffer,uv+vec2(-delta.x,delta.y)   ).xyz;
    col+=texture(texture_buffer,uv+vec2(delta.x,-delta.y)   ).xyz;
    col+=texture(texture_buffer,uv+vec2(-delta.x,-delta.y)  ).xyz;
    col=col/16.0;
    return length(col);
}

mat2 rotate(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat2(c, s, -s, c);
}

//http://jamie-wong.com/2016/07/15/ray-marching-signed-distance-functions/#signed-distance-functions
float intersectSDF(float distA, float distB) {
    return max(distA, distB);
}
float unionSDF(float distA, float distB) {
    return min(distA, distB);
}

float differenceSDF(float distA, float distB) {
    return max(distA, -distB);
}

float sdCappedCylinder( vec3 p, vec2 h )
{
  vec2 d = abs(vec2(length(p.xz),p.y)) - h;
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}

float sdSphere( vec3 p, float s )
{
  return length(p)-s;
}

mat4 rotateY(float theta) {
    float c = cos(theta);
    float s = sin(theta);

    return mat4(
        vec4(c, 0, s, 0),
        vec4(0, 1, 0, 0),
        vec4(-s, 0, c, 0),
        vec4(0, 0, 0, 1)
    );
}
mat4 rotateX(float theta) {
    float c = cos(theta);
    float s = sin(theta);

    return mat4(
        vec4(1, 0, 0, 0),
        vec4(0, c, -s, 0),
        vec4(0, s, c, 0),
        vec4(0, 0, 0, 1)
    );
}
mat4 rotateZ(float theta) {
    float c = cos(theta);
    float s = sin(theta);

    return mat4(
        vec4(c, -s, 0, 0),
        vec4(s, c, 0, 0),
        vec4(0, 0, 1, 0),
        vec4(0, 0, 0, 1)
    );
}

//float intersectSDF(float distA, float distB) {
//float unionSDF(float distA, float distB) {
//float differenceSDF(float distA, float distB) {

//http://iquilezles.org/www/articles/distfunctions/distfunctions.htm
float disp(vec3 p) {
	float t = T;
	float f = 10.0+sin(t*0.53+1.0)*2.0;
	p.xy=rotate(t*0.30)*p.xy;
	return (.08+sin(t*0.67+2)/12.0) * cos( p.x * f  ) * cos(p.z * f + t ) * cos( p.y * f + t ) ;
}

float map(vec3 p) {
	float d = 1.0E30;
	p.z=p.z+camera_pos; // keep object at origen.

//	d = distance(p, vec3(0.0,0.0,+2.0) ) - 0.5 + disp(p);
//	d = unionSDF(d,        sdSphere(p+vec3(0.0,0.0,0.0) ,0.5) + disp(p)/2.0)   ;
//	d = unionSDF(d,        distance(p, vec3(0.0,0.0,-0.5 ) )  - 0.2 + disp(p.zxy)/2.0 )   ;

//	d = unionSDF(d,        sdSphere(p+vec3(0.0,0.0,0.0),1.0) + disp(p) )   ;
	d = unionSDF(d,        sdSphere(p+vec3(0.0,0.0,0.0),1.0) )   ;

    vec3 cylinder = (rotateX(-T*0.10*2.0*PI) * vec4(p.x,p.y,p.z, 1.0)).xyz;
//	d = unionSDF( d,  sdCappedCylinder(cylinder,vec2(.50,1.15)) - 0.2 );

	d = smax( d ,- sdCappedCylinder(cylinder,vec2(.40,1.4)) - 0.0 , 8 );

//    cylinder = (rotateZ(PI/2.0) * vec4(p.x,p.y,p.z, 1.0)).xyz;
//	d = smax( d ,- sdCappedCylinder(cylinder,vec2(.40,1.4)) - 0.0 , 8 );

//    cylinder = (rotateY(PI/2.0) * vec4(p.x,p.y,p.z, 1.0)).xyz;
//	d = smax( d ,- sdCappedCylinder(cylinder,vec2(.40,1.4)) - 0.0 , 8 );

//	d = smin( d,  sdCappedCylinder(cylinder,vec2(.50,1.15)) - 0.2, 0.1 );

//	d = smax( d,  sdCappedCylinder(cylinder,vec2(.50,1.5)) - 0.0, 8.6 );
//	d = SoftMaximum( d,  sdCappedCylinder(cylinder,vec2(.50,1.5)) - 0.0 );

//	d = unionSDF(d,sdSphere(p,0.5));

//	d = min (d, distance(p, vec3( sin(iTime*0.27)/3.0 ,   sin(iTime*0.28)/3.0 , sin(iTime*0.29)/4.0 ) )   - 0.1*(2.0+sin(iTime*0.33)) + disp(p.xzy)/1.0 ) ;
//	d = min (d, distance(p, vec3( sin(iTime*0.28+1)/2.0 , sin(iTime*0.29)/3.0 , sin(iTime*0.30+1)/4.0 ) ) - 0.1*(2.0+sin(iTime*0.43)) + disp(p.yzx)/1.5 ) ;
//	d = min (d, distance(p, vec3( sin(iTime*0.29+2)/3.0 , sin(iTime*0.30)/2.0 , sin(iTime*0.31+2)/4.0 ) ) - 0.1*(2.0+sin(iTime*0.53)) + disp(p.yxz)/1.0 ) ;
//	d = min (d, distance(p, vec3( sin(iTime*0.30+3)/3.0 , sin(iTime*0.31)/3.0 , sin(iTime*0.32+3)/2.0 ) ) - 0.1*(2.0+sin(iTime*0.63)) + disp(p.zxy)/1.5 ) ;
//	d = min (d, distance(p, vec3( sin(iTime*0.31+4)/2.0 , sin(iTime*0.32)/3.0 , sin(iTime*0.33+4)/4.0 ) ) - 0.1*(2.0+sin(iTime*0.73)) + disp(p.zyx)/1.0 ) ;
//	d = min (d, distance(p, vec3( sin(iTime*0.32+5)/3.0 , sin(iTime*0.33)/2.0 , sin(iTime*0.34+5)/4.0 ) ) - 0.1*(2.0+sin(iTime*0.83)) + disp(p.xyz)/1.5 ) ;
//	d = min (d, distance(p, vec3( sin(iTime*0.33+6)/3.0 , sin(iTime*0.34)/3.0 , sin(iTime*0.35+6)/3.0 ) ) - 0.1*(2.0+sin(iTime*0.93)) + disp(p.xzz)/1.5 ) ;
	return d;

}

vec3 normal(vec3 p) {
	vec3 n, E = vec3(.005, 0., 0.);
	n.x = map(p + E.xyy) - map(p - E.xyy);
	n.y = map(p + E.yxy) - map(p - E.yxy);
	n.z = map(p + E.yyx) - map(p - E.yyx);
	return normalize(n);
}

float getVal2(vec2 uv)
{
    return length( texture(texture_buffer,uv).xyz);
}

vec2 getGrad(vec2 uv,vec2 delta) {

     return vec2(  getVal(uv+vec2(delta.x,0),delta) - getVal(uv-vec2(delta.x,0),delta) , getVal(uv+vec2(0,delta.y),delta) - getVal(uv-vec2(0,delta.y),delta) )/delta;
//     return vec2( getVal2(uv+vec2(delta.x,0))-getVal2(uv-vec2(delta.x,0)) , getVal2(uv+vec2(0,delta.y))-getVal2(uv-vec2(0,delta.y)) )/delta;
}

vec4 getpaint( vec2 gl_FragCoord,vec2 uv)
{
//	uv = (gl_FragCoord.xy) / iResolution.xy;
//	uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
//    vec3 light = normalize(vec3(1,1,2));
//	float T = iTime/10.0;
	//float TT = T * 0.2 + sin(T*0.4)*3.14;
//	vec3 light=normalize(vec3(-cos(TT)*1.7+3.14/4.0, 1., 3.14*-0.5+0.2*cos(TT)*1.4));
//	vec3 light=normalize(vec3(-cos(TT)*1.7+3.14/4.0, 1., 3.14*-0.5+0.2*cos(TT)*1.4));
    vec3 light = normalize(vec3(1,1,2));

    vec3 n = vec3(getGrad(uv,1.0/iResolution_buffer.xy),150.0);
    n=normalize(n);

    float diff=clamp(dot(n,light),0.5,1.0);
    float spec=clamp(dot(reflect(light,n),vec3(0,0,-1)),0.0,1.0);
    spec=pow(spec,36.0)*1.5;

//	vec4 col=texture(texture_buffer,uv);
	vec4 col=texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2;
//	vec4 col=texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);
    return col;
}

void main() {
	vec3 kS = vec3(.7, .5, .9);
	vec3 kA = vec3(0.0, .0, .0);

//	float ppy = .0+sin(T*.3+cos(T*0.3)*3.14)*.1;
//	float ppx = .0+cos(T*.4+sin(T*0.5)*3.14)*.1;
	float ppy = .0;
	float ppx = .0;
	float TT = T * 0.071 + sin(T*0.1334)*3.14;
	vec3 light=vec3(-cos(TT)*1.7+3.14/4.0, 1., 3.14*-0.5+0.2*cos(TT)*1.4+camera_pos); // zzzzz 2.0

	vec3 ro = vec3(0.0,0.0, -1.0);

	vec2 uv = .5*(gl_FragCoord.xy - pos_correction.xy - .5 * iResolution) / iResolution.y;
	vec3 rd = vec3(uv+vec2(ppx,ppy)*2.0, 1.0);





	float t = 0.;
    float m;
    vec3 p;
	for (int i = 0; i < 512; i++) {
		p = ro + rd * t;
        m=map(p);
		t += 0.9 * m;
 		if (m<0.0001) break;
	}

//    uv2= vec2(1.0,1.0)*  (( (   ( p.xy*1.2*vec2(1.0,-1.0) +  vec2(ppx,ppy) - t/1.5  ) ) -0.5) + 0.25);
//    extra = getVal2(uv2,1.0/iResolution_buffer);

	vec3 n = normal( p );
	vec3 lp = normalize(light - p);
	float diff = 1.75 * clamp(dot(lp, n), 0., 1.);
	float spec = (9.5) * pow(max(dot(reflect(-lp, n), ro), 0.), 120.);

//    uv2=rotate(iTime/14.0) * ( (   ( p.xy*2.0 + (gl_FragCoord.xy - pos_correction.xy ) / iResolution.xy) ) -0.5)+0.5;
//    extra = getVal(uv2);

	if (m < 0.0001) {// my raymarch function must be messed?
        vec2 calc=p.xy*1.2*vec2(1.0,-1.0)*(1.0+p.z/1.50) +  vec2(ppx,ppy) - (t)/2.5;
        vec2 uv2= vec2(.5,.5) * ( calc )  +  vec2(0.0,-(T+calc.y)*0.20);

        vec2 uv_adj=uv2/(1.0+2.0*(-camera_pos+1.0)/iResolution.y);
        vec4 kD = vec4(.4, .15+cos(T*4.0+uv_adj.y*25.0+cos(T*0.4+uv_adj.x*10.0-uv_adj.y*15.0))*0.45, 0.1+cos(T*5.1+uv_adj.y*5.0+cos(T*0.33+uv_adj.x*15.0-uv_adj.y*25.0))*0.8, 1.0);

//        if (background_plot==1) kD = getpaint(gl_FragCoord.xy,uv2.xy);
//        if (background_plot==1) kD = texture(texture_buffer,uv2.xy);

//        else kD = getpaint(gl_FragCoord.xy,uv2.xy);
//        else kD = texture(texture_buffer,uv2.xy);

//        else kD2 = texture(texture_in,fract(uv2.xy));

		gl_FragColor = clamp(vec4(kA + kD.xyz * diff + kS * spec, 1.), 0.0,1.0);
	} else {
		gl_FragColor = vec4(0.);
	}

    if (background_plot==1) {
        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
        gl_FragColor = mix(gl_FragColor,background,background.a);
    }
}

//        vec2 uv=rotate(iTime/3.0) * ( (  vec2(ppx,ppy) +  ( (gl_FragCoord.xy - pos_correction.xy ) / iResolution.xy) ) -0.5)+0.5;
//        vec2 uv=rotate(iTime/3.0) * ( (  vec2(ppx,ppy) +  ( (gl_FragCoord.xy ) / iResolution.xy) ) -0.5)+0.5;
//        vec2 uv2= ( (  vec2(ppx,ppy) +  ( (gl_FragCoord.xy - pos_correction.xy ) / iResolution.xy) ) -0.5)+0.5+vec2(0.0,iTime*0.20);
