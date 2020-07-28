//precision highp float;
uniform sampler2D texture_movie;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform float iCircle_size;
uniform vec2 iCircle_centre;
uniform vec2 iResolution_buffer;

float ratio=1920.0/1080.0;
float ratio_buffer=max(iResolution.x,iResolution.y)/min(iResolution.x,iResolution.y);

void main( )
{
//    float uMIN=min(     iResolution_buffer.x*ratio/iResolution.x,
//                        iResolution_buffer.y*ratio/iResolution.y    );
	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;

	uv.y=(1.0-uv.y);
    uv.x=(uv.x-0.5);
    uv.y=(uv.y-0.5);

    float distance=sqrt(uv.x*uv.x+uv.y*uv.y);
    vec4 color;
    if (distance<(0.45)) {
//        float smooth smoothstep(0.45-delta, 0.45, dist)
        float smooth=smoothstep( 0.45, 0.45-0.001, distance);
        color=vec4(1.0,1.0,1.0,smooth);



/*
        if (distance<(0.45-0.05)) {
            color=vec4(1.0,1.0,1.0,0.0);
        } else {
            vec2 p = -1.0 + 2.0 * uv;
            p.x *= iResolution.x/iResolution.y;
            vec2 m = vec2(0.5);
            float an = 3.5 + 0.5*iTime - 6.2831*(m.x-0.5);

            vec3  ta = vec3(1.0,3.5,2.0);
            vec3  ro = ta + 1.1*vec3(2.0*sin(an*5),2.5,2.0*cos(an*5));
            float rr = 0.0*sin(0.4*iTime) ;

            // camera matrix
            vec3 ww = normalize( ta - ro );
            vec3 uu = normalize( cross(ww*iTime,vec3(sin(rr+iTime),cos(rr+iTime),0.0) ) );
            vec3 vv = normalize( cross(uu,ww));
            vec3 rd = normalize( p.x*uu + p.y*vv + p.x*p.y*ww );

            vec3 col = vec3(1.0);
            col = col * rd;
            col = pow( col, vec3(2.0,2.0,2.0) )*7.0;

            color=vec4(col,smooth);
        }
*/

    }
    else
        color=vec4(0.0,0.0,0.0,0.0);
    gl_FragColor = color;
}


