// 46 Space

uniform sampler2D texture_in;
uniform float float_param1;
uniform float float_param2;
uniform vec2 pos_correction;

uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

//#ifdef GL_ES
//precision highp float;
//#endif

float lensSize=0.4;

void main(void)
{
    vec2 p = (gl_FragCoord.xy-pos_correction.xy) / iResolution.xy;
//    vec2 m = iMouse.xy / iResolution.xy;
    vec2 m = iMouse.xy;
    m.y=-m.y+1.0;

    vec2 d = p - m;
    float r = sqrt(dot(d, d)); // distance of pixel from mouse

    vec2 uv;
    vec3 col = vec3(0.0, 0.0, 0.0);
    if (r > lensSize+0.01)
    {
        uv = p;
        col = texture2D(texture_in, vec2(uv.x, -uv.y)).xyz;
    }
    else if (r < lensSize-0.01)
    {
        // Thanks to Paul Bourke for these formulas; see
        // http://paulbourke.net/miscellaneous/lenscorrection/
        // and .../lenscorrection/lens.c
        // Choose one formula to uncomment:
        // SQUAREXY:
        // uv = m + vec2(d.x * abs(d.x), d.y * abs(d.y));
        // SQUARER:
        uv = m + d * r; // a.k.a. m + normalize(d) * r * r
        // SINER:
        // uv = m + normalize(d) * sin(r * 3.14159 * 0.5);
        // ASINR:
        // uv = m + normalize(d) * asin(r) / (3.14159 * 0.5);
        col = texture2D(texture_in, vec2(uv.x, -uv.y)).xyz;
    }
    gl_FragColor = vec4(col, 1.0);
}
