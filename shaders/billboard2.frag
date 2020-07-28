uniform sampler2D texture_plot;
uniform sampler2D texture;
uniform sampler2D texture_source;
uniform vec2 resolution;
in vec4 tex_coord;

void main()
{
//    if (gl_FragCoord.z<0.480)
//            discard;
//        gl_FragColor = vec4(1.0,0.0,0.0,1.0);
//    else
//        gl_FragColor = vec4(tex_coord.xy/resolution,0.0,1.0);


//        gl_FragColor.xy+=tex_coord.zw/resolution;

//        gl_FragColor.xy=gl_Color.rg;


//one of 8x8 textures
//        gl_FragColor = vec4(0.0,0.0,0.0,1.0);
//        vec2 Pixel=(tex_coord.xy/resolution);
//        gl_FragColor.xy=(tex_coord.rg/resolution);
//        gl_FragColor = texture2D(texture_plot,  Pixel);


//normal
        gl_FragColor = texture2D(texture_plot,  (tex_coord.xy/resolution) );


//whole 8x8 one texture
//        vec2 Pixel=gl_Color.rg;
//        Pixel.xy+=(tex_coord.zw/resolution)/vec2(8.0,8.0);          // + withing one texture of 8x8
//        gl_FragColor = texture2D(texture,  Pixel);            //
//        gl_FragColor = vec4(Pixel,0.0,1.0);


//        gl_FragColor = vec4(gl_Color.rg,0.0,1.0);                          //
//        gl_FragColor.xy+=(tex_coord.zw/resolution)/vec2(8.0,8.0);          // + withing one texture of 8x8
//        gl_FragColor = texture2D(texture,  gl_FragColor.xy);            //

//        vec2 Pixel=gl_Color.ba/vec2(8.0,8.0);
//        Pixel+=tex_coord.zw/resolution;
//        gl_FragColor = texture2D(texture_plot,  Pixel);            //
//        gl_FragColor=vec4(Pixel,0.0,1.0);


//  one on 8x8 (draw_mode 0)
//        gl_FragColor = texture2D(texture_plot,  (tex_coord.zw)/resolution);   // resolution maze2.png texture.... gives smooth pixesls instead of texelFetch.... (sub pixel division...?) Important for smooth textures...

//        gl_FragColor = texture2D(texture_plot,  tex_coord.xy/resolution);   // resolution maze2.png texture.... gives smooth pixesls instead of texelFetch.... (sub pixel division...?) Important for smooth textures...

//        gl_FragColor.rgb = vec3(1.0-tex_coord.w/resolution.x);

//        gl_FragColor.rgb = vec3(clamp(1.3-gl_FragCoord.z*1.2,0.0,1.0));

//        gl_FragColor.a = 1.0;

//        gl_FragColor.a = texture2D(texture_plot,  (tex_coord.xy/resolution) ).a;

//        gl_FragColor.a = gl_FragColor.a * (1.0-tex_coord.w/resolution.y);

//        gl_FragColor.a = gl_FragColor.a * (clamp(1.3-gl_FragCoord.z*1.2,0.0,1.0));
//        gl_FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
//    gl_FragColor = texelFetch(texture_plot, ivec2( tex_coord.xy ) , 0);
}
