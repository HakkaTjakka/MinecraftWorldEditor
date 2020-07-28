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
#define iteration 32.
#define spread 0.01

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec4 image_at(vec2 uv,sampler2D image)
{
    return texture(image,uv);
}


void main3( )
{
	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;

    float time = iTime*10.;

//    vec2 uv = (fragCoord.xy-pos_correction.xy / iResolution.xy;

    /*
    float angle = radians(sin(time*0.5)*22.);
    float zoom = (sin(time*0.78)+1.5)/2.;

    vec2 offset = vec2(cos(time*0.15)*0.2,sin(time)*0.17);

    //Zoom in

    vec2 uv = 0.5 + (uvorig-0.5)*zoom;

    //Rotate
    uv -= 0.5;

    mat2 m = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));

    uv *= m;

    uv += 0.5;*/

    vec4 final;
    vec4 original = image_at(uv,texture_buffer);


    vec4 final_old;
    vec4 temp;

    for (float i=iteration;i>0.;i-=1.)
    {
    temp = vec4(rand(vec2(0.,i)),rand(vec2(sin(i),cos(i))),rand(vec2(i,0.)),0.) + image_at(uv+vec2(cos(i+time+mod(i,2.)+sin(i*time*0.5))*0.2*(i*spread),sin(i+time+mod(i,2.)+sin(i*time*0.5))*0.2*(i*spread)),texture_buffer);

    final_old = mix(final_old,temp,temp.a);
    }
    final_old = mix(final_old,original,original.a);

    final = final_old;

    gl_FragColor = final;

//    gl_FragColor = original;
}


void main( )
{
	vec2 q = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
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


void main__( )
{
	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
//	vec2 uv = (gl_FragCoord.xy) / iResolution.xy;
//	uv.y=1.0-uv.y;
//    vec4 col=texture(texture_in,uv);
//    if (col.r<=0.1 && col.b<=0.1) col.a=1.0-col.g;
//	gl_FragColor = col;

//    vec4 greenScreen = vec4(0.,1.,0.,1.);
    vec4 color=texture(texture_buffer,uv);
//    vec3 diff = color.xyz - greenScreen.xyz;
//    if(dot(diff, diff) < threshold) {
//        color.a = 0.;
//    }

    gl_FragColor = color;


//	gl_FragColor = texture(texture_in,uv);
}


//How many shots of imbecile syringe did you had?
#define man_debris 8.

//Render Background only?
#define BG_only false

vec4 SHIT(vec2 uv,sampler2D image,float time)
{
    vec2 uvorig = uv;

    float angle = radians(sin(time*0.25+cos(time*0.3)*2.5)*32.);
    float zoom = (sin(time*0.78)+1.8)/2.;

    vec2 offset = vec2(cos(time*0.15)*0.2,sin(time)*0.17);
    vec2 pixel_size = 1. / iResolution.xy;
    //Zoom in

    vec2 uv2 = 0.5 + (uvorig-0.5)*zoom;

    //Rotate
    uv2 -= 0.5;

    mat2 m = mat2(cos(angle), -sin(angle), sin(angle), cos(angle));

    uv2 *= m;
    uv2 *= pixel_size*500.;

    uv2 += 0.5;

    uv2 += offset;

    return texture(image,uv2);

}

void mainhop()
{
    vec4 finalcolor = vec4(0);
    float time = iTime * 10.;

	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
    vec4 guy = SHIT(uv,texture_buffer,time);
    vec4 guy2 = SHIT(uv+vec2(-0.1,0.1),texture_buffer,time);

    vec4 guybrush;

    vec2 count;



//	vec4 trip = SHIT(uv,iChannel2,time);

    //Shadow color
    guy2.xyz = vec3(0.2,0.35,0.43);
    //RAINBOWWWWW
    guy.xyz += vec3(sin(time*0.5)*0.7,cos(time*0.5)*0.8,cos(time*0.3+sin(time))*0.83);


//    finalcolor = background;

    if (!BG_only)
    {

    for (float i=0.;i<man_debris;i+=1.)
    {
    count += vec2((cos(i+time)+0.)*0.2,cos(i*2.+time)*0.4);
    //Flying mann-debris shadow.
    guybrush = SHIT(uv+vec2(count.x,count.y)+vec2(-0.1,0.1),texture_buffer,time);

    guybrush.xyz = vec3(0.2,0.35,0.43);

    finalcolor = mix(finalcolor,guybrush,guybrush.a);
    }



    count = vec2(0.);

    for (float i=0.;i<man_debris;i+=1.)
    {
    count += vec2((cos(i+time)+0.)*0.2,cos(i*2.+time)*0.4);
    //Flying mann-debris.
    guybrush = SHIT(uv+vec2(count.x,count.y),texture_buffer,time);

    guybrush.xyz += vec3(sin(i+time)+0.7,cos(i+time)+0.3,sin(i+3.145436435435+time)+0.6);

    finalcolor = mix(finalcolor,guybrush,guybrush.a);
    }

//    finalcolor = mix(finalcolor,trip,trip.a);
    finalcolor = mix(finalcolor,guy2,guy2.a);


    for (float i=0.;i<4.;i+=1.)
    {
        guybrush = SHIT(uv+vec2(i*0.01-0.015,0.),texture_buffer,time);
        guybrush.xyz = vec3(1.0);

        finalcolor = mix(finalcolor,guybrush,guybrush.a);
    }
    for (float i=0.;i<4.;i+=1.)
    {
        guybrush = SHIT(uv+vec2(0.,i*0.01-0.015),texture_buffer,time);
        guybrush.xyz = vec3(1.0);

        finalcolor = mix(finalcolor,guybrush,guybrush.a);
    }

    finalcolor = mix(finalcolor,guy,guy.a);


    }



    //finalcolor = mix();

	gl_FragColor = finalcolor;
}
