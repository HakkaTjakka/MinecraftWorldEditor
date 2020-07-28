#version 150
#define PI 3.141592653589793
uniform float iTime;
uniform float iZoom;
uniform int draw_mode;
uniform int num_pacman;
uniform vec2 draw_scale;
uniform vec2 fixit;
uniform vec2 resolution;
uniform vec2 render_pos;
uniform vec2 size;
uniform vec3 translate;
uniform vec3 rotate;
uniform mat4 perspective;
uniform int draw_model;
uniform vec2 wave_amplitude;

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;

out vec4 tex_coord;
out vec4 my_color;

int ok;

vec2 draw_scale_adj=draw_scale;
int draw_mode_off=draw_mode;

float iZoom2=iZoom/256.0;
float aspect = resolution.x / resolution.y;

float c_x = cos(rotate.x);
float s_x = sin(rotate.x);
float c_y = cos(rotate.y);
float s_y = sin(rotate.y);
float c_z = cos(rotate.z);
float s_z = sin(rotate.z);

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


vec4 make_vertex(vec3 pos) {
    vec4 vertex_in=vec4(pos.x,pos.y,pos.z,1.f);
    vec4 vertex=vertex_in;

    if (draw_mode_off>=1) {
        if (draw_mode_off==2) {

            switch(draw_model){
                case 0 : {
                    vertex = rotateXYZ * vertex;
                    vertex.xyz+=translate/100.0;

                    vertex.z+=-1.0;
                    vertex*=perspective;
                    break;
                }
                case 1 : {
                    vertex.z += cos(vertex.x*draw_scale_adj.x*PI/8.0)/draw_scale.x*2.5;
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

//    if (vertex.z > -0.4 -0.5 -2 && vertex.z < 5.0) ok=1;
    ok=1;
//    vertex.z-=0.005;
//    vertex.w=1.0;

//    vertex.xy=vertex.xy*iZoom;
    return vertex;
}

mat4 rotateXYZ_2;

void set_rotation(vec3 rotation) {
    c_x = cos(rotation.x);
    s_x = sin(rotation.x);
    c_y = cos(rotation.y);
    s_y = sin(rotation.y);
    c_z = cos(rotation.z);
    s_z = sin(rotation.z);
    rotateXYZ_2 =
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
}


vec2 half_size = 2.0/(resolution*draw_scale);
float adapt=512*half_size.x;

vec2 extra=(fixit+vec2(1920.0,1080.0))*vec2(2.0,-2.0)/(resolution*draw_scale);

float vertex_edge=1.00;
float texture_edge=0.0;

void main()
{
    vec4 col = gl_in[0].gl_FrontColor;
    float pos_z=col.a*adapt;
//    gl_FrontColor = col;
    my_color=col;

    vec2 pos = gl_in[0].gl_Position.xy + extra;
    vec4 coord = gl_in[0].gl_TexCoord[0];

    ok=0;
//    vec4 Position1;    vec4 Position2;    vec4 Position3;    vec4 Position4;

//    if (ok==0) return;

    coord.xy=vec2(0.0,0.0);
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y - half_size.y*vertex_edge, half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y - half_size.y*vertex_edge, half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(texture_edge,         size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y + half_size.y*vertex_edge, half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  texture_edge);           EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y + half_size.y*vertex_edge, half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(texture_edge,         texture_edge);           EmitVertex();
    EndPrimitive();

    coord.x+=256.0;
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y - half_size.y*vertex_edge, -half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y - half_size.y*vertex_edge, -half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(texture_edge,         size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y + half_size.y*vertex_edge, -half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  texture_edge);           EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y + half_size.y*vertex_edge, -half_size.x+pos_z)); tex_coord.xy = coord.xy + vec2(texture_edge,         texture_edge);           EmitVertex();
    EndPrimitive();

    coord.x+=256.0;
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y + half_size.y, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y + half_size.y, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y + half_size.y, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  texture_edge);           EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y + half_size.y, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         texture_edge);           EmitVertex();
    EndPrimitive();

    coord.x+=256.0;
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y - half_size.y, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x*vertex_edge, pos.y - half_size.y, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y - half_size.y, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  texture_edge);           EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x*vertex_edge, pos.y - half_size.y, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         texture_edge);           EmitVertex();
    EndPrimitive();

    coord.x+=256.0;
    gl_Position = make_vertex(vec3(pos.x + half_size.x, pos.y - half_size.y*vertex_edge, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x, pos.y - half_size.y*vertex_edge, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x, pos.y + half_size.y*vertex_edge, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  texture_edge);           EmitVertex();
    gl_Position = make_vertex(vec3(pos.x + half_size.x, pos.y + half_size.y*vertex_edge, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         texture_edge);           EmitVertex();
    EndPrimitive();

    coord.x+=256.0;
    gl_Position = make_vertex(vec3(pos.x - half_size.x, pos.y - half_size.y*vertex_edge, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x, pos.y - half_size.y*vertex_edge, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         size.y-texture_edge);    EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x, pos.y + half_size.y*vertex_edge, pos_z - half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(size.x-texture_edge,  texture_edge);           EmitVertex();
    gl_Position = make_vertex(vec3(pos.x - half_size.x, pos.y + half_size.y*vertex_edge, pos_z + half_size.x*vertex_edge)); tex_coord.xy = coord.xy + vec2(texture_edge,         texture_edge);           EmitVertex();
    EndPrimitive();

}
