uniform float wave_phase;
uniform vec2 wave_amplitude;
uniform vec2 offset;

void main()
{
    vec4 vertex = gl_Vertex;
    vertex.x += ( cos((gl_Vertex.y+offset.y*1080.0) * 0.02 + wave_phase * 3.8)  + sin((gl_Vertex.y+offset.y*1080.0) * 0.02 + wave_phase * 6.3) * 0.3 ) * wave_amplitude.x;
    vertex.y += ( sin((gl_Vertex.x+offset.x*1920.0) * 0.02 + wave_phase * 2.4)  + cos((gl_Vertex.x+offset.x*1920.0) * 0.02 + wave_phase * 5.2) * 0.3 ) * wave_amplitude.y;

    gl_Position = gl_ModelViewProjectionMatrix * vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
