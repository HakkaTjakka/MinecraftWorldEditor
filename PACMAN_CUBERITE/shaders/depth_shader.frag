#version 330 compatibility

uniform int whattodo;
uniform float wave_phase;
uniform sampler2D the_texture;
uniform bool WIRE_FRAME;
uniform bool TEXTURE_ARRAY;
uniform bool COLOR_ARRAY;
//uniform sampler2D texture;

in vec3 my_normal;
in mat4 my_modelviewmatrix;
//in vec4 out_color;

//varying vec4 my_light;
//varying vec4 out_color;
//varying float hit_mouse;
//varying float hit_center_rot;
//varying float hit_center;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float ratio;

void main() {
    vec4 fragcolor;

//    switch(whattodo) {

//        case 0 : {
        if (whattodo==0) {
            if (TEXTURE_ARRAY) {
                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);
                float hit_center_screen=( sqrt(pow(gl_FragCoord.x/resolution.x-0.5,2.0)+pow(ratio*(gl_FragCoord.y/resolution.y-0.5),2.0)) );

                if (hit_center_screen<0.005) {
                    float add=1.0;
                    fragcolor.r=clamp(fragcolor.r+add,0.0,1.0);
                    fragcolor.g=clamp(fragcolor.g-add,0.0,1.0);
                    fragcolor.b=clamp(fragcolor.b-add,0.0,1.0);
                }
                float hit_mouse=( sqrt(pow(gl_FragCoord.x/resolution.x-mouse.x/2.0-0.5,2.0)+pow(ratio*(gl_FragCoord.y/resolution.y-mouse.y/2.0-0.5),2.0)) );
                if (hit_mouse<0.025) {
                    float add=(0.025-hit_mouse)*20.0*(sin(wave_phase*15.0)+1.0);
                    fragcolor.r=clamp(fragcolor.r-add,0.0,1.0);
                    fragcolor.g=clamp(fragcolor.g+add,0.0,1.0);
                    fragcolor.b=clamp(fragcolor.b-add,0.0,1.0);

                }
            } else if (COLOR_ARRAY) {
                float z = gl_FragCoord.z / gl_FragCoord.w;
                int tot=int(z*(256.0*256.0*256.0-1));
                float red=float(tot >> 16)/256.0;
                float green=float(tot&0xFF00 >> 8)/256.0;
                float blue=float(tot&0xFF )/256.0;
               fragcolor =  vec4(red,green,blue,1.0);
            }
            if (WIRE_FRAME) {
                float z = gl_FragCoord.z / gl_FragCoord.w;
                fragcolor =  vec4(1.0,1.0,0.0,1.0)*(1.0-z/3.0);
            }
//            break;
        }
/*
        else if (whattodo==1) {
//        case 1 : {
            if (TEXTURE_ARRAY) {
                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);
            }
            else if (WIRE_FRAME) {
                fragcolor =  gl_Color;
            }
            else if (COLOR_ARRAY) {
                fragcolor=gl_Color;
            }
//            break;
        }
*/
        else if (whattodo==3 || whattodo==1) {
//        case 3 : {
            if (TEXTURE_ARRAY) {
//                vec2 uv = zoom*rotate(iRotate)*(Coord.xy - .5 * Resolution) / Resolution.x;
                vec4 color;
                vec4 kS = vec4(1.0, 1.0, 1.0, 1.0);
                vec4 kA = vec4(0.1, 0.1, 0.1, 1.0);
                vec4 kD;
//                vec3 light=vec3(1.5, 1.5, -5.0); // zzzzz 2.0

//                vec2 rotje=vec2( (sin(wave_phase))/2.0 , (cos(wave_phase))/2.0 );
//              vec3 light=vec3(rotje.x, -.5, rotje.y); // zzzzz 2.0

                vec3 light=vec3(0.5, -0.5, 0.5); // zzzzz 2.0
                vec3 ro = vec3(0.0,0.0, -1.0);
                vec2 uv;
//                vec3 n=gl_Color.xyz;
                vec3 n=my_normal;
//                n=normalize(n);
//                uv = (gl_TexCoord[0].xy - .5 * resolution) / resolution.x;
//                uv = (gl_FragCoord.xy- .5 * resolution) / resolution.x;

//    n=normalize(n);
//                light.xyz=( my_modelviewmatrix * vec4(light,1.0) ).xyz;
//                light.xyz=( vec4(light,1.0) *  my_modelviewmatrix  ).xyz;
                vec3 lp = normalize(light);
//                vec3 lp = light;
                float diff = 1.5 * clamp(dot( n,lp), 0.3, 1.);
                float spec = (0.5) * clamp(pow(max( dot(reflect(-lp, n), ro), 0.), 120.),0.0,0.8);

                kD =  texture2D(the_texture,  gl_TexCoord[0].xy);
//                kD = texture(the_texture,uv);


//                kD =  texture2D(the_texture,  gl_TexCoord[0].xy);


                fragcolor = clamp(   vec4(kA.xyz + kD.xyz * (diff ) + kS.xyz * ( spec ), kD.a) , 0.0 , 1.0);

//                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);

//                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);

//                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);

//                float test=length(my_light.xyz);
//                float test=length(normalize(out_color.xyz));
//                float test=gl_Normal[0].x;
//                float test=length(normalize(gl_Color.xyz));
//                float test=length(normalize(gl_Normal.xyz));
//                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy) * my_light.x;
//                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy) * test;

////                fragcolor = vec4(my_light.xyz,1.0);

//                float z = gl_FragCoord.z / gl_FragCoord.w;
//                fragcolor =  vec4(fragcolor.xyz*(1.0-z/3.0),fragcolor.a);
//                fragcolor =  mix( fragcolor , vec4(0.7,0.8,1.0,1.0) , clamp((z/2.0)-0.5,0.0,1.0) );

//                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy) * (sin(wave_phase)+1)/2.0;

////                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);

//                fragcolor = fragcolor * my_light;
            }
            else if (WIRE_FRAME) {
                fragcolor =  gl_Color;
            }
            else if (COLOR_ARRAY) {
                fragcolor=gl_Color;
            }
//            break;
        }
        else if (whattodo==2) {
//        case 2 : {
            if (TEXTURE_ARRAY) {
                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);
            }
            else if (WIRE_FRAME) {
                fragcolor = gl_Color;
            }
            else if (COLOR_ARRAY) {
                fragcolor = gl_Color;
            }
//            break;
        }
//    }
    gl_FragColor=fragcolor;
}

