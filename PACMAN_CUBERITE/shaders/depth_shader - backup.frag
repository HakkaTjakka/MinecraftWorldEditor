
	float z = gl_FragCoord.z / gl_FragCoord.w;

    if (TEXTURE_ARRAY) {
        gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy);
        float hit_center_screen=( sqrt(pow(gl_FragCoord.x/resolution.x-0.5,2.0)+pow(ratio*(gl_FragCoord.y/resolution.y-0.5),2.0)) );

/*
            float hop=(sin(wave_phase*5.0)+2.0)*0.025;
            if (hit_center_rot<hop) {
                float add=clamp( (hop-hit_center_rot)*20.0*( sin(wave_phase*5.0)+2.0 ), 0.0, 1.0);
//                float add=1.0;
                gl_FragColor = clamp(gl_FragColor * (1.0+add), 0.0, 1.0);
//                gl_FragColor.r=clamp(gl_FragColor.r+add,0.0,1.0);
//                gl_FragColor.g=clamp(gl_FragColor.g+add,0.0,1.0);
//                gl_FragColor.b=clamp(gl_FragColor.b-add,0.0,1.0);
            }
*/

/*            if (hit_center<0.05) {
//                float add=(0.05-hit_center)*40.0*(sin(wave_phase*15.0)+1.0);
                float add=1.0;
                gl_FragColor.r=clamp(gl_FragColor.r-add,0.0,1.0);
                gl_FragColor.g=clamp(gl_FragColor.g-add,0.0,1.0);
                gl_FragColor.b=clamp(gl_FragColor.b+add,0.0,1.0);
            }
*/
        if (hit_center_screen<0.005) {
    //                float add=1.0;
            float add=1.0;
    //                float add=(0.005-hit_center_screen)*100.0*(sin(wave_phase*15.0)+1.0);
            gl_FragColor.r=clamp(gl_FragColor.r+add,0.0,1.0);
            gl_FragColor.g=clamp(gl_FragColor.g-add,0.0,1.0);
            gl_FragColor.b=clamp(gl_FragColor.b-add,0.0,1.0);
        }
        float hit_mouse=( sqrt(pow(gl_FragCoord.x/resolution.x-mouse.x/2.0-0.5,2.0)+pow(ratio*(gl_FragCoord.y/resolution.y-mouse.y/2.0-0.5),2.0)) );
        if (hit_mouse<0.025) {
            float add=(0.025-hit_mouse)*20.0*(sin(wave_phase*15.0)+1.0);
            gl_FragColor.r=clamp(gl_FragColor.r-add,0.0,1.0);
            gl_FragColor.g=clamp(gl_FragColor.g+add,0.0,1.0);
            gl_FragColor.b=clamp(gl_FragColor.b-add,0.0,1.0);

        }
/*
        if (hit_center_rot<0.05) {
            float add=(0.05-hit_center_rot)*10.0*(sin(wave_phase*5.0)+1.0);
            gl_FragColor.r=clamp(gl_FragColor.r+add,0.0,1.0);
            gl_FragColor.g=clamp(gl_FragColor.g+add,0.0,1.0);
            gl_FragColor.b=clamp(gl_FragColor.b-add,0.0,1.0);
        }
*/
    } else if (COLOR_ARRAY) {
//      gl_FragColor=out_color;
        int tot=int(z*(256.0*256.0*256.0-1));
        float red=float(tot >> 16)/256.0;
        float green=float(tot&0xFF00 >> 8)/256.0;
        float blue=float(tot&0xFF )/256.0;
//      float green=0.0;
//      float blue=0.0;
       gl_FragColor =  vec4(red,green,blue,1.0);
//            gl_FragColor =  vec4(1.0,1.0,0.0,1.0)*(1.0-z/3.0);
    }
//        if (TEXTURE_ARRAY) { gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy); }
    if (WIRE_FRAME) {
/*
        int tot=int(z*(256.0*256.0*256-1));
        float red=float(tot >> 16)/256.0;
        float green=float(tot&0x00FF00 >> 8)/256.0;
//            float blue=float(tot&0x0000FF)/256.0;
//            float green=0.0;
        float blue=0.0;
        gl_FragColor =  vec4(red,green,blue,1.0);
*/
//            gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy);

//            gl_FragColor.rgb = vec3(1.0,1.0,0.0);
//            gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy);

        gl_FragColor =  vec4(1.0,1.0,0.0,1.0)*(1.0-z/3.0);
    }
//        if (WIRE_FRAME) gl_FragColor =  out_color;
//        if (COLOR_ARRAY) { gl_FragColor=gl_FrontColor; }
//        else if (TEXTURE_ARRAY) { gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy); }
//        if (WIRE_FRAME) gl_FragColor =  gl_Color;
//	}

