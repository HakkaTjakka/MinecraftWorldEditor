//#version 460 core
//#version 330 core
uniform sampler2D texture_in;
//uniform sampler2D texture_current;
//uniform ivec2 texture_size;
uniform vec2 iResolution;
uniform vec2 iObject;
//in vec4 tex_coord;
//in vec3 colour;

//out vec4 out_Color;

/*
void main() {
    int x;
    int y;
    vec4 col;
//    gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    for (y=0; y<texture_size.y; y++) {
        for (x=0; x<texture_size.x; x++) {
            col=texelFetch(texture_in, ivec2( x,y ) , 0);
//            vec4 col=texture(texture_in,vec2(x,y)/vec2(1920.0,1080.0));
            if (col.a!=0.0) {
                out_Color = vec4(1.0,1.0,1.0,1.0);
//                gl_FragColor = vec4(1.0,1.0,1.0,1.0);
                return;
//                if (texelFetch(texture, ivec2( x,y ) , 0))!=vec4(0.0,0.0,0.0,0.0) {
//                if (texture2D(texture,vec2((float)x/1920.0,(float)y/1080.0)).xyz!=vec3(0.0,0.0,0.0)) {
//                if (texture2D(texture,vec2((float)x/1920.0,(float)y/1080.0)).xyz!=vec3(0.0,0.0,0.0)) {
            }
        }
    }
    out_Color = vec4(0.0,0.0,0.0,0.0);
}
*/

void main() {
    int x;
    int y;
    vec4 col;

//    if (gl_FragCoord.y<10 && gl_FragCoord.x<10) {
//        gl_FragColor=vec4(1.0,0.0,0.0,1.0);
//        return;
//    }
/*        for (y=0; y<texture_size.y; y++) {
            for (x=0; x<texture_size.x; x++) {
                col=texture(texture_in,((vec2(x,y)+vec2(0.5,0.5))/iResolution));
                if (col.r!=0.0) {
                    gl_FragColor=vec4(1.0,1.0,1.0,1.0);
                    return;
                }
            }
        }
    }
    gl_FragColor=vec4(0.0,0.0,0.0,1.0);
*/
//    gl_FragColor=vec4((gl_FragCoord+vec2(0.5,0.5))/iResolution , 0.0 , 1.0 );

    col=texture(texture_in,((gl_FragCoord.xy)/iResolution));
    if (col.r>0.0) {
        float blue=fract((1.0+iObject.x)*(1.0+iObject.y)/16.0);
        gl_FragColor=vec4(iObject.x/256.0,iObject.y/256.0,blue,1.0);
    } else {
        gl_FragColor=vec4(0.0,0.0,0.0,0.0);
    }

//    gl_FragColor=texture(texture_in,((gl_FragCoord.xy)/iResolution));
}
