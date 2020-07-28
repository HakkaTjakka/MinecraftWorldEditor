precision highp float;
uniform sampler2D texture_surround[9];
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform int background_plot;
uniform int formula_on;

#define PI 3.141592653589793

float getVal(vec2 uv) {
    int nText=int(floor(uv.x+1.0)+floor(uv.y+1.0)*3.0);
    return length(texture(  texture_surround[nText]  , uv ).xyz);
}

vec2 getGrad(vec2 uv,vec2 delta) {

     return vec2( getVal(uv+vec2(delta.x,0))-getVal(uv-vec2(delta.x,0)) , getVal(uv+vec2(0,delta.y))-getVal(uv-vec2(0,delta.y)) )/delta;
}

vec4 getPix(vec2 uv) {
    int nText=int(floor(uv.x+1.0)+floor(uv.y+1.0)*3.0);
    return texture(  texture_surround[nText]  , uv );
}

vec4 AA(vec2 uv,vec2 d)
{
    return vec4(
        (getPix(uv+vec2(d.x,0))  +getPix(uv-vec2(d.x,0))   +getPix(uv+vec2(0,d.y))   +getPix(uv-vec2(0,d.y)))*2.0 +
         getPix(uv)*4.0 +
        (getPix(uv+vec2(d.x,d.y))+getPix(uv+vec2(-d.x,d.y))+getPix(uv+vec2(d.x,-d.y))+getPix(uv+vec2(-d.x,-d.y)))
    )/16.0;
}

void main( )
{

//	gl_FragColor = texture(texture_in,uv)*vec4(vec3(diff),1.0);
//	gl_FragColor = texture(texture_in,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);

//    vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));

//	gl_FragColor = mix(texture(texture_buffer,uv)*vec4(vec3(diff),1.0)+vec4(vec3(spec),0.0),background,background.a);
//	gl_FragColor = mix(texture(texture_buffer,uv),background,background.a);
//	gl_FragColor = texture(texture_buffer,uv);

    if (background_plot==1) {
        vec2 uv = (gl_FragCoord.xy) / vec2(1920,1080);
//        gl_FragColor=vec4(1);


//    vec2 coord_abs = (gl_FragCoord.xy-pos_correction.xy)/iResolution.xy-0.5;
//    vec3 n= vec3( (sin( (coord_abs+0.5)*PI*2 ) )/2.0, 1.0);



// PAINT
/*

    vec3 n = vec3(getGrad(uv,1.0/vec2(1920,1080)),150.0);
    n=normalize(n);
    vec3 light;
    if (iMouse_on==1)
        light = normalize(vec3(iMouse.xy*vec2(3,-3)+vec2(-1,2) ,1) - vec3( (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy,0));
    else
        light = normalize(vec3(1,1,2));
    float diff=clamp(dot(n,light),0.5,1.0);
    float spec=clamp(dot(reflect(light,n),vec3(0,0,-1.0)),0.0,1.0);
    spec=pow(spec,36.0)*2.5;

    gl_FragColor = texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)) )*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);
//    gl_FragColor = texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)) )*vec4(vec3(diff),1.0)*1.2;
*/

///* ANTIALIAS
       gl_FragColor = AA(uv,1.0/vec2(1920,1080) );
//*/



//        gl_FragColor = texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);
// copy
//        gl_FragColor = texture(texture_buffer,vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy)/iResolution.xy);

//        vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
//        gl_FragColor = mix(gl_FragColor,background,background.a);
    } else {
       vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
        gl_FragColor = texture(texture_buffer,vec2(1.0,-1.0)*(gl_FragCoord.xy-pos_correction.xy)/iResolution.xy);

//       gl_FragColor = AA(vec2(0.0,1.0)+vec2(1.0,-1.0)*uv,1.0/iResolution.xy );
//        gl_FragColor=vec4(0.0,1.0,1.0,1.0);
//        gl_FragColor = texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);
//        gl_FragColor = texture(texture_buffer,uv);
    }
}
