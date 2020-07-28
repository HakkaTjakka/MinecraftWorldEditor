//precision highp float;
uniform sampler2D texture_buffer;
uniform sampler2D texture_in;
uniform vec2 iResolution;
uniform vec2 pos_correction;
uniform int iFrame;
uniform int iTime;
uniform vec2 iMouse;


vec3 pulsar(in vec3 p, in vec2 uv)
{
	float	str = 15.0,
        	accum = 0.5,
        	prev = mod((iTime+sin(iTime*20.0)*0.025)*10.1, 60.0),
        	tw = 1.0;

    p.z += sin(iTime*1.0)*0.01;

	for (int i = 0; i < 18; ++i)
    {
		float mag = dot(p, p);
		p = abs(p) / mag + vec3(-.5, -.42 - cos(iTime*0.2)*0.02, -1.75 + sin(iTime*0.2)*0.003);
		float w = exp(-float(i) / str);
		accum += w * exp(-str * pow(abs(mag - prev), 2.2));
		tw += w;
		prev = mag;
	}
    float t = clamp(5.0 * accum / tw - 0.9, 0.0, 1.0);
	return vec3(1.3*t*t*t*(1.0 - length(uv)*0.2) , 1.2*t*t, 1.0*t);
}

void main()
{
    vec2 offset = iResolution.xy * (0.5 + iMouse.xy);

    vec2 uv = 2.0 * (gl_FragCoord.xy) / iResolution.xy - 1.  + offset/iResolution.xy - 0.5;

	vec3 p = vec3(uv * (iResolution.xy / iResolution.x) / 0.2, 0.0);

    vec3 noise = texture(texture_in, uv*(3.0-mod(iTime*2.0,0.2))).rgb*0.1;

    vec2 vig_coord = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy - pow((gl_FragCoord.xy-pos_correction.xy) / iResolution.xy,vec2(2.0));
    float vig_highlight = 1.0-pow(vig_coord.x*vig_coord.y*3.0, 0.05);

	gl_FragColor = vec4((vec3(pulsar(p*0.99,uv).r, pulsar(p, uv).gb)-noise)+vig_highlight, 1.0) ;
}
