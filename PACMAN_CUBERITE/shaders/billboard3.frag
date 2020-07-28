uniform sampler2D texture;
uniform vec2 resolution_source_texture;
in vec4 my_color;
//varying vec4 out_color;
in vec4 tex_coord;
//in vec4 coord;
void main()
{
    //if (gl_FragCoord.z<0.480)
//            discard;
//    else
//        gl_FragColor = texelFetch(texture, ivec2( tex_coord.xy ) , 0);

        gl_FragColor = texture2D(texture,  tex_coord.xy/resolution_source_texture);   // resolution maze2.png texture.... gives smooth pixesls instead of texelFetch.... (sub pixel division...?) Important for smooth textures...

        if (gl_FragColor.g>=0.2) {
            gl_FragColor = vec4(my_color.xyz,1.0);
        } else if (gl_FragColor.a==1.0 && gl_FragColor.r>0.0) {
            gl_FragColor = vec4(my_color.xyz,1.0)*(gl_FragColor.g)+gl_FragColor*(1.0-gl_FragColor.g);
        }

//        gl_FragColor.a = gl_FragColor.a * (2.0-gl_FragCoord.z/0.4);
//                gl_FragColor = vec4(gl_Color.xyz,1.0);
//                gl_FragColor = vec4(out_color.xyz,1.0);
//                if (gl_PrimitiveID==0)
//                    gl_FragColor = vec4(0,0,gl_PrimitiveID,1.0);

//                    gl_FragColor = vec4(my_color.xyz,1.0);

//                gl_FragColor = gl_FrontColor;
//                gl_FragColor = gl_Color;
//        gl_FragColor = texture2D(texture_plot,  (tex_coord.xy/resolution) );


//    gl_FragColor = texelFetch(texture, ivec2( tex_coord.xy ) , 0);
//    gl_FragColor = texelFetch(texture, ivec2( coord.xy ) , 0);
}

