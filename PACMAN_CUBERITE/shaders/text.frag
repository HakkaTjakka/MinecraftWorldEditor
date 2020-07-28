precision highp float;
uniform sampler2D texture_in;
uniform vec2 pos_correction;
uniform vec2 txt_correction;
uniform vec2 txt_resolution;
uniform vec2 iResolution;
uniform vec2 i;
uniform float iTime;
uniform vec2 iMouse;
uniform float iRotate;
uniform vec2 iSubpixel;
uniform ivec2 texture_index;
uniform sampler2D texture_surround[4];
uniform vec3 outline_color;
void main()
{
    vec4 pixel = texture2D(texture_in, gl_TexCoord[0].xy);
//    vec4 pixel = texture2D(texture, gl_FragCoord.xy/iResolution.xy);
//    if (pixel.a == 0.0)
//        discard;
//    if (pixel.b<1.0) pixel.a=pixel.b;
    if (pixel.b<1.0) pixel.a=pixel.b;

//    if (pixel.b<outline_color.b) pixel.a=pixel.b;
    gl_FragColor = pixel ;
//    gl_FragColor = pixel;
}
