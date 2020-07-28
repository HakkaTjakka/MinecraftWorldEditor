uniform sampler2D texture_in;
uniform sampler2D texture_buffer;
uniform vec2 iResolution_buffer;
uniform vec2 pos_correction;
uniform int iMouse_on;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform int iFrame;
uniform int background_plot;
uniform vec2 pos_abs;

const float PI = 3.14159265358979;

const float c1 = 0.8;
const float c2 = 0.01;
const float c3 = 0.49;

mat2 rot(float t){
    return mat2(cos(t), -sin(t), sin(t), cos(t));
}

float line(vec2 p, float w){
    // return (1.0 - step(w, abs(p.y)));
    return (1.0 - smoothstep(0.0, w, abs(p.y)));
    // return smoothstep(w, -w, abs(p.y));
}

void main(  )
{
    vec2 p = ((gl_FragCoord.xy - pos_correction.xy) * 2.0 - iResolution.xy) / min(iResolution.x, iResolution.y);

    vec3 draw = vec3(0.0);

    float period = 5.0;
    float t = mod(iTime * 0.5, period);

    for (int i=0; i<3; i++) {
	    float b = (t + float(i) * period / 3.0) * PI * 0.4;
        float s = sin(b);
        float ss = s * 1.0 - 0.5;

        vec2 pos = vec2(p.x*cos(b+1.0)/2.0, p.y*(sin(b+1.0)/2.0));
        pos *= rot(ss * length(p-vec2(s, cos(b))));
        pos *= rot(0.5 * PI);

        vec3 color;
        if (i == 0) {
        	color = vec3(c1, c2, c3);
        } else if (i==1) {
        	color = vec3(c2, c3, c1);
        } else {
        	color = vec3(c3, c1, c2);
        }
        draw += line(pos, 0.3) * color;
    }

    gl_FragColor = vec4(draw,1.0);
}
