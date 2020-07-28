//pixelate

uniform sampler2D texture_in;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;

void main()
{
    float factor = 1.0 / ((iMouse.x+iMouse.y) + 0.001);
    vec2 pos = floor(gl_FragCoord.xy * factor + 0.5) / factor;
//    gl_FragColor = texture2D(texture_in, pos) * gl_Color;
    gl_FragColor = texture2D(texture_in, pos); 
}
