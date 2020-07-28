//shader 37 Cycling texture

uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform float iTime;
uniform vec2 pos_pacman;


void main()
{
    gl_FragColor += .5+.5*sin(10.*( length(texture(texture_in,gl_FragCoord.xy/iResolution.xy).rgb) + iTime/10.0));
}
