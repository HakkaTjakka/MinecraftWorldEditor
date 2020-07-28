//precision highp float;
uniform sampler2D texture_movie;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;


#define threshold 0.6

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main2( )
{
	vec2 uv = (gl_FragCoord.xy) / iResolution.xy;
	uv.y=1.0-uv.y;
//    vec4 col=texture(texture_in,uv);
//    if (col.r<=0.1 && col.b<=0.1) col.a=1.0-col.g;
//	gl_FragColor = col;

    vec4 greenScreen = vec4(0.,1.,0.,1.);
    vec4 color=texture(texture_in,uv);
    vec3 diff = color.xyz - greenScreen.xyz;
    if(dot(diff, diff) < threshold) {
        color.a = 0.;
    }

    gl_FragColor = color;


//	gl_FragColor = texture(texture_in,uv);
}


void main( )
{
	vec2 q = (gl_FragCoord.xy) / iResolution.xy;
	q.y=1.0-q.y;

//	vec3 bg = texture( iChannel0, q ).xyz;
	vec3 fg = texture( texture_in, q ).xyz;

    float maxrb = max( fg.r, fg.b );
    float k = clamp( (fg.g-maxrb)*5.0, 0.0, 1.0 );


    float dg = fg.g;
    fg.g = min( fg.g, maxrb*0.8 );
    fg += dg - fg.g;


//    fragColor = vec4( mix(fg, bg, k), 1.0 );
    gl_FragColor = vec4( fg.rgb, 1.0-k );
}
