//shader 19 GLOWING EDGE

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform vec2 pos_pacman;

float d;

float lookup(vec2 p, float dx, float dy)
{
    vec2 uv = (p.xy + vec2(dx * d, dy * d)) / iResolution.xy;
    vec4 c = texture(texture_in, uv.xy);

	// return as luma
    return 0.2126*c.r + 0.7152*c.g + 0.0722*c.b;
}

void main()
{
    d = sin(iTime * 5.0)*0.5 + 1.5; // kernel offset
    vec2 p = (gl_FragCoord.xy-pos_correction.xy);
    p.y=-p.y;

	// simple sobel edge detection
    float gx = 0.0;
    gx += -1.0 * lookup(p, -1.0, -1.0);
    gx += -2.0 * lookup(p, -1.0,  0.0);
    gx += -1.0 * lookup(p, -1.0,  1.0);
    gx +=  1.0 * lookup(p,  1.0, -1.0);
    gx +=  2.0 * lookup(p,  1.0,  0.0);
    gx +=  1.0 * lookup(p,  1.0,  1.0);

    float gy = 0.0;
    gy += -1.0 * lookup(p, -1.0, -1.0);
    gy += -2.0 * lookup(p,  0.0, -1.0);
    gy += -1.0 * lookup(p,  1.0, -1.0);
    gy +=  1.0 * lookup(p, -1.0,  1.0);
    gy +=  2.0 * lookup(p,  0.0,  1.0);
    gy +=  1.0 * lookup(p,  1.0,  1.0);

	// hack: use g^2 to conceal noise in the video
    float g = gx*gx + gy*gy;
    float g2 = g * (sin(iTime) / 2.0 + 0.5);

    vec4 col = texture(texture_in, p / iResolution.xy);
    col += vec4(0.0, g, g2, 1.0);

    gl_FragColor = col;
}
