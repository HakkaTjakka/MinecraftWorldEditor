#version 460 compatibility

uniform int whattodo;
uniform float wave_phase;
uniform sampler2D the_texture;
uniform bool WIRE_FRAME;
uniform bool TEXTURE_ARRAY;
uniform bool COLOR_ARRAY;
//uniform sampler2D texture;

//in vec3 my_normal;
in vec3 kS_x_spec_;
in float diff_;

//in mat4 my_modelviewmatrix;
in vec4 out_color;
in float z_;

//varying vec4 my_light;
//varying vec4 out_color;
//varying float hit_mouse;
//varying float hit_center_rot;
//varying float hit_center;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float ratio;

//vec4 kS = vec4(0.0, 0.0, 0.0, 1.0);
//vec4 kS = vec4(.2, .2, .2, 1.0);
vec4 kA = vec4(0.2, 0.2, 0.2, 1.0);
float z;

void main() {
    vec4 fragcolor;

    switch(whattodo) {

        case 0 : {
//        if (whattodo==0) {
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
            break;
        }
        case 1 :
        case 2 :
        case 3 : {
            if (TEXTURE_ARRAY) {
                vec4 kD;
//                kD =  texture2D(the_texture,  gl_TexCoord[0].xy);
                kD =  texture2D(the_texture,  vec2(gl_TexCoord[0].s,gl_TexCoord[0].t))*z_;
//                kD =  texture2D(the_texture,  vec2(gl_MultiTexCoord0.s,gl_MultiTexCoord0.t));

//              fragcolor = clamp(   vec4(kA.xyz + kD.xyz * (diff_ ) + kS_x_spec_, kD.a) , 0.0 , 1.0);
              fragcolor = clamp(   vec4( kD.xyz * (diff_ ) + kS_x_spec_, kD.a) , 0.0 , 1.0);

//              fragcolor = clamp(   vec4(kA.xyz + kD.xyz * (diff ) + kS.xyz * ( spec ), kD.a) , 0.0 , 1.0);
            }
            else if (WIRE_FRAME) {
                fragcolor=out_color;
//                if (gl_FrontFacing)  fragcolor=vec4(0.0,0.0,1.0,0.5);
//                else  fragcolor=vec4(1.0,0.0,0.0,1.0);
//                fragcolor=vec4(gl_SamplePosition.x,0.0,gl_SamplePosition.y,1.0);
//                fragcolor=vec4(gl_PointCoord.x,0.0,gl_PointCoord.y,1.0);
//                if ( (gl_SampleID%4)==1 ) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else if ( (gl_SampleID%4)==0 ) fragcolor=vec4(1.0,1.0,0.0,1.0);
//                else if ( (gl_SampleID%4)==3 ) fragcolor=vec4(0.0,1.0,0.0,1.0);
//                else if ( (gl_SampleID%4)==2 ) fragcolor=vec4(1.0,0.0,0.0,1.0);
//                else if ( (gl_PrimitiveID%16)==5) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else if ( (gl_PrimitiveID%16)==7) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else if ( (gl_PrimitiveID%16)==9) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else if ( (gl_PrimitiveID%16)==11) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else if ( (gl_PrimitiveID%16)==13) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else if ( (gl_PrimitiveID%16)==15) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else if ( (gl_PrimitiveID%12)==0) fragcolor=vec4(0.0,0.0,1.0,1.0);
//                else fragcolor=vec4(1.0,0.0,0.0,0.0);
                break;
            }
            if (COLOR_ARRAY) {
                fragcolor=out_color;
            }
            break;
        }
/*
        case 2 : {
            if (TEXTURE_ARRAY) {
                fragcolor =  texture2D(the_texture,  gl_TexCoord[0].xy);
            }
            else if (WIRE_FRAME) {
//                fragcolor = gl_Color;
                fragcolor=out_color;
            }
            else if (COLOR_ARRAY) {
                fragcolor = gl_Color;
//                fragcolor=out_color;
            }
            break;
        }
*/
    }
    gl_FragColor=fragcolor;
}

