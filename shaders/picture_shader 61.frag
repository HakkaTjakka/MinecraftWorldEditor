//paint
//precision highp float;

uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform int iFrame;

// Created by Eivind Magnus Hvidevold emnh/2016.
// Reaction-diffusion by Flexi.
// Raymarching by inigo quilez - iq/2013.
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.

float sdSphere( vec3 p, float s )
{
    return length(p)-s;
}

//----------------------------------------------------------------------

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float hash( float n ) { return fract(sin(n)*753.5453123); }

float noise( vec3 x )
{
    vec3 p = floor(x);
    vec3 f = fract(x);
    f = f*f*(3.0-2.0*f);

    float n = p.x + p.y*157.0 + 113.0*p.z;
    return mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
                   mix( hash(n+157.0), hash(n+158.0),f.x),f.y),
               mix(mix( hash(n+113.0), hash(n+114.0),f.x),
                   mix( hash(n+270.0), hash(n+271.0),f.x),f.y),f.z);
}

vec2 map(vec3 pos) {
    vec3 o = pos;

    pos = pos - vec3(0.0, -1.5, 0.0);
//    vec2 mo = iMouse.xy/iResolution.xy;
    vec2 mo = iMouse.xy;
    float ms = 3.14 * 2.0;
    mat4 mrx = rotationMatrix(vec3(1.0, 0.0, 0.0), mo.y * ms);
    mat4 mry = rotationMatrix(vec3(0.0, 1.0, 0.0), mo.x * ms);
    mat4 mrt = rotationMatrix(vec3(0.0, 1.0, 0.0), sin(float(iFrame)/10 / 10.0));

    pos = (vec4(pos, 1.0) * mrx * mry * mrt).xyz;

    // uv mapping
    vec3 p = normalize(pos);
    vec2 uv = vec2(0.0);
    uv.x = 0.5 + atan(p.z, p.x) / (2.*3.14159);
    uv.y = 0.5 - asin(p.y) / 3.14159;

    float y = texture(texture_buffer, uv).y;
    float y2 = 0.1 * y;

    float ss = 5.0;
    vec3 sphereO = pos; // - vec3(0.0, 0.25, 1.0);

    float sd = 0.0;
	sd = sdSphere(sphereO / ss, 0.4 + y2) * ss;

    return vec2(sd, float(iFrame)/10 / 10.0 + y); //sd + iTime / 10.0);
}

vec2 castRay( vec3 ro, vec3 rd )
{
    float tmin = 1.0;
    float tmax = 20.0;

#if 0
    float tp1 = (0.0-ro.y)/rd.y; if( tp1>0.0 ) tmax = min( tmax, tp1 );
    float tp2 = (1.6-ro.y)/rd.y; if( tp2>0.0 ) { if( ro.y>1.6 ) tmin = max( tmin, tp2 );
                                                 else           tmax = min( tmax, tp2 ); }
#endif

	float precis = 0.002;
    float t = tmin;
    float m = -1.0;
    for( int i=0; i<50; i++ )
    {
	    vec2 res = map( ro+rd*t );
        if( res.x<precis || t>tmax ) break;
        t += res.x;
	    m = res.y;
    }

    if( t>tmax ) m=-1.0;
    return vec2( t, m );
}


float softshadow( vec3 ro, vec3 rd, float mint, float tmax )
{
	float res = 1.0;
    float t = mint;
    for( int i=0; i<16; i++ )
    {
		float h = map( ro + rd*t ).x;
        res = min( res, 8.0*h/t );
        t += clamp( h, 0.02, 0.10 );
        if( h<0.001 || t>tmax ) break;
    }
    return clamp( res, 0.0, 1.0 );

}

vec3 calcNormal( vec3 pos )
{
	vec3 eps = vec3( 0.001, 0.0, 0.0 );
	vec3 nor = vec3(
	    map(pos+eps.xyy).x - map(pos-eps.xyy).x,
	    map(pos+eps.yxy).x - map(pos-eps.yxy).x,
	    map(pos+eps.yyx).x - map(pos-eps.yyx).x );
	return normalize(nor);
}

float calcAO( vec3 pos, vec3 nor )
{
	float occ = 0.0;
    float sca = 1.0;
    for( int i=0; i<5; i++ )
    {
        float hr = 0.01 + 0.12*float(i)/4.0;
        vec3 aopos =  nor * hr + pos;
        float dd = map( aopos ).x;
        occ += -(dd-hr)*sca;
        sca *= 0.95;
    }
    return clamp( 1.0 - 3.0*occ, 0.0, 1.0 );
}

vec3 render( vec3 ro, vec3 rd )
{
    vec3 col = vec3(0.0) +rd.y*0.8;
//    vec3 col = vec3(0.7, 0.9, 1.0) +rd.y*0.8;
    vec2 res = castRay(ro,rd);
    float t = res.x;
	float m = res.y;
    if( m>-0.5 )
    {
        vec3 pos = ro + t*rd;
        vec3 nor = calcNormal( pos );
        vec3 ref = reflect( rd, nor );

        // material
		/* col = 0.45 + 0.3*sin( vec3(0.05,0.08,0.10)*(m-1.0) );


        if( m<1.5 )
        {

            float f = mod( floor(5.0*pos.z) + floor(5.0*pos.x), 2.0);
            col = 0.4 + 0.1*f*vec3(1.0);
        }*/
		col = hsv2rgb(vec3(m, 1.0, 1.0));

        // lighting
        float occ = calcAO( pos, nor );
		vec3  lig = normalize( vec3(-0.6, 0.7, -0.5) );
		float amb = clamp( 0.5+0.5*nor.y, 0.0, 1.0 );
        float dif = clamp( dot( nor, lig ), 0.0, 1.0 );
        float bac = clamp( dot( nor, normalize(vec3(-lig.x,0.0,-lig.z))), 0.0, 1.0 )*clamp( 1.0-pos.y,0.0,1.0);
        float dom = smoothstep( -0.1, 0.1, ref.y );
        float fre = pow( clamp(1.0+dot(nor,rd),0.0,1.0), 2.0 );
		float spe = pow(clamp( dot( ref, lig ), 0.0, 1.0 ),16.0);

        dif *= softshadow( pos, lig, 0.02, 2.5 );
        dom *= softshadow( pos, ref, 0.02, 2.5 );

		vec3 lin = vec3(0.0);
        lin += 1.20*dif*vec3(1.00,0.85,0.55);
		lin += 1.20*spe*vec3(1.00,0.85,0.55)*dif;
        lin += 0.20*amb*vec3(0.50,0.70,1.00)*occ;
        lin += 0.30*dom*vec3(0.50,0.70,1.00)*occ;
        lin += 0.30*bac*vec3(0.25,0.25,0.25)*occ;
        lin += 0.40*fre*vec3(1.00,1.00,1.00)*occ;
		col = col*lin;

    	col = mix( col, vec3(0.8,0.9,1.0), 1.0-exp( -0.002*t*t ) );

    }

	return vec3( clamp(col,0.0,1.0) );
}

mat3 setCamera( vec3 ro, vec3 ta, float cr )
{
	vec3 cw = normalize(ta-ro);
	vec3 cp = vec3(sin(cr), cos(cr),0.0);
	vec3 cu = normalize( cross(cw,cp) );
	vec3 cv = normalize( cross(cu,cw) );
    return mat3( cu, cv, cw );
}

void main(  )
{
	vec2 q = (gl_FragCoord.xy-pos_correction.xy)/iResolution.xy;
//	vec2 q = (gl_FragCoord.xy)/iResolution.xy;
    vec2 p = -1.0+2.0*q;
	p.x *= iResolution.x/iResolution.y;
    vec2 mo = iMouse.xy;
//    vec2 mo = iMouse.xy/iResolution.xy;

	float time = 15.0 + float(iFrame)/10;

	// camera
	// vec3 ro = vec3( -0.5+3.5*cos(0.1*time + 6.0*mo.x), 1.0 + 2.0*mo.y, 0.5 + 3.5*sin(0.1*time + 6.0*mo.x) );
    //vec3 ro = vec3( -0.5+3.5*cos(6.0*mo.x), 1.0 + 2.0*mo.y, 0.5 + 3.5*sin(6.0*mo.x) );
    vec3 ro = vec3( 3.5, 1.0, 3.5 );
	vec3 ta = vec3( -0.5, -2.0, -1.0 );

	// camera-to-world transformation
    mat3 ca = setCamera( ro, ta, 0.0 );

    // ray direction
	vec3 rd = ca * normalize( vec3(p.xy,2.0) );

    // render
    vec3 col = render( ro, rd );

	col = pow( col, vec3(0.4545) );

    gl_FragColor=vec4( col, 1.0 );
}
