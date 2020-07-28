//paint
precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

float getVal(vec2 uv)
{
    return length( texture(texture_buffer,uv).xyz);
}

vec2 getGrad(vec2 uv,vec2 delta) {

     return vec2( getVal(uv+vec2(delta.x,0))-getVal(uv-vec2(delta.x,0)) , getVal(uv+vec2(0,delta.y))-getVal(uv-vec2(0,delta.y)) )/delta;
}

void main( )
{
	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
    vec3 n = vec3(getGrad(uv,1.0/iResolution.xy),150.0);
//    vec3 n = vec3(getGrad(uv,1.0/iResolution.y),150.0);
    //n *= n;
    n=normalize(n);
//    gl_FragColor=vec4(n,1);
//    vec3 light = normalize(vec3(1,1,2));
//    vec3 light = normalize(vec3(iMouse.xy / iResolution.y,1) - vec3( (gl_FragCoord.xy-pos_correction.xy) / iResolution.y,0));
    vec3 light;
    if (iMouse_on==1)
        light = normalize(vec3(iMouse.xy*vec2(3,-3)+vec2(-1,2) ,1) - vec3( (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy,0));
    else
        light = normalize(vec3(1,1,2));
    float diff=clamp(dot(n,light),0.5,1.0);
    float spec=clamp(dot(reflect(light,n),vec3(0,0,-1)),0.0,1.0);
    spec=pow(spec,36.0)*2.5;


    //spec=0.0;y
//	gl_FragColor = texture(texture_buffer,uv);
//	gl_FragColor = texture(texture_in,uv)*vec4(vec3(diff),1.0);

	gl_FragColor = texture(texture_buffer,uv)*vec4(vec3(diff),1.0)*1.2+vec4(vec3(spec),0.0);

//    gl_FragColor.xyz = vec3(clamp(gl_FragColor.r+0.3*gl_FragColor.g,0.0,1.0) , clamp(gl_FragColor.g+0.3*gl_FragColor.b,0.0,1.0) , clamp(gl_FragColor.b+0.3*gl_FragColor.r,0.0,1.0) );
//    gl_FragColor = clamp(gl_FragColor*1.3,0.0,1.0);
//	gl_FragColor.xyz = texture(texture_buffer,uv).xyz*vec3(diff)+vec3(spec);
//	gl_FragColor.xyz = texture(texture_buffer,uv).xyz;
//	gl_FragColor = texture(texture_buffer,uv);
//	gl_FragColor.a=1.0;
}

