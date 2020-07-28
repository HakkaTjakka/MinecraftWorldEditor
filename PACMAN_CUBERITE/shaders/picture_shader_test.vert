uniform float wave_phase;
uniform vec2 wave_amplitude;
uniform vec2 pos_correction;
uniform vec2 pos_correction2;
uniform vec2 pos_abs;
uniform float iTime;

#define PI 3.141592653589793


void main()
{
    vec4 vertex = gl_Vertex;
//    vec4 vertex2 = gl_Vertex;
	vec2 scale_correction;
    float ang;

//	vertex.x -= pos_correction.x;
//	vertex.y -= pos_correction.y;

    vec2 krimp=(1.0-cos( (pos_abs+0.5)*PI*4 ))/2.0;

    vertex.x=vertex.x - (vertex.x-pos_correction2.x)*(sqrt(krimp.x*krimp.x+krimp.y*krimp.y)/4.0);

//    vertex.x=vertex.x - ((vertex.x-pos_correction2.x))*(sqrt(pos_abs.x*pos_abs.x+pos_abs.y*pos_abs.y))*2.0;
//    vertex.x=vertex.x - ((vertex.x-pos_correction2.x))*(sqrt(krimp.x*krimp.x+krimp.y*krimp.y))/3.0;
//    vertex.x=vertex.x - ((vertex.x-pos_correction2.x)-1920.0/2.0)*(sqrt(krimp.x*krimp.x+krimp.y*krimp.y))/2.0;

//    vertex.xy=vertex.xy - (vertex.xy-vec2(1920.0/2.0,1080.0/2.0))/(1.5+krimp);

//    vec2 vert_center=vertex.xy  - vec2(1920.0/2.0,1080.0/2.0) ;

    vec2 vert_center=vertex.xy  - pos_correction2.xy ;
//    if (pos_abs.x!=0) {
        ang=atan(pos_abs.y,pos_abs.x);
//    } else {
//        ang=PI/2;
//    }
//    ang=iTime/1.0;
//    ang=0.3;
    vec2 vert_rot;
    vert_rot.x=vert_center.x*cos(ang)-vert_center.y*sin(ang);
    vert_rot.y=vert_center.x*sin(ang)+vert_center.y*cos(ang);
//    vertex.xy=vert_rot.xy + vec2(1920.0/2.0,1080.0/2.0);
//    vertex.xy=vert_rot.xy + vec2(1920.0/2.0,1080.0/2.0) ;
    vertex.xy=vert_rot.xy + pos_correction2.xy ;


//    vec2 ret=vec2(1920.0/2.0,1080.0/2.0);
//    vert_rot.x=ret.x*cos(ang)-ret.y*sin(ang);
//    vert_rot.y=ret.x*sin(ang)+ret.y*cos(ang);
//    vertex.xy=vertex.xy - vert_rot.xy;//  + vec2(1920.0/2.0,1080.0/2.0);

//    vertex.w=0;
//    vec3 norm=gl_Normal;
//    norm.x=gl_Normal.x*cos(ang)-gl_Normal.y*sin(ang);
//    norm.y=gl_Normal.x*sin(ang)+gl_Normal.y*cos(ang);



//	scale_correction.x=abs(vertex2.x)/(abs(vertex2.x)+1.3 * wave_amplitude.x); // 1.3 is to correct vertex to be maximal original value (for plotting not larger than calculated in program) (max sin/cos functions result).
//	scale_correction.y=abs(vertex2.y)/(abs(vertex2.y)+1.3 * wave_amplitude.y);

//	vertex.x += 1.3 * wave_amplitude.x ;
//	vertex.y += 1.3 * wave_amplitude.y ;

//	vertex.x += 2.6 * wave_amplitude.x ;
//	vertex.y += 2.6 * wave_amplitude.y ;

//    vec4 vertex2=vertex;
//    vertex2.xy=vertex2.xy-pos_correction2.xy;

//    vertex.x =  vertex.x + (cos(vertex2.x * 0.02 + wave_phase * 3.8)  + sin(vertex2.y * 0.02 + wave_phase * 6.3) * 0.3 ) * wave_amplitude.x;
//    vertex.y =  vertex.y + (sin(vertex2.y * 0.02 + wave_phase * 2.4)  + cos(vertex2.x * 0.02 + wave_phase * 5.2) * 0.3 ) * wave_amplitude.y;


//    vertex.x =  vertex.x + (cos(vertex2.y * 0.02 + wave_phase * 3.8)  + sin(vertex2.y * 0.02 + wave_phase * 6.3) * 0.3 ) * wave_amplitude.x;
//    vertex.y =  vertex.y + (sin(vertex2.x * 0.02 + wave_phase * 2.4)  + cos(vertex2.x * 0.02 + wave_phase * 5.2) * 0.3 ) * wave_amplitude.y;

//tuut
//    vertex.x =  vertex.x + (cos( wave_phase * 50.0)  + sin( wave_phase * 50.0) * 0.3 ) * wave_amplitude.x*2.0;
//    vertex.y =  vertex.y + (sin( wave_phase * 50.0)  + cos( wave_phase * 50.0) * 0.3 ) * wave_amplitude.y*2.0;

//	vertex.x = vertex.x * scale_correction.x; //adjust scaling for plotting (preserve size).
//	vertex.y = vertex.y * scale_correction.y;

    gl_Position = gl_ModelViewProjectionMatrix * vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
