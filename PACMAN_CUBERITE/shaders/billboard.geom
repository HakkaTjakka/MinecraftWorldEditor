#version 150
uniform float iTime;
uniform int draw_mode;
uniform int num_pacman;
uniform vec2 draw_scale;
uniform vec2 resolution;
//uniform float iZoom;
uniform vec2 BITMAPS;
uniform vec2 render_pos;
uniform vec2 size;
uniform vec3 translate;
uniform vec3 rotate;
uniform mat4 perspective;
uniform int draw_model;
uniform vec2 wave_amplitude;
#define PI 3.141592653589793

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
out vec4 tex_coord;

int ok;
vec2 half_size;
vec2 draw_scale_adj=draw_scale;
//vec2 draw_scale_adj=(draw_scale+sin(rotate.x+rotate.y)*draw_scale/2.0)*1.5;
int draw_mode_off=draw_mode;
float aspect = resolution.x / resolution.y;

float c_x = cos(rotate.x);
float s_x = sin(rotate.x);
float c_y = cos(rotate.y);
float s_y = sin(rotate.y);
float c_z = cos(rotate.z);
float s_z = sin(rotate.z);

//float c_x = cos( sin(rotate.x     +sin(rotate.x*1.28)/2.0)/2.0);
//float s_x = sin( sin(rotate.x*2.12+sin(rotate.y*2.43)/2.0)/2.0);
//float c_y = cos( sin(rotate.y*1.23+sin(rotate.y*1.84)/2.0)/2.0);
//float s_y = sin( sin(rotate.y*1.69+sin(rotate.z*1.29)/2.0)/2.0);
//float c_z = cos( sin(rotate.z*1.45+sin(rotate.z*2.11)/2.0)/2.0);
//float s_z = sin( sin(rotate.z*1.98+sin(rotate.x*1.82)/2.0)/2.0);

mat4 rotateXYZ =
    mat4(   vec4(1,   0,    0, 0),
            vec4(0, c_x, -s_x/aspect, 0),
            vec4(0, s_x*aspect,  c_x, 0),
            vec4(0,   0,    0, 1)                       ) *
    mat4(   vec4( c_y, 0, s_y, 0),
            vec4(   0, 1,   0, 0),
            vec4(-s_y, 0, c_y, 0),
            vec4(   0, 0,   0, 1)                       ) *
    mat4(   vec4(c_z,           -s_z*aspect,    0, 0),
            vec4(s_z/aspect,    c_z,            0, 0),
            vec4(0,             0,              1, 0),
            vec4(0,             0,              0, 1)   );

float wave_x1 = wave_amplitude.x/(1920.0/3.0*(draw_scale.x+0.2));
float wave_y1 = wave_amplitude.y/(1080.0/3.0*(draw_scale.y+0.2));
float wave_x2 = 0.02 * 1920.0;
float wave_y2 = 0.02 * 1080.0;
float wave_a1 = iTime * 5.8;
float wave_a2 = iTime * 7.3;
float wave_a3 = iTime * 4.4;
float wave_a4 = iTime * 6.2;
vec2 render_offset=vec2(render_pos.x/1920.0*2.0,render_pos.y/1080.0*2.0)/draw_scale;
vec4 col;
int skip_x;
int skip_y;

vec4 make_vertex(int number,vec2 pos) {
    vec4 vertex_in=vec4(pos.x,pos.y,0.0f,1.f);
    vec4 vertex=vertex_in;

    if (draw_mode_off>=1) {
        if (col.r!=1.0) {

            if (skip_x==0) vertex_in.x += ( cos(-(pos.y-render_offset.y) * wave_y2 + wave_a1+col.g*33.23)  + sin(-(pos.y-render_offset.y) * wave_y2 + wave_a2+col.g*29.34) * 0.3 ) * wave_x1;
            if (skip_y==0) vertex_in.y += ( sin( (pos.x+render_offset.x) * wave_x2 + wave_a3+col.g*21.12)  + cos( (pos.x+render_offset.x) * wave_x2 + wave_a4+col.g*23.98) * 0.3 ) * wave_y1;
//            if (skip_x==0) vertex_in.x += ( cos(-pos.y * wave_y2 + wave_a1+col.g*33.23)  + sin(-pos.y * wave_y2 + wave_a2+col.g*29.34) * 0.3 ) * wave_x1;
//            if (skip_y==0) vertex_in.y += ( sin( pos.x * wave_x2 + wave_a3+col.g*31.12)  + cos( pos.x * wave_x2 + wave_a4+col.g*29.98) * 0.3 ) * wave_y1;
            vertex=vertex_in;
        }
        if (draw_mode_off==2) {
            switch(draw_model){
                case 0 : {
                    vertex = rotateXYZ * vertex;
                    vertex.xyz+=translate/100.0;

//                    vertex.xy = vertex.xy/(vertex.z * 0.5 + 1.0);
//                    vertex.z = vertex.z/(vertex.z * 0.25 + 2.5);

                    vertex.z+=-1.0;
                    vertex*=perspective;
                    break;
                }
                case 1 : {
//            vertex.z = cos(vertex.y*draw_scale_adj.y*PI/25.0)/draw_scale.y*2.5;
//            vertex.y = sin(vertex.y*draw_scale_adj.y*PI/25.0 )/draw_scale.y*2.5;
                    vertex.z = cos(vertex.x*draw_scale_adj.x*PI/8.0)/draw_scale.x*2.5;
                    vertex.x = sin(vertex.x*draw_scale_adj.x*PI/8.0 )/draw_scale.x*2.5;
                    vertex = rotateXYZ * vertex;
                    vertex.xyz+=translate/100.0;
                    vertex.z+=-1.0;
                    vertex*=perspective;
                    break;
                }
                case 2 : {
                    vertex_in.z = cos(vertex_in.x*draw_scale_adj.x*PI/8.0)/draw_scale.x*2.5;
                    vertex_in.x = sin(vertex_in.x*draw_scale_adj.x*PI/8.0 )/draw_scale.x*2.5;

                    vertex_in.x=vertex_in.x-2.0/draw_scale_adj.x*2.5;

                    vertex.y = -vertex_in.x*sin(vertex_in.y*draw_scale_adj.y*PI/8.0)*aspect;
                    vertex.x = vertex_in.x*cos(vertex_in.y*draw_scale_adj.y*PI/8.0);
                    vertex.z=vertex_in.z;

                    vertex = rotateXYZ * vertex;
                    vertex.xyz+=translate/100.0;
                    vertex.z+=-1.0;
                    vertex*=perspective;
                    break;
                }
                case 3 : {
                    vertex.z += (   sin(   .5*(vertex.x+render_pos.x/(960.0*draw_scale.x))*draw_scale.x*PI/.5+iTime*2.0   )
                                +  cos(   -.5*(vertex.y+(render_pos.y)/(-540.0*draw_scale.y))*-draw_scale.y*PI/.5+iTime*2.4)   )/draw_scale.x/10.0;
                    vertex.z += (   sin(   .33*(vertex.x/2.0+render_pos.x/(960.0*draw_scale.x))*draw_scale.x*PI/.5+iTime*.97   )
                                +  cos(   -.29*(vertex.y/2.0+(render_pos.y)/(-540.0*draw_scale.y))*-draw_scale.y*PI/.5+iTime*1.022)   )/draw_scale.x/5.0;
                    vertex = rotateXYZ * vertex;
                    vertex.xyz+=translate/100.0;
                    vertex.z+=-1.0;
                    vertex*=perspective;
                    break;
                }
            }
        } else {
            vertex=vertex_in;
        }
    } else {
        vertex=vertex_in;
    }
//    vertex.xy=vertex.xy*iZoom;
    if (vertex.z > -0.4 -0.5 && vertex.z < 5.0) ok=1;
//    ok=1;
    vertex.z-=0.005;
    return vertex;
}

vec2 half_size_factor = 256.0/(resolution*draw_scale);
vec2 scalar = BITMAPS/draw_scale;
void main()
{
    col = gl_in[0].gl_FrontColor;
    if (col.ba==vec2(0.0,0.0)) return;

    vec2 pos = gl_in[0].gl_Position.xy;
    vec4 coord = gl_in[0].gl_TexCoord[0];


    switch(draw_mode_off){
        case 0 : {
            if (pos.x>8.0/draw_scale.x) pos.x=-scalar.x+(pos.x-scalar.x);
            if (abs(pos.y*draw_scale.y)>(8.0)) return;
            if (abs(pos.x*draw_scale.x)>(8.0)) return;
            break;
        }
        case 1 : {
            if (pos.x>7.0/draw_scale.x) pos.x=-scalar.x+(pos.x-scalar.x);
            if (abs(pos.x*draw_scale.x)>(1.1)) return;
            if (abs(pos.y*draw_scale.y)>(1.1)) return;
            break;
        }
        case 2 : {
            if (pos.x>(BITMAPS.x)/draw_scale.x) pos.x=-scalar.x+(pos.x-scalar.x);
//            if (pos.x<(-BITMAPS.x/2.0)/draw_scale.x) pos.x=scalar.x+(-pos.x-scalar.x);
            break;
        }
    }

/*
    if (draw_mode_off==0) {                 //radar screen
        if (pos.x>8.0/draw_scale.x) pos.x=-scalar.x+(pos.x-scalar.x);
        if (abs(pos.y*draw_scale.y)>(8.0)) return;
        if (abs(pos.x*draw_scale.x)>(8.0)) return;
    } else if (draw_mode_off==1) {          // plot_all==0
        if (pos.x>8.0/draw_scale.x) pos.x=-scalar.x+(pos.x-scalar.x);
        if (abs(pos.x*draw_scale.x)>(1.1)) return;
        if (abs(pos.y*draw_scale.y)>(1.1)) return;
    } else if (draw_mode_off==2) {          // plot_all==1
//        if (pos.x>(BITMAPS.x/2.0)/draw_scale.x) pos.x=-scalar.x+(pos.x-scalar.x);
        if (pos.x<-4.0/draw_scale.x) pos.x=-scalar.x+(pos.x-scalar.x);
    }
*/


    half_size = col.ba*half_size_factor;

    ok=0;
    int test=int(col.r*256.0);
    vec4 Position1;
    vec4 Position2;
    vec4 Position3;
    vec4 Position4;

    if (test>0) {
        if ((test&8)==8) skip_x=1; else skip_x=0;
        if ((test&2)==2) skip_y=1; else skip_y=0;
        Position1 = make_vertex(1,vec2(pos.x + half_size.x, pos.y - half_size.y));
        if (abs(Position1.x)>1.05 || abs(Position1.y)>1.05) return;

        if ((test&4)==4) skip_x=1; else skip_x=0;
        if ((test&2)==2) skip_y=1; else skip_y=0;
        Position2 = make_vertex(2,pos - half_size);

        if ((test&8)==8) skip_x=1; else skip_x=0;
        if ((test&1)==1) skip_y=1; else skip_y=0;
        Position3 = make_vertex(3,pos + half_size);

        if ((test&4)==4) skip_x=1; else skip_x=0;
        if ((test&1)==1) skip_y=1; else skip_y=0;
        Position4 = make_vertex(4,vec2(pos.x - half_size.x, pos.y + half_size.y));
    } else {
        Position1 = make_vertex(1,vec2(pos.x + half_size.x, pos.y - half_size.y));
        if (abs(Position1.x)>1.05 || abs(Position1.y)>1.05) return;
        Position2 = make_vertex(2,pos - half_size);
        Position3 = make_vertex(3,pos + half_size);
        Position4 = make_vertex(4,vec2(pos.x - half_size.x, pos.y + half_size.y));
    }

    if (ok==0) return;

    half_size=col.ba*256.0;

    gl_Position=Position1;
    tex_coord.xy = coord.xy+half_size;
    EmitVertex();

    gl_Position=Position2;
    tex_coord.xy = coord.xy + vec2(0.f, half_size.y);
    EmitVertex();

    gl_Position=Position3;
    tex_coord.xy = coord.xy+vec2(half_size.x,0.f);
    EmitVertex();

    gl_Position=Position4;
    tex_coord.xy = coord.xy;
    EmitVertex();

    EndPrimitive();

}
