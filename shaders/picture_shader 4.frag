//copy
precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 txt_resolution;
uniform vec2 iMouse;
uniform float iTime;

vec2 vd = 1.0/iResolution.xy;

vec4 getVal2(vec2 uv)
{
    return texture(texture_buffer,uv);
}

vec4 getBlur(vec2 uv)
{
    return vec4(
        (getVal2(uv+vec2(vd.x,0))   +getVal2(uv-vec2(vd.x,0))    +getVal2(uv+vec2(0,vd.y))    +getVal2(uv-vec2(0,vd.y)))*2.0 + getVal2(uv)*4.0 +
        (getVal2(uv+vec2(vd.x,vd.y))+getVal2(uv+vec2(-vd.x,vd.y))+getVal2(uv+vec2(vd.x,-vd.y))+getVal2(uv+vec2(-vd.x,-vd.y)))
    )/16.0;
}


float getVal(vec2 uv)
{
//    return length(getBlur(uv).xyz);
    return length(texture(texture_buffer,uv).xyz);
}

vec2 getGrad(vec2 uv,vec2 delta) {

     return vec2( -getVal(uv+vec2(delta.x,0))+getVal(uv-vec2(delta.x,0)) , -getVal(uv+vec2(0,delta.y))+getVal(uv-vec2(0,delta.y)) )/delta;
//     return vec2( getVal(uv+vec2(delta.x,0))-getVal(uv-vec2(delta.x,0)) , getVal(uv+vec2(0,delta.y))-getVal(uv-vec2(0,delta.y)) )/delta;
}

/*
vec2 getGrad(vec2 uv,float delta)
{
    vec2 d=vec2(delta,0);
    return vec2(
        getVal(uv+d.xy)-getVal(uv-d.xy) + getVal(uv+2*d.xy)-getVal(uv-2*d.xy),
        getVal(uv+d.yx)-getVal(uv-d.yx) + getVal(uv+2*d.yx)-getVal(uv-2*d.yx)
    )/(delta*2);
}
*/

vec2 getGrad2(vec2 uv,float delta)
{
    vec2 d=vec2(delta,0);
    return vec2(
        getVal(uv+d.xy)-getVal(uv-d.xy),
        getVal(uv+d.yx)-getVal(uv-d.yx)
    )/delta;
}

void main( )
{
	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
	uv.y=-uv.y;

	vec4 background=texture(texture_in,(gl_FragCoord.xy/vec2(1920,1080)));
	vec4 buf=texture(texture_buffer,(gl_FragCoord.xy/txt_resolution.xy));

    vec3 n = vec3(getGrad(uv,1.0/iResolution.xy),150.0);
    n=normalize(n);
    vec3 light;
    if (iMouse_on==1)
        light = normalize(vec3(iMouse.xy*vec2(3,-3)+vec2(-1,2) ,1) - vec3( (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy,0));
    else
        light = normalize(vec3(1,1,2));
    float diff=clamp(dot(n,light),0.5,1.0);
    float spec=clamp(dot(reflect(light,n),vec3(0,0,-1)),0.0,1.0);
    spec=pow(spec,36.0)*2.5;

//	gl_FragColor = texture(texture_buffer,uv)*vec4(vec3(diff),1.0)+vec4(vec3(spec),0.0);

//	gl_FragColor = mix(texture(texture_buffer,uv)*2.0,background,background.a);

//	gl_FragColor = mix(texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*2.0+vec4(vec3(spec),0.0),background,background.a);

    gl_FragColor = mix(texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0),background,background.a);

//	gl_FragColor = mix(texture(texture_buffer,uv),background,background.a);

//    gl_FragColor = mix(buf,background,background.a);


//	gl_FragColor = mix(texture(texture_buffer,uv),background,background.a);
//	gl_FragColor = texture(texture_buffer,uv);

}

