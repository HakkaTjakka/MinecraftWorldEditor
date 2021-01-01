uniform int whattodo;
uniform float wave_phase;
uniform sampler2D the_texture;
uniform bool WIRE_FRAME;
uniform bool TEXTURE_ARRAY;
uniform bool COLOR_ARRAY;
varying vec4 out_color;
//varying float hit_mouse;
varying float hit_center_rot;
varying float hit_center;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float ratio;
varying float my_light;

void main() {
    switch(whattodo) {
        case 0 : {
            if (TEXTURE_ARRAY) {
                gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy);
                float hit_center_screen=( sqrt(pow(gl_FragCoord.x/resolution.x-0.5,2.0)+pow(ratio*(gl_FragCoord.y/resolution.y-0.5),2.0)) );

                if (hit_center_screen<0.005) {
                    float add=1.0;
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
            } else if (COLOR_ARRAY) {
                float z = gl_FragCoord.z / gl_FragCoord.w;
                int tot=int(z*(256.0*256.0*256.0-1));
                float red=float(tot >> 16)/256.0;
                float green=float(tot&0xFF00 >> 8)/256.0;
                float blue=float(tot&0xFF )/256.0;
               gl_FragColor =  vec4(red,green,blue,1.0);
            }
            if (WIRE_FRAME) {
                float z = gl_FragCoord.z / gl_FragCoord.w;
                gl_FragColor =  vec4(1.0,1.0,0.0,1.0)*(1.0-z/3.0);
            }
            break;
        }
        case 2 : {
            if (TEXTURE_ARRAY) {
                gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy);
            }
            else if (WIRE_FRAME) {
                gl_FragColor = gl_Color;
            }
            else if (COLOR_ARRAY) {
                gl_FragColor = gl_Color;
            }
            break;
        }
        case 1 : {
            if (TEXTURE_ARRAY) {
                gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy);
            }
            else if (WIRE_FRAME) {
                gl_FragColor =  gl_Color;
            }
            else if (COLOR_ARRAY) {
                gl_FragColor=gl_Color;
            }
            break;
        }
        case 3 : {
            gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy);
            gl_FragColor.rgb = gl_FragColor.rgb * my_light;
            break;
        }
    }
}

