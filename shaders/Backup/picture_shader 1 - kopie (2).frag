//copy
//precision highp float;
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

const float camera_pos=-10.0;
vec2 uv2;
vec2 uv;
float diff2;
vec2 delta_buffer;
float T;
vec2 Resolution;
int horizon=0;
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
//    return length(texture(texture_buffer,uv).xyz);
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

mat4 rotateXYZ(float theta_x, float theta_y, float theta_z) {
    float c_x = cos(theta_x);
    float s_x = sin(theta_y);
    float c_y = cos(theta_x);
    float s_y = sin(theta_y);
    float c_z = cos(theta_x);
    float s_z = sin(theta_y);

    return mat4(
        vec4(1, 0, 0, 0),
        vec4(0, c_x, -s_x, 0),
        vec4(0, s_x, c_x, 0),
        vec4(0, 0, 0, 1)
    ) *
    mat4(
        vec4(c_y, 0, s_y, 0),
        vec4(0, 1, 0, 0),
        vec4(-s_y, 0, c_y, 0),
        vec4(0, 0, 0, 1)
    ) *
    mat4(
        vec4(c_z, -s_z, 0, 0),
        vec4(s_z, c_z, 0, 0),
        vec4(0, 0, 1, 0),
        vec4(0, 0, 0, 1)
    );
}

mat4 rotateZYX(float theta_x, float theta_y, float theta_z) {
    float c_x = cos(theta_x);
    float s_x = sin(theta_y);
    float c_y = cos(theta_x);
    float s_y = sin(theta_y);
    float c_z = cos(theta_x);
    float s_z = sin(theta_y);

    return mat4(
        vec4(c_z, -s_z, 0, 0),
        vec4(s_z, c_z, 0, 0),
        vec4(0, 0, 1, 0),
        vec4(0, 0, 0, 1)
    ) *
    mat4(
        vec4(c_y, 0, s_y, 0),
        vec4(0, 1, 0, 0),
        vec4(-s_y, 0, c_y, 0),
        vec4(0, 0, 0, 1)
    ) *
    mat4(
        vec4(1, 0, 0, 0),
        vec4(0, c_x, -s_x, 0),
        vec4(0, s_x, c_x, 0),
        vec4(0, 0, 0, 1)
    );
}

mat4 projection(float theta) {

    return mat4(
        vec4(1, 0, 0, 0),
        vec4(0, 1, 0, 0),
        vec4(0, 0, 1, 0),
        vec4(0, 0, 1/theta, 1)
    );
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
float disp(vec3 p,float n) {
	float t = T+n;
//	float f = 16.0+sin(t*0.53+1.0+n)*2.0;
	float f = 4.0;
//	p.xy=rotate(t*0.30)*p.xy;
	return (.18) * cos( p.x * f + t ) * cos(p.z * f + t ) * cos( p.y * f + t ) ;
//	return (.08+sin(t*0.67+2)/50.0) * cos( p.x * f  ) * cos(p.z * f + t ) * cos( p.y * f + t ) ;
}

//mat4 rotje=rotateXYZ(0.0,-T*0.1*2.0*PI,0.0);
//mat4 rotje2=rotateZYX(0.0,-T*0.1*2.0*PI,0.0);

mat4 rotje=rotateX(-T*0.1*2.0*PI)*rotateY(-T*0.1*2.0*PI)*rotateZ(-T*0.1*2.0*PI);
mat4 rotje2=rotateZ(T*0.1*2.0*PI)*rotateY(T*0.1*2.0*PI)*rotateX(T*0.1*2.0*PI);

//mat4 rotje=rotateX(-T*0.1*2.0*PI)*rotateY(0.0)*rotateZ(0.0);
//mat4 rotje2=rotateZ(0.0)*rotateY(0.0)*rotateX(T*0.1*2.0*PI);

//mat4 rotje=rotateX(0.5)*rotateY(0.5)*rotateZ(-T*0.1*2.0*PI);
//mat4 rotje2=rotateZ(T*0.1*2.0*PI)*rotateY(5.0)*rotateX(0.5);

//mat4 rotje=rotateX(-T*0.1*2.0*PI)*rotateY(0.0)*rotateZ(-T*0.1*2.0*PI);
//mat4 rotje2=rotateZ(T*0.1*2.0*PI)*rotateY(0.0)*rotateX(T*0.1*2.0*PI);

//mat4 rotje=rotateX(0.0)*rotateY(-T*0.1*2.0*PI)*rotateZ(-T*0.1*2.0*PI);
//mat4 rotje2=rotateZ(T*0.1*2.0*PI)*rotateY(T*0.1*2.0*PI)*rotateX(0.0);

//mat4 rotje2=rotateZYX(T*0.1*2.0*PI,T*0.1*2.0*PI,T*0.1*2.0*PI);
//mat4 rotje=rotateXYZ(-T*0.1*2.0*PI,-T*0.1*2.0*PI,-T*0.1*2.0*PI);
//mat4 rotje2=rotateZYX(T*0.1*2.0*PI,T*0.1*2.0*PI,T*0.1*2.0*PI);

float map(vec3 p) {
	float d = 1.0E10;
	horizon=0;
//	float d = 0.0;
	p.z=p.z+camera_pos; // keep object at origen.
//	d = distance(p, vec3(0.0,0.0,+2.0) ) - 0.5 + disp(p);
//	d = unionSDF(d,        sdSphere(p+vec3(0.0,0.0,0.0) ,0.5) + disp(p)/2.0)   ;
//	d = unionSDF(d,        distance(p, vec3(0.0,0.0,-0.5 ) )  - 0.2 + disp(p.zxy)/2.0 )   ;

//	d = unionSDF(d,        sdSphere(p+vec3(0.0,0.0,0.0),1.0) + disp(p) )   ;

//a	d = unionSDF(d,        sdSphere(p+vec3(0.0,0.0,0.0),1.0) )   ;

//    vec3 cylinder = (rotateX(-T*0.10*2.0*PI) * vec4(p.x,p.y,p.z, 1.0)).xyz;
//	d = unionSDF( d,  sdCappedCylinder(cylinder,vec2(.50,1.15)) - 0.2 );

//	d = smax( d ,- sdCappedCylinder(cylinder,vec2(.40,1.4)) - 0.0 , 8 );


//  vec3 cylinder = (rotateX(T) * vec4(p.x,p.y,p.z, 1.0)).xyz;
//	d = sdCappedCylinder(cylinder,vec2(.50,3.0)) - 0.3 ;

/*
    cylinder = (rotateZ(0.5*PI) * rotje2 * vec4(p.x,p.y,p.z, 1.0)).xyz;
	float d2 = sdCappedCylinder(cylinder,vec2(.50,2.0)) - 0.3 ;

    d = smin( d, d2, .2);

    cylinder = (rotateZ(0.5*PI) * rotateY(0.5*PI) * rotje2 * vec4(p.x,p.y,p.z, 1.0)).xyz;
	d2 = sdCappedCylinder(cylinder,vec2(.30,2.0)) - 0.3 ;

    d = smax( d, -d2, 8);

//    d = smin( d, d2, .2);

*/
//    d2 = 1.0E10;

//    for (int x=0; x<10; x++) {
//        float ff=float(x);
//        d = smin(d, sdSphere(p + (  rotje * vec4( sin(T*0.354*ff), sin(T*0.452*ff),sin(T*0.399*ff)  ,  1.0)).xyz    ,
//                             2.0 ) +disp(p,1.0) // size sphere
//                  ,.4)   ;
//    }

//	d =  smax ( sdSphere(p+   vec3(0.0,0.0,0.0),2.0), -d ,8);
	d =  disp(p,1.0)/2.0+sdSphere(p+   vec3(0.0,0.0,0.0),2.0) ;
    for (int x=0; x<10; x++) {
        float ff=float(x);
        float where=mod(T*1.22+ff*ff,2*PI);
        if ((where<PI*0.5 || (where>PI && where<1.5*PI)) ) {
                float d2 = ( 1.0-(0.5+sin(2.0*where+.5*PI)/2.0) )*disp(p,1.0) +sdSphere(p +  ( rotateX(ff+T*0.33) * rotateY(ff+T*0.45) * rotateZ(ff+T*0.56) * vec4( 0.0+sin(where)*2.0, 0.0+sin(where)*2.0,  0.0+sin(where)*4.0  ,  1.0  )).xyz    ,   1.33*( 1.0-(0.5+sin(2.0*where+1.5*PI)/2.0) ));    d = smin(d,d2,0.3);
        }
    }

//    d = smax(d,-d2,12);

//	d=d+extra;

//    for (int x=0; x<5; x++) {
//        float ff=float(x);
//        d = smin(d, sdSphere(p + ( vec4( sin(T*0.345+ff*1.2)*2.5,    sin(T*0.4+PI+ff*2.332)*1.8,      -cos(T*0.532+PI/1.5  +ff*1.662   )*2.1,  1.0)).xyz    ,
//                             0.5+sin(ff+T)/4.0 ) // size sphere
//                  ,.8+sin(ff+T*0.778)*0.2)   ;
//    }


//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.4+PI/2.0)*2.0,  0.0,                             -cos(T*0.432+PI/2     )*2.0,  1.0)).xyz    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.5+PI)*2.0,      0.0,                             -cos(T*0.33423+PI       )*2.0,  1.0)).xyz    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.6+PI*1.5)*2.0,  0.0,                             -cos(T*0.5433+PI*1.5   )*2.0,  1.0)).xyz    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.33)*2.0,         0.0,                             -cos(T*0.22323          )*2.0,  1.0)).xyz    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( 0.0,                     sin(T*0.31+PI/2.0   )*2.0,       -cos(T*0.3233+PI*1.5   )*2.0,  1.0)).xyz    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( 0.0,                     sin(T*0.34+PI*1.5   )*2.0,       -cos(T*0.43453          )*2.0,  1.0)).xyz    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.44+PI/2.0)*2.0,  0.0,                             -cos(T*0.3+PI/2     )*2.0,  1.0)).yxz    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.55+PI)*2.0,      0.0,                             -cos(T*0.32343+PI       )*2.0,  1.0)).zyx    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.22+PI*1.5)*2.0,  0.0,                             -cos(T*0.5433+PI*1.5   )*2.0,  1.0)).yzx    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( sin(T*0.29)*2.0,         0.0,                             -cos(T*0.43          )*2.0,  1.0)).xzy    ,0.5) ,.5)   ;
//	d = smin(d, sdSphere(p+ (rotje * vec4( 0.0,                     sin(T*0.35+PI/2.0   )*2.0,       -cos(T*0.323+PI*1.5   )*2.0,  1.0)).zxy    ,0.5) ,.5)   ;

    d = min(1.0E10 , d );
    if (d>= 1.0E10) horizon=1;
//    if (d==1.0E10) return 0.0;


//    d = smax( d, -d2, 8);

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

/*
	float n1,n2,n3;

	n1=map(p);
	n2=map(p - 1.0 * E.xyy);
	n3=map(p + 1.0 * E.xyy);
	if (abs(n1-n2)>abs(n3-n1)) {n.x=(n3 - n1)*2.0;  }
	else n.x=(n1 - n2)*2.0;

	n2=map(p - 1.0 * E.yxy);
	n3=map(p + 1.0 * E.yxy);
	if (abs(n1-n2)>abs(n3-n1)) {n.y=(n3 - n1)*2.0;  }
	else n.y=(n1 - n2)*2.0;

	n2=map(p - 1.0 * E.yyx);
	n3=map(p + 1.0 * E.yyx);
	if (abs(n1-n2)>abs(n3-n1)) {n.z=(n3 - n1)*2.0;  }
	else n.z=(n1 - n2)*2.0;
*/

//	n.x = (map(p )                 - map(p - 1.0 * E.xyy)  )*2.0;
//	n2 = (map(p + 1.0 * E.xyy)    - map(p)                )*2.0;
//    n.x=min(n1,n2);

//	n.y = (map(p ) - map(p - 1.0 * E.yxy))*2.0;
//	if (abs(n.y-n.x) > 0.1) n.y = (map(p + 1.0 * E.yxy) - map(p))*2.0 ;

//	n.z = (map(p ) - map(p - 1.0 * E.yyx))*2.0;
//	if (abs(n.z-n.x) > 0.1) n.z = (map(p + 1.0 * E.yyx) - map(p))*2.0 ;

//	n.x = min( (map(p ) - map(p - 1.0 * E.xyy))*2.0      ,      (map(p + 1.0 * E.xyy) - map(p))*2.0 );
//	n.y = min( (map(p ) - map(p - 1.0 * E.yxy))*2.0      ,      (map(p + 1.0 * E.yxy) - map(p))*2.0 );
//	n.z = min( (map(p ) - map(p - 1.0 * E.yyx))*2.0      ,      (map(p + 1.0 * E.yyx) - map(p))*2.0 );

//	n.x = map(p + E.xyy) - map(p - E.xyy); if (abs(n.x)>0.1) n.x = (map(p ) - map(p - 1.0 * E.xyy))*2.0; if (abs(n.x)>0.1) n.x = (map(p + 1.0 * E.xyy) - map(p))*2.0;
//	n.y = map(p + E.yxy) - map(p - E.yxy); if (abs(n.y)>0.1) n.y = (map(p ) - map(p - 1.0 * E.yxy))*2.0; if (abs(n.y)>0.1) n.y = (map(p + 1.0 * E.yxy) - map(p))*2.0;
//	n.z = map(p + E.yyx) - map(p - E.yyx); if (abs(n.z)>0.1) n.z = (map(p ) - map(p - 1.0 * E.yyx))*2.0; if (abs(n.z)>0.1) n.z = (map(p + 1.0 * E.yyx) - map(p))*2.0;

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
//	vec4 col=texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2;
	vec4 col=texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);
    return col;
}

int back=0;
float t;

//vec4 main2(vec2 Coord, float zoom) {
void main() {
    delta_buffer=1.0/iResolution_buffer.xy;
    T = iTime/4.0;
    Resolution=iResolution;
    back=0;
    vec4 Color=vec4(0.0);
    vec2 Coord=gl_FragCoord.xy;
    float zoom=1.0;
	vec3 kS = vec3(.7, .5, .9);
	vec3 kA = vec3(0.0, .0, .0);

//	float ppy = .0+sin(T*.3+cos(T*0.3)*3.14)*.1;
//	float ppx = .0+cos(T*.4+sin(T*0.5)*3.14)*.1;
	float ppy = .0;
	float ppx = .0;
	float TT = T * 0.71 + sin(T*0.1334)*3.14;
//	vec3 light=vec3(-cos(TT)*15.7+1.0, 5., -2.5+cos(TT)*1.0+camera_pos); // zzzzz 2.0
	vec3 light=vec3(-pos_abs.x*30, pos_abs.y*30, 5.5+camera_pos); // zzzzz 2.0

    vec3 ro = vec3(0.0,0.0, -1.0);

	uv = zoom*(Coord.xy - pos_correction.xy - .5 * Resolution) / Resolution.y;
	vec3 rd = vec3(uv+vec2(ppx,ppy)*2.0, 1.0);



	t = 0.0;
    vec3 p;
    p = ro + rd * t;
    float m=map(p);
	for (int i = 0; i < 512; i++) {
        m=map(p);
//        if (m==1.0E10) break;
        if (horizon==1) break;
        t += 0.9 * m;
        p = ro + rd * t;
 		if (m<0.0001) break;
	}

    uv2= vec2(1.0,-1.0)*  (( (   ( p.xy*1.2*vec2(1.0,-1.0) +  vec2(ppx,ppy) - t/1.5  ) ) -0.5) + 0.25);
//    extra = getVal2(uv2,1.0/iResolution_buffer);


//    uv2=rotate(iTime/14.0) * ( (   ( p.xy*2.0 + (Coord.xy - pos_correction.xy ) / iResolution.xy) ) -0.5)+0.5;
//    extra = getVal(uv2);

//	if (maximum==0) {// my raymarch function must be messed?
	if (horizon==0 || m<0.0001) {// my raymarch function must be messed?
//	if (m!=1.0E10 || m<0.001) {// my raymarch function must be messed?
//	if (m < 0.00001 || m!=1.0E10) {// my raymarch function must be messed?

        vec4 kD=vec4(0.0);

//        col.xyz = raymarch(ro,rd,tmm.xy).xyz;
//        vec3 nor=(ro+t*rd)/2.;
//        vec3 nor=(n)/2.;
//        vec2 rot= -vec3(   (rotateX(-T*0.1*2.0*PI)*vec4(p.x,p.y,p.z,1.0)).xyz + (rotateY(-T*0.1*2.0*PI)*vec4(p.x,p.y,p.z,1.0)).xyz + (rotateZ(-T*0.1*2.0*PI)*vec4(p.x,p.y,p.z,1.0)).xyz ).xy;

//        mat2 rot=rotate( -T*0.1*2.0*PI * (cos(-T*0.1*2.0*PI)/2.0+1.0) ); //* rotate( -T*0.1*2.0*PI * (sin(-T*0.1*2.0*PI+PI*1.5)/2.0+1.0) ) * rotate( -T*0.1*2.0*PI * (sin(-T*0.1*2.0*PI+PI*0.5)/2.0+1.0) ) ;
        //vec3 rot= (rotje2 * vec4(uv.x,-uv.y  ,t,1.0)).xyz;
//        rot=normalize(rot);
//        mat2 rot2=rotate(atan(rot.y,rot.x));
//        float at=-atan(rot.z,rot.x);
//        mat2 rot2=rotate(at+(sign(rot.z)+1.0)*PI/2.0); // * rotate(-atan(rot.y,rot.z)) * rotate(-atan(rot.y,rot.x));

//        mat2 rot2= rotate(-T*0.1*1.0*rot.x + -T*0.1*1.0*rot.y + -T*0.1*1.0*rot.z);
//        nor = reflect(rd, nor);
//        float fre = pow(.5+ clamp(dot(nor,rd),0.0,1.0), 3. )*4.3;
//        vec2 offset=vec2(0.0,(T*0.1*1.0));  //xyz
//        vec2 offset=vec2(0.0,0.0);  //xyz
//        kD.xyz += texture(texture_buffer, offset+(nor.xy)/20.0 * rot2 ).rgb * fre;


//        vec3 rot= (-rotje * vec4(p.x,p.y,p.z,1.0)).xyz; //rotate(T*0.1*2.0*PI)*
//        vec2 offset=vec2(0.0,-T*0.1*1.0);
//        vec2 offset=vec2(0.0,-T*0.1*1.0);     //xz

//        vec2 offset=vec2(-T*0.1*1.0,0.0);       //yz
        vec2 offset=vec2(1.5,1.5);       //yz

//        vec2 offset=vec2(-T*0.12*1.0,-T*0.1*1.0);  //xyz

//        vec2 offset=vec2(0.0);
//        mat2 rot=rotate( cos(-T*0.1*2.0*PI)*2.0*PI/3.0 - sin(-T*0.1*2.0*PI)*2.0*PI/3.0 - sin(-T*0.1*2.0*PI)*2.0*PI/3.0  );   //xz
//        mat2 rot=rotate( (T*0.1*1.0)*(rotje.x));
//        vec2 rot=vec2(  (-rotje2*vec4(p.x,p.y,t/10.0,1.0)).xy );

//        mat2 rot=rotate(-rotje2.x)*rotate(-rotje2.y)*rotate(-rotje2.z);

//        vec3 prot=(rotje*vec4(p,1.0)).xyz;
        vec3 n = normal( p );
        vec2 calc=(p.xy*vec2(0.6,0.6)*(1.1+p.z/1.50) +  vec2(ppx,ppy)  - (t)/2.5);
        vec2 uv2= vec2(1.1,1.1) * ( calc /(1.0+ p.xy/10.0) )  +  vec2(0.0,-(calc.y)*0.20)+ offset;
//        vec2 uv_adj;

//        uv_adj=uv2/(1.0+2.0*(-camera_pos+1.0)/Resolution.y);
//        uv_adj=uv2/(1.0+sqrt(-camera_pos + 1.0)/iResolution.y)*vec2(0.1,0.1) ;
//        kD = vec4(.4, .15+cos(T*4.0+uv_adj.y*25.0+cos(T*0.4+uv_adj.x*10.0-uv_adj.y*15.0))*0.45, 0.1+cos(T*5.1+uv_adj.y*5.0+cos(T*0.33+uv_adj.x*15.0-uv_adj.y*25.0))*0.8, 1.0);
//        kD = vec4(0.0,0.0,0.0, 1.0);

//            vec2 uv_adj=(uv2/(1.0+sqrt(-camera_pos + 1.0)/iResolution_buffer.y)*vec2(0.05,0.05) * rotate(T*0.03)+ vec2(sin(T*0.042),cos(T*0.033)));

        vec2 uv_adj=(uv2/(1.0+sqrt(-camera_pos/2.0 + 1.0)/iResolution_buffer.y)*vec2(0.04,0.04)  )*vec2(1.0,-1.0)+ vec2(-0.3,1.4);

//        vec2 uv_adj=0.1*(rotje*vec4(p-ro,1.0)).xy;
//        vec2 uv_adj=0.1*(projection(t)*rotje*vec4(p,1.0)).xy;
//        vec2 uv_adj=1.1*(rotje*vec4(p,1.0)).xy;


//      vec3 L = normalize(light);
//      vec4 color = texture2D(texture_buffer, uv);
//      float NdotL = dot(L, n);
//      float diffuse = 0.5 * NdotL + 0.5;
//      gl_FragColor = vec4(1.0,1.0,1.0,1.0)*vec4(vec3(diffuse),1.0);
//      return;

//        kD=vec4(1.0,1.0,0.0,1.0);
//        vec2 angles=vec2( 0.5+atan(p.z,p.x)/(2.0*PI) ,0.5-asin(p.y)/PI) ;
//        vec2 uv_adj=vec2(mod(angles.y,2.0*PI)/2.0*PI, (PI-angles.x)/PI );


//        vec3 norm=(rotateY(T*.2)*vec4(n,1.0)).xyz;
//        vec2 uv_adj=2.0*vec2( 0.5+atan(norm.x,norm.z)/(2.0*PI) ,0.5-asin(norm.y)/PI) ;

//        vec2 uv_adj=vec2( 0.5+atan(norm.x,norm.z)/(2.0*PI) ,0.5-asin(norm.y)/PI) ;
//        uv_adj=vec2(mod(uv_adj.y,2.0*PI)/2.0*PI, (PI-uv_adj.x)/PI );

//        vec3 e=normalize(  (rotje*vec4(p,1.0) ).xyz);
//        vec3 r=reflect(e,n);
//        float m= 2. * sqrt(   pow( r.x, 2. ) +   pow( r.y, 2. ) +   pow( r.z + 1., 2. )  );
//        vec2 vN = r.xy / m + .5;
//        vec2 uv_adj=vN;

//        if (sin(p.x*10)>0.0) kD=vec4(1.0,0.0,0.0,1.0);
//        else kD=vec4(0.0,1.0,1.0,1.0);

//        if (background_plot==1) kD = getpaint(Coord.xy,uv_adj.xy);
//        if (background_plot==1) kD = getpaint(Coord.xy,uv_adj.xy);
//        if (background_plot==1) kD = texture(texture_buffer,uv2.xy);
//        if (background_plot==1) kD = texture(texture_buffer,uv_adj.xy);

//        else kD = getpaint(Coord.xy,uv_adj.xy);
//        else kD = texture(texture_buffer,uv2.xy);
//        else kD = texture(texture_buffer,uv_adj.xy);

//        else kD2 = texture(texture_in,fract(uv2.xy));

//        kD=vec4( kD.x+sin( (p.x+p.z)/3.0+T*0.24)/4.0, kD.y+sin((p.y+p.x)/3.0+T*0.35)/4.0, kD.z+sin((p.z+p.y)/3.0+T*0.29)/4.0,1.0);

        vec3 n2 = vec3(getGrad(uv_adj,-1.0/iResolution_buffer.xy),-150.0);
        n2=normalize(n2)*vec3(1.0,1.0,1.0);

//        vec3 light2 = normalize(vec3(1,1,2));
//        float diff2=clamp(dot(n2,light2),0.5,1.0);
//        float spec2=clamp(dot(reflect(light2,n2),ro),0.0,1.0);
//        spec2=pow(spec2,36.0)*1.5;
        kD = texture(texture_buffer,uv_adj  );
//        kD = texture(texture_buffer,uv_adj)*vec4(vec3(diff2),1.0)+vec4(vec3(spec2),0.0);

        n=n-(n-n2)/1.0;
//        n=n2;

//    float diff=clamp(dot(n,light),0.5,1.0);

//        n=normalize(n+n2*3.0);
        vec3 lp = normalize(light - p);
        float diff = 1.0 * clamp(dot( n,lp), 0.0, 1.);
        float spec = (9.5) * pow(max(dot(reflect(-lp, n), ro), 0.), 120.);

//		Color = clamp(vec4(kA + kD.xyz * (diff ) + kS *( spec ), 1.0), 0.0,1.0);
		Color = clamp(vec4(kA + kD.xyz * (diff ) + kS * ( spec ), 1.0), 0.0,1.0);
	} else {
		Color = vec4(0.0);
//        Color = vec4(.4, .415+cos(T*.7+uv.y*25.0+cos(T*0.4+uv.x*10.0-uv.y*15.0))*0.45, 0.1+cos(T*1.33+uv.y*5.0+cos(T*0.33+uv.x*15.0-uv.y*25.0))*0.8, 1.0)*2.0;
//        T=T*2.5;Color += vec4( .45+cos(T*0.5+uv.y*25.0+cos(T*0.4+uv.x*10.0-uv.y*15.0))*0.45, 0.1+cos(T*1.1+uv.y*5.0+cos(T*0.73+uv.x*15.0-uv.y*25.0))*0.8,.4, 1.0)*2.0;
        back=1;
	}

    if (background_plot==1) {
        vec4 background=texture(texture_in,(Coord.xy/vec2(1920,1080)));
        Color = mix(Color,background,background.a);
    }
    gl_FragColor=Color;
//    return Color;
}
/*
#define AA 1

void main2() {
    Resolution=iResolution;
    float t1=0.0;
    float tt=T;
    if (AA<=1) {
        gl_FragColor=main2(gl_FragCoord.xy,1.0);
//        gl_FragColor=main2(gl_FragCoord.xy+vec2(sin(tt*0.12+PI)*Resolution.x/6.0,cos(tt*0.12+PI)*Resolution.y/6.0),1.0);
//        t1=t;
//        t=0.0;
//        T+=343.34;
//        vec4 Color2=main2(gl_FragCoord.xy+vec2(sin(tt*0.12+PI/2.0)*Resolution.x/6.0,cos(tt*0.12+PI/2.0)*Resolution.y/6.0),1.0);
//        if (t<t1) { gl_FragColor=Color2; t1=t; }
//        T+=343.34;
//        Color2=main2(gl_FragCoord.xy+vec2(sin(tt*0.12+PI*1.5)*Resolution.x/6.0,cos(tt*0.12+PI*1.5)*Resolution.y/6.0),1.0);
//        if (t<t1) { gl_FragColor=Color2; t1=t; }
//        T+=343.34;
//        Color2=main2(gl_FragCoord.xy+vec2(sin(tt*0.12)*Resolution.x/6.0,cos(tt*0.12)*Resolution.y/6.0),1.0);
//        if (t<t1) { gl_FragColor=Color2; t1=t; }

//        if (back==1 && back1==1) {
//            T=T+44.24;
//            t=0.0;
//            gl_FragColor=main2(gl_FragCoord.xy+vec2(sin(tt*0.12+PI*1.5)*Resolution.x/4.0,cos(tt*0.12+PI*1.5)*Resolution.y/4.0),2.0-sin(tt*0.12+PI*1.5));
//        }
    }
    else {
        gl_FragColor=vec4(0.0);
//        Resolution*=AA;
        for (int x=0;x<AA; x++)
            for (int y=0;y<AA; y++)
                gl_FragColor+=main2(gl_FragCoord.xy + vec2( float(x)/(float(AA)) , float(y)/float(AA) ) , 1.0);
        gl_FragColor/=(AA*AA);
    }
}
*/
