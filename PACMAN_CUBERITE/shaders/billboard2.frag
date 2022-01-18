uniform sampler2D texture_plot;
uniform sampler2D texture_plot2;
uniform sampler2D texture;
uniform sampler2D texture_source;
uniform vec2 resolution;
uniform int draw_model;
uniform int flash;
uniform float iTime;

in vec4 tex_coord;

in vec3 ro;
in vec3 n;
in vec3 lp1;
in vec3 lp2;
in vec3 lp3;
in vec3 lp4;

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

        if (draw_model<=0) {
                gl_FragColor            =  texture2D(texture_plot,  (tex_coord.xy/resolution) );
        } else {
                vec4 kD;
                vec4 kB=vec4(0);
//                kD =  texture2D(the_texture,  vec2(gl_TexCoord[0].s,gl_TexCoord[0].t));
                kD =  texture2D(texture_plot,  (tex_coord.xy/resolution) );
//                if (flash && sin(5.0*iTime*3.1415)>0.0) {
                if (flash && draw_model==6) {
                    kB =  texture2D(texture_plot2,  (tex_coord.xy/resolution) );
                }
//                if (kD.a!=1.0) {
//                        kD.rgb=(kD.a)*vec3(1.0,1.0,1.0);
//                    if (kD.a!=1.0) kD.a=0.0;
//                }
//                kD.a=kD.a*kD.a*kD.a;

//        gl_FragColor = texture2D(texture_plot,  (tex_coord.xy/resolution) );


/*
                float spec1 = (1.5) * clamp(pow(max( dot(reflect(lp1, n), ro), 0.), 120.),0.0,1.0);
//                float spec2 = (0.5) * clamp(pow(max( dot(reflect(lp2, n), ro), 0.), 120.),0.0,1.0);

                float diff1 = 1.5 * clamp(dot( n,lp1), 0.1, 1.);
//                float diff2 = 2.5 * clamp(dot( n,lp2), 0.2, 1.);

                float diff=diff1;
//                if (diff2>diff) diff=diff2;

                vec3 kS_x_spec =  spec1*vec3(.7, .7, .7) + vec3(0.10, 0.10, 0.10);
//                vec3 kS_x_spec_1 =  spec1*vec3(.7, .7, .7) + vec3(0.10, 0.10, 0.10);
//                vec3 kS_x_spec_2 =  spec2*vec3(.7, .7, .7) + vec3(0.10, 0.10, 0.10);
//                vec3 kS_x_spec = (kS_x_spec_1+kS_x_spec_2)/2.0;
//                vec3 kS_x_spec = (kS_x_spec_1+kS_x_spec_2)/2.0;

*/
                float hoppa=1.0;
                if (draw_model==6) hoppa=0.3;

                float diff1 = 0.7 * clamp(dot( n,lp1), 0.3, 1.);
                float diff2 = 0.7 * clamp(dot( n,lp2), 0.3, 1.);
                float diff3 = 0.7 * clamp(dot( n,lp3), 0.3, 1.);
                float diff4 = 0.7 * clamp(dot( n,lp4), 0.3, 1.);

                float diff=diff1;
                if (diff2>diff) diff=diff2;
                if (diff3>diff) diff=diff3;
                if (diff4>diff) diff=diff4;

                float spec1 = (hoppa*diff*1.4) * clamp(pow(max( dot(reflect(lp1, n), ro), 0.), 120.),0.0,1.0);
                float spec2 = (hoppa*diff*1.5) * clamp(pow(max( dot(reflect(lp2, n), ro), 0.), 120.),0.0,1.0);
                float spec3 = (hoppa*diff*1.5) * clamp(pow(max( dot(reflect(lp3, n), ro), 0.), 120.),0.0,1.0);
                float spec4 = (hoppa*diff*1.5) * clamp(pow(max( dot(reflect(lp4, n), ro), 0.), 120.),0.0,1.0);



//                float spec=spec1+spec2+spec3+spec4;
//                vec3 kS_x_spec1 = spec1*vec3(1.0, 1.0, 1.0);
//                vec3 kS_x_spec2 = spec2*vec3(1.0, 1.0, 1.0);
//                vec3 kS_x_spec3 = spec3*vec3(1.0, 1.0, 1.0);
//                vec3 kS_x_spec4 = spec4*vec3(1.0, 1.0, 1.0);

//                vec3 kS_x_spec=(kS_x_spec1+kS_x_spec2+kS_x_spec3+kS_x_spec4)/4.0;

//                vec3 kS_x_spec = spec*vec3(1.0, 1.0, 1.0) + vec3(0.10, 0.10, 0.10);


//                float spec=(spec1+spec2+spec3+spec4)/4.0;
                float spec=spec1;
                if (spec2>spec) spec =  spec2;
                if (spec3>spec) spec =  spec3;
                if (spec4>spec) spec =  spec4;


                vec3 kS_x_spec = spec*vec3(1.0, 1.0, 1.0) ;


                gl_FragColor = clamp(   kB*0.8 + vec4( kD.xyz * (diff*.7 ) + kS_x_spec, kD.a) , 0.0 , 1.0);

//                vec4 fragcolor = clamp(   vec4( kD.xyz * (diff ) + kS_x_spec, kD.a) , 0.0 , 1.0);

//        gl_FragColor = texture2D(texture_plot,  (tex_coord.xy/resolution) );

//        gl_FragColor.b = 1.0;

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





}
