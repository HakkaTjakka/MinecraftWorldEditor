//copy
//precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

const float PI_2 = 1.57079632679489661923;


// ---------------------------------------------------

// taken from https://www.shadertoy.com/view/XsBXRV
#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

bool keyToggled(int key)
{
	return false;
}


// ---------------------------------------------------


mat3 calcLookAtMatrix(vec3 origin, vec3 target, float roll) {
   vec3 rr = vec3(sin(roll), cos(roll), 0.0);
   vec3 ww = normalize(target - origin);
   vec3 uu = normalize(cross(ww, rr));
   vec3 vv = normalize(cross(uu, ww));

   return mat3(uu, vv, ww);
}


// ---------------------------------------------------

// taken from IQ: http://www.iquilezles.org/www/articles/warp/warp.htm

const mat2 m = mat2( 0.80,  0.60, -0.60,  0.80 );

float noise( in vec2 x )
{
	return sin(1.5*x.x)*sin(1.5*x.y);
}

float fbm( vec2 p )
{
    float f = 0.0;
    f += 0.500000*(0.5+0.5*noise( p )); p = m*p*2.02;
    f += 0.250000*(0.5+0.5*noise( p )); p = m*p*2.03;
    f += 0.125000*(0.5+0.5*noise( p )); p = m*p*2.01;
    f += 0.062500*(0.5+0.5*noise( p )); p = m*p*2.04;
    f += 0.031250*(0.5+0.5*noise( p )); p = m*p*2.01;
    f += 0.015625*(0.5+0.5*noise( p ));
    return f/0.96875;
}

float pattern( in vec2 p )
{
    vec2 q = vec2( fbm( p + vec2(0.0,0.0) ),
                  fbm( p + vec2(5.2,1.3) ) );

    vec2 r = vec2( fbm( p + 4.0*q + vec2(1.7,9.2) ),
                  fbm( p + 4.0*q + vec2(8.3,2.8) ) );

    return fbm( p + 4.0*r )/4.0;
}

// ------------------------------------------------------

bool isMoving() { return(!keyToggled(KEY_M)); }
bool isAdaptiveAAEnabled() { return(!keyToggled(KEY_S)); }
bool isSimpleAAEnabled() { return(!keyToggled(KEY_A)); }
bool isRandomAAEnabled() { return(!keyToggled(KEY_R)); }

vec3 getSkyColor(in vec3 ray) {
    float sinAngle = ray.y / length(ray);
    vec3 bottom = vec3(0.54, 0.77, 0.98);
    vec3 top = vec3(0.13, 0.39, 0.68);
    return mix(bottom, top, sinAngle/2.0);
}

vec3 getGroundColor(vec2 uv, float distance, float shadow) {
    vec3 col;

    // get ground pattern with the checkerboards
    if ( abs(mod(uv.x,12.0)) > 6.0 ||  abs(mod(uv.y,12.0)) > 6.0 ) {
        col = vec3(0.1);
    } else {
        if ( (fract(uv.x) > 0.5) != (fract(uv.y) > 0.5) ) {
            // white floor tile
            col = vec3(0.9);
        } else {
            // black floor tile
            col = vec3(0.2);
        }
    }

    // apply perlin noise-based pattern
    float p = pattern(uv);
    col += vec3(p, p*0.7, p*0.2);

    // fade to blue in the distance
    vec3 far = vec3(0.54, 0.77, 0.98);
    col = mix(col, far, atan(distance/30.0)/PI_2);

    // apply shadow
    col = mix(col,col * ( 0.35 * shadow ), shadow);
    return col;
}


vec3 renderPixel(in vec2 fragCoord) {
    // number of spheres
    const int SPHERES=3;

    // sphere data: x, y, z
    vec3 SPHERE_COORD[SPHERES]= vec3[3](
        vec3(0.0,            1.1-sin(iTime*1.3)*0.5, 0.0),
        vec3(0.0+sin(iTime), 0.9,                    0.0+cos(iTime)),
        vec3(1.5,            1.2,                    0.5)
    );

    // sphere data: radius
    float SPHERE_RADIUS[SPHERES]= float[3](
        0.6,
        0.2,
        0.3
    );

    vec3 SPHERE_COLOR[SPHERES]= vec3[3](
        vec3(0.9, 0.9, 0.9),
        vec3(0.64, 0.74, 0.86),
        vec3(1.0, 0.84, 0.0)
    );


    vec3 eye = isMoving() ? vec3(0.0+sin(iTime*0.2)*3.0, 1.0-sin(iTime*0.2)*0.5, 0.0+cos(iTime*0.2)*7.0) :  vec3(0.0, 1.0, 3.0);
    vec3 pos=eye;

    // TODO: it's buggy but still looks good
    vec3 ray=vec3(fragCoord.x-iResolution.x/2.0, fragCoord.y-iResolution.y/2.0, iResolution.x*1.0);
    mat3 lookAt=calcLookAtMatrix(eye, vec3(1.0, 0.5, 0.0), 0.0);
    ray = ray * lookAt;



    vec3 colorCor=vec3(1.0);
    float totalDistance = 0.0;

    while ( true ) {
        float s=0.0;
        int n = -1;

        // check if we hit the floor
        if ( ray.y < 0.0 ) {
            s = -pos.y/ray.y;
            n = 0;
        }

        // check the spheres
        for ( int k=0 ; k < SPHERES ; k++ ) {
            vec3 to_sphere = SPHERE_COORD[k]-pos;
            float sc = dot(to_sphere, ray);
            if ( sc > 0.0 ) { // the angle between to_sphere and ray is between -90 and +90 degrees
                float pp = dot(to_sphere, to_sphere); // TODO: length?
                float bb = sc * sc / (length(ray) * length(ray));
                float aa = SPHERE_RADIUS[k]*SPHERE_RADIUS[k] - pp + bb;
                if ( aa > 0.0 ) { // sphere is hit
                    sc = (sqrt(bb) - sqrt(aa)) / length(ray);
                    if ( sc < s || n < 0 ) { // if nothing else is hit or this is the nearest hit so far then remember this object
                        n = k+1;
                        s = sc;
                    }
                }
            }
        }



        if ( n < 0 ) { // we hit the sky
            return getSkyColor(ray) * colorCor;
        }

        // we hit something
        ray = ray * s; // set the ray to the correct length
        totalDistance += length(ray);
        pos += ray; // go where the ray hit


        if ( n == 0 ) { // we hit the floor - finally!
            // calculate soft shadows
            const float penumbra_outer = 0.2 ; // choosen by the vote of the family
            const float penumbra_inner = 0.05 ;
            float shadow = 0.0;
            // check the shadows - the check is done just on the xz plane not in 3D
            for ( int k=0 ; k < SPHERES ; k++ ) {
                float dist_from_sphere = length(SPHERE_COORD[k].xz-pos.xz);
                float penumbra_radius = SPHERE_RADIUS[k] + (SPHERE_COORD[k].y * penumbra_outer );
                float umbra_radius = SPHERE_RADIUS[k] - ( SPHERE_COORD[k].y * penumbra_inner );

                shadow += ( 1.0 - smoothstep(umbra_radius, penumbra_radius, dist_from_sphere) );
            }
            shadow = min(shadow, 1.0);

            vec2 uv=vec2(pos.x+3.0, pos.z + ( isMoving() ? iTime*1.5 : 0.0 ) ); // to add an illusion of movement
            return getGroundColor(uv, totalDistance, shadow) * colorCor;


        } else { // we hit a sphere - bounce the ray

            colorCor = colorCor * SPHERE_COLOR[n-1];

            // calculate normal vector
            vec3 normal =pos - SPHERE_COORD[n-1];
            float l = 2.0*dot(ray, normal)/dot(normal, normal);
            ray = ray - ( l * normal );
            totalDistance += length(ray);
        }
    }
}


float rand(vec2 st) {
    // the classic random function that noone knows where comes from
    st.x += iTime;
    st.y += iTime;
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}


//

vec4 main2(vec2 fragCoord )
{
    // primitive adaptive sampling
    vec3 col = renderPixel(fragCoord.xy-pos_correction.xy);
    vec3 col2 = renderPixel(fragCoord.xy-pos_correction.xy+vec2(0.5));
    if ( isAdaptiveAAEnabled() || length(col-col2) > 0.2 ) {
        // there be antialiasing, sample more with slightly randomized offsets (frankly, it's not worth the hassle)
        for ( int i = 1 ; i < 16 ; i++ ) {
            if ( i == 10 ) {
                col += col2;
            } else {
                vec2 coord = fragCoord.xy - pos_correction.xy + vec2(float(i & 3 )*0.25, float((i>>2) & 3 )*0.25);
                if ( isRandomAAEnabled() )
                	coord += vec2( rand(fragCoord- pos_correction.xy + vec2(float(i))) )*0.2;

        		col += renderPixel(coord);
            }
        }
        col = col / 16.0;
    } else if ( isSimpleAAEnabled() ) {
        col += col2;
    	col = col / 2.0;
    }

    // Output to screen
    return vec4(col,1.0);
}



void main() {
  gl_FragColor= main2(gl_FragCoord.xy);
//  gl_FragColor= (main2(gl_FragCoord.xy)*4 +
//                ( main2(gl_FragCoord.xy+vec2(-1,0)) + main2(gl_FragCoord.xy+vec2(0,-1)) + main2(gl_FragCoord.xy+vec2(1,0)) + main2(gl_FragCoord.xy+vec2(0,1)) )*2 +
//                 main2(gl_FragCoord.xy+vec2(-1,-1)) + main2(gl_FragCoord.xy+vec2(-1,1)) + main2(gl_FragCoord.xy+vec2(1,-1)) + main2(gl_FragCoord.xy+vec2(1,1)) )/16  ;
}

