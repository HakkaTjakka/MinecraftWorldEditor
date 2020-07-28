uniform sampler2D texture;
uniform vec2 resolution_source_texture;
in vec4 tex_coord;
//in vec4 coord;

void main()
{
    //if (gl_FragCoord.z<0.480)
//            discard;
//    else
        gl_FragColor = texture2D(texture,  tex_coord.xy/resolution_source_texture);   // resolution maze2.png texture.... gives smooth pixesls instead of texelFetch.... (sub pixel division...?) Important for smooth textures...
//        gl_FragColor.a = gl_FragColor.a * (2.0-gl_FragCoord.z/0.4);

//    gl_FragColor = texelFetch(texture, ivec2( tex_coord.xy ) , 0);
//    gl_FragColor = texelFetch(texture, ivec2( coord.xy ) , 0);
}
