//copy
precision highp float;
uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

vec4 getVal(vec2 uv)
{
    return texture(texture_in,uv);
}

vec4 getGrad(vec2 uv,vec2 d)
{
    return vec4(
        (getVal(uv+vec2(d.x,0))  +getVal(uv-vec2(d.x,0))   +getVal(uv+vec2(0,d.y))   +getVal(uv-vec2(0,d.y)))*2.0 + getVal(uv)*4.0 +
        (getVal(uv+vec2(d.x,d.y))+getVal(uv+vec2(-d.x,d.y))+getVal(uv+vec2(d.x,-d.y))+getVal(uv+vec2(-d.x,-d.y)))
    )/16.0;
}

void main( )
{
	vec2 uv = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;

	uv.y=-uv.y;

    vec4 col = getGrad(uv,1.0/iResolution);

	gl_FragColor = col;

//	gl_FragColor = mix(texture(texture_buffer,uv)*vec4(vec3(diff),1.0)+vec4(vec3(spec),0.0),background,background.a);
//	gl_FragColor = mix(texture(texture_buffer,uv),background,background.a);
//	gl_FragColor = texture(texture_buffer,uv);

}

