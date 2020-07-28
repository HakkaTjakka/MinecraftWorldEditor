//#version 400

uniform sampler2D the_texture;
//in vec2 gl_SamplePosition;
//out vec4 gl_FragColor;
//in vec4 gl_Color;
//in vec2 gl_Position;
uniform bool WIRE_FRAME;
uniform bool TEXTURE_ARRAY;
uniform bool COLOR_ARRAY;
varying vec4 out_color;

void main()
{
	float z = gl_FragCoord.z / gl_FragCoord.w;
//	fragColor = (gl_Color + vec4( vec3(z), 1.0) ) / 2.0;
//	gl_FragColor = vec4( vec3(z), 1.0);


//	gl_FragColor = (  texture2D(the_texture,  gl_TexCoord[0].xy)  +  vec4( vec3(z), 1.0)  )  /  2.0;
//	gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy)*(1.0-z/3.0);

//	if (TEXTURE_ARRAY) {
        if (COLOR_ARRAY) {
//            gl_FragColor=out_color;
            int tot=int(z*(256.0*256.0*256.0-1));
            float red=float(tot >> 16)/256.0;
            float green=float(tot&0xFF00 >> 8)/256.0;
            float blue=float(tot&0xFF )/256.0;
//            float green=0.0;
//            float blue=0.0;
            gl_FragColor =  vec4(red,green,blue,1.0);
//            gl_FragColor =  vec4(1.0,1.0,0.0,1.0)*(1.0-z/3.0);
        }
        else if (TEXTURE_ARRAY) { gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy); }
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
            gl_FragColor =  vec4(1.0,1.0,0.0,1.0)*(1.0-z/3.0);
        }
//        if (WIRE_FRAME) gl_FragColor =  out_color;

//        if (COLOR_ARRAY) { gl_FragColor=gl_FrontColor; }
//        else if (TEXTURE_ARRAY) { gl_FragColor =  texture2D(the_texture,  gl_TexCoord[0].xy); }
//        if (WIRE_FRAME) gl_FragColor =  gl_Color;

//	}
}

