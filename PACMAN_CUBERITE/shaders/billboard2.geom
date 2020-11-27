#version 150
uniform float iTime;
uniform int draw_mode;
uniform int num_pacman;
uniform vec2 draw_scale;
uniform vec2 draw_translate;
uniform vec2 resolution;
//uniform float iZoom;
uniform vec2 BITMAPS;
uniform vec2 render_pos;
uniform vec2 size;
uniform vec2 mappos;
uniform vec2 ar;
uniform vec3 translate;
uniform vec3 rotate;
uniform mat4 perspective;
uniform int draw_model;
#define PI 3.141592653589793

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;
out vec4 tex_coord;

int ok;
vec2 half_size = 2.0*size/(resolution*draw_scale);
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

vec4 make_vertex(vec2 pos) {
    vec4 vertex_in=vec4(pos.x,pos.y,0.0f,1.f);
    vec4 vertex=vertex_in;

    switch(draw_model){
        case 0 : {
            break;
        }
        case 1 : {
            vertex.z = cos(vertex.x*draw_scale_adj.x*PI/8.0)/draw_scale.x*2.5;
            vertex.x = sin(vertex.x*draw_scale_adj.x*PI/8.0)/draw_scale.x*2.5;
            break;
        }
        case 2 : {
            vertex_in.z = cos(vertex_in.x*draw_scale_adj.x*PI/8.0)/draw_scale.x*2.5;
            vertex_in.x = sin(vertex_in.x*draw_scale_adj.x*PI/8.0 )/draw_scale.x*2.5;
            vertex_in.x=vertex_in.x-2.0/draw_scale_adj.x*2.5;
            vertex.y = vertex_in.x*sin(vertex_in.y*draw_scale_adj.y*PI/8.0)*aspect;
            vertex.x = vertex_in.x*cos(vertex_in.y*draw_scale_adj.y*PI/8.0);
            vertex.z=vertex_in.z;
            break;
        }
        case 3 : {
            vertex.z += (   sin(   .5*(vertex.x  +render_pos.x/(960.0*draw_scale.x))*draw_scale.x*PI/.5+iTime*2.0   )
                         +  cos(  -.5*(vertex.y  +render_pos.y/(540.0*draw_scale.y))*draw_scale.y*PI/.5+iTime*2.4   )   )/draw_scale.x/10.0;
            vertex.z += (   sin(   .33*(vertex.x/2.0+render_pos.x/(960.0*draw_scale.x))*draw_scale.x*PI/.5+iTime*.97   )
                         +  cos(  -.29*(vertex.y/2.0+render_pos.y/(540.0*draw_scale.y))*draw_scale.y*PI/.5+iTime*1.022 )   )/draw_scale.x/5.0;
            break;
        }
    }

    vertex = rotateXYZ * vertex;
    vertex.xyz+=translate/100.0;
    vertex.z+=-1.0;
    vertex.w=1.0;
    vertex=vertex*perspective;
//    vertex.x=vertex.x/(vertex.w);
//    vertex.y=vertex.y/(vertex.w);
//    vertex.z=vertex.z/(vertex.w);

//    vertex.xy=vertex.xy*iZoom;

//    if (vertex.z > -0.5 && vertex.z < 5.0) ok=1;
    if (vertex.z > -0.4 -0.5 && vertex.z < 5.0) ok=1;
//  ok=1;
    return vertex;
}

vec2 adapt=vec2(1.0,-1.0) * (1.0+2.0*(draw_translate/resolution)) / draw_scale + vec2(-1.0,1.0);

void main()
{
        vec4 col = gl_in[0].gl_FrontColor;
        gl_FrontColor = col;
        vec2 pos = gl_in[0].gl_Position.xy / draw_scale + adapt;

        vec4 coord = vec4(
            (1.0+vec2(1.0,-1.0)*(gl_in[0].gl_Position.xy)) * resolution/2.0,
            0.0,0.0
             );

// 8x8 texture
//        vec2 large= vec2(0.0,1.0)+vec2(1.0,-1.0)*(mappos-vec2(.5,-1.5))/vec2(8.0,8.0) ;
//        gl_FrontColor.rg= large + (1.0+vec2(1.0,-1.0)*(gl_in[0].gl_Position.xy ) / 2.0)/vec2(8.0,8.0)  ;

//one of 8x8 textures
//       gl_FrontColor.ba=(1.0+vec2(1.0,-1.0)*(gl_in[0].gl_Position.xy)) /2.0;

        ok=0;
        vec4 Position1 = make_vertex(vec2(pos.x + half_size.x, pos.y));
        vec4 Position2 = make_vertex(pos );
        vec4 Position3 = make_vertex(pos + half_size);
        vec4 Position4 = make_vertex(vec2(pos.x , pos.y + half_size.y));


        if (ok==1) {
            gl_Position=Position1;
            tex_coord.xy = coord.xy+size;
            tex_coord.zw = gl_FrontColor.ba+size;

            EmitVertex();

            gl_Position=Position2;
            tex_coord.xy = coord.xy + vec2(0.f, size.y);
            tex_coord.zw = gl_FrontColor.ba+ vec2(0.f, size.y);
            EmitVertex();

            gl_Position=Position3;
            tex_coord.xy = coord.xy+vec2(size.x,0.f);
            tex_coord.zw = gl_FrontColor.ba+vec2(size.x,0.f);
            EmitVertex();

            gl_Position=Position4;
            tex_coord.xy = coord.xy;
            tex_coord.zw = gl_FrontColor.ba;
            EmitVertex();

            EndPrimitive();
        }

//        vec4 col = gl_in[0].gl_FrontColor;
//        if (abs(pos.y*draw_scale.y)>(7.0)) return;
//        if (pos.x>8.0/draw_scale.x) pos.x=-BITMAPS.x/draw_scale.x+(pos.x-BITMAPS.x/draw_scale.x);
//        if (abs(pos.x*draw_scale.x)>(8.0)) return;
//        if (pos.x>7.0/draw_scale.x) pos.x=-8.0/draw_scale.x+(pos.x-8.0/draw_scale.x);
//        else if (pos.x<-8.0/draw_scale.x) pos.x=8.0/draw_scale.x-(pos.x-8.0/draw_scale.x);


}

