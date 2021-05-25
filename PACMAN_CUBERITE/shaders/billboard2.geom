#version 330 compatibility
#extension GL_EXT_geometry_shader4 : enable
//#version 150
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

out vec3 ro;
out vec3 n;
out vec3 lp1;
out vec3 lp2;
out vec3 lp3;
out vec3 lp4;

vec2 draw_scale_new=draw_scale*1.0;

int ok;
//vec2 half_size = (2.000+min(draw_model,1)*0.001)*size/(resolution*draw_scale_new);
vec2 half_size = (2.000+min(draw_model,1)*0.001)*size/(resolution*draw_scale_new);

vec2 scale_adjust=draw_scale_new;

//vec2 scale_adjust=(draw_scale_new+sin(rotate.x+rotate.y)*draw_scale_new/2.0)*1.5;

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

vec4 vertex_non;

vec4 make_vertex(vec2 pos) {
    vec4 vertex_in=vec4(pos.x,pos.y,0.0f,1.f);
    vec4 vertex=vertex_in;

    switch(draw_model){
        case 0 : {
            break;
        }
        case 1 : {
            vertex.z = cos(vertex.x*scale_adjust.x*PI/8.0)/draw_scale_new.x*2.5;
            vertex.x = sin(vertex.x*scale_adjust.x*PI/8.0)/draw_scale_new.x*2.5;
            break;
        }
        case 2 : {
            vertex_in.z = cos(vertex_in.x*scale_adjust.x*PI/8.0)/draw_scale_new.x*2.5;
            vertex_in.x = sin(vertex_in.x*scale_adjust.x*PI/8.0 )/draw_scale_new.x*2.5;
            vertex_in.x=vertex_in.x-2.0/scale_adjust.x*2.5;
            vertex.y = vertex_in.x*sin(vertex_in.y*scale_adjust.y*PI/8.0)*aspect;
            vertex.x = vertex_in.x*cos(vertex_in.y*scale_adjust.y*PI/8.0);
            vertex.z=vertex_in.z;
            break;
        }
        case 3 : {
            vertex.z += (   sin(   .5*(vertex.x  +render_pos.x/(960.0*draw_scale_new.x))*draw_scale_new.x*PI/.5+iTime*2.0   )
                         +  cos(  -.5*(vertex.y  +render_pos.y/(540.0*draw_scale_new.y))*draw_scale_new.y*PI/.5+iTime*2.4   )   )/draw_scale_new.x/10.0;
            vertex.z += (   sin(   .33*(vertex.x/2.0+render_pos.x/(960.0*draw_scale_new.x))*draw_scale_new.x*PI/.5+iTime*.97   )
                         +  cos(  -.29*(vertex.y/2.0+render_pos.y/(540.0*draw_scale_new.y))*draw_scale_new.y*PI/.5+iTime*1.022 )   )/draw_scale_new.x/5.0;
            break;
        }
        case 4 : {
            vertex_in.z = cos(-vertex_in.y*scale_adjust.y*PI/8.0)/draw_scale_new.x*2.5;
            vertex_in.y = sin(vertex_in.y*scale_adjust.y*PI/8.0 )/draw_scale_new.y*2.5;
            vertex_in.y=vertex_in.y-2.0/scale_adjust.y*2.5;
            vertex.x = vertex_in.y*sin(vertex_in.x*scale_adjust.x*PI/8.0)/1.4;

            float add=(sin(iTime*4.0 ) + 1.0 )/2.0 ;
            add=clamp(add,0.95,1.00);
            add=(smoothstep( 0.0, 1.0, add)-0.95)*4.0;

            float add2=(sin(iTime*4.0-0.5 ) + 1.0 )/2.0 ;
            add2=clamp(add2,0.85,9.50);
            add2=(smoothstep( 0.0, 1.0, add2)-0.95)*5.0;

            vertex.y = vertex_in.y*cos(vertex_in.x*scale_adjust.x*PI/8.0)*(aspect );
            vertex.z=vertex_in.z;

//            vertex.y = vertex_in.y*cos(vertex_in.x*scale_adjust.x*PI/8.0)*(aspect + add2 );
//            vertex.y = vertex_in.y*cos(vertex_in.x*scale_adjust.x*PI/8.0)*(aspect + (add + add2)/3.0 );

//            vertex_in.z = cos(-vertex_in.y*scale_adjust.y*PI/8.0)/draw_scale_new.x*2.5;
//            vertex_in.y = sin(vertex_in.y*scale_adjust.y*PI/8.0 )/draw_scale_new.y*2.5;
//            vertex_in.y=vertex_in.y-2.0/scale_adjust.y*2.5;
//            vertex.x = vertex_in.y*sin(vertex_in.x*scale_adjust.x*PI/8.0)/1.4;
//            vertex.y = vertex_in.y*cos(vertex_in.x*scale_adjust.x*PI/8.0)*aspect;
//            vertex.z=vertex_in.z;
            break;
        }
        case 5 : {
            float add=(sin(iTime*6.0 - 1.0 ) + 1.0 )/2.0 ;
            add=clamp(add,0.95,1.00);
            add=(smoothstep( 0.0, 1.0, add)-0.95)*8.0;

            float add2=(sin(iTime*6.0-0.5 ) + 1.0 )/2.0 ;
            add2=clamp(add2,0.85,9.50);
            add2=(smoothstep( 0.0, 1.0, add2)-0.95)*5.0;

            vertex.z =  cos(vertex.x*scale_adjust.x*PI/32.0)/draw_scale_new.x*2.5;
            vertex.z -= cos(vertex.y*scale_adjust.y*PI/32.0)/draw_scale_new.y*2.5;
//            vertex.z *=(1.0 + (add + add2)/1.8 );
            vertex.x = sin(vertex.x*scale_adjust.x*PI/64.0)/draw_scale_new.x*5.0;
//            vertex.x =vertex.x/2.5;
            vertex.y = sin(vertex.y*scale_adjust.y*PI/32.0)/draw_scale_new.y*2.5;
            break;
        }
        case 6 : {
//            vertex.z = cos(vertex.x*scale_adjust.x*PI/8.0)/draw_scale_new.x*2.5;
//            vertex.x = sin(vertex.x*scale_adjust.x*PI/8.0)/draw_scale_new.x*2.5;
//            break;

//            vertex.x = (vertex_in.x - 0.5)*s_x + (vertex_in.x - 0.5)*c_x;
//            vertex.y = (vertex_in.y - 0.5)*c_x + (vertex_in.y - 0.5)*s_x;


            vertex.z = -cos(vertex.y*scale_adjust.y*PI/20.0)/draw_scale_new.y*6.0/aspect;
            vertex.y = sin(vertex.y*scale_adjust.y*PI/20.0)/draw_scale_new.y*6.0;
            break;
        }
    }

    vertex = rotateXYZ * vertex;
    vertex.xyz+=translate/100.0;
    vertex.z+=-1.0;
    vertex.w=1.0;

    vertex_non=vertex;

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

vec2 adapt=vec2(1.0,-1.0) * (1.0+2.0*(draw_translate/resolution)) / draw_scale_new + vec2(-1.0,1.0);


vec2 normal_size = half_size/2.0;

//void do_pong(vec3 Normal) {
void do_pong(vec2 Position) {

//            n=calcNormal(Position);
//            n=calcNormal(Position).xyz;


            make_vertex( Position-vec2(normal_size.x/2.0,0.0) );
            vec4 Position1=vertex_non;

            make_vertex( Position+vec2(normal_size.x/2.0,0.0) );
            vec4 Position2=vertex_non;

            make_vertex( Position-vec2(0.0,normal_size.y/2.0) );
            vec4 Position3=vertex_non;

            Position1.y*=aspect;
            Position2.y*=aspect;
            Position3.y*=aspect;
            vec4 A = Position3 - Position1;
            vec4 B = Position2 - Position1;

            n = normalize(cross(A.xyz,B.xyz));

//            ro = normalize( (  vec4(0.0, .0, -1.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0


//            n = normalize(Normal);



            if (draw_model<=5) {
                ro = normalize( (  vec4(0.0, 0.0, 2.0, 1.0) ).xyz) ; // zzzzz 2.0
                vec2 off1=6.4*vec2( sin(PI+iTime/11.3) ,    cos(PI+iTime/11.3) )  ;
                vec2 off2=6.4*vec2( sin(iTime/11.3) ,    cos(iTime/11.3) )  ;
                vec2 off3=6.4*vec2( sin(iTime/5.3) ,    cos(iTime/5.9) )  ;
                vec2 off4=6.4*vec2( sin(iTime/4.9) ,    cos(iTime/4.6) )  ;
                lp1=normalize( (  vec4( off1.x*3.0,  -4.0+off1.y,  -4.0, 1.0)         ).xyz) ; // zzzzz 2.0
                lp2=normalize( (  vec4( off2.x*2.5,  -2.0+off2.y,  -5.0, 1.0)         ).xyz) ; // zzzzz 2.0
                lp3=normalize( (  vec4( off3.x*3.0,  -4.0+off3.y,  -6.0, 1.0)         ).xyz) ; // zzzzz 2.0
                lp4=normalize( (  vec4( off4.x*3.5,  -4.0+off4.y,  -7.0, 1.0)         ).xyz) ; // zzzzz 2.0
            } else {
                if (draw_model==5) {
                    ro = normalize( (  vec4(0.0, 0.0, 2.0, 1.0) ).xyz) ; // zzzzz 2.0
                    vec2 off1=6.4*vec2( sin(PI+iTime/3.3) ,    cos(PI+iTime/4.3) )  ;
                    vec2 off2=6.4*vec2( sin(iTime/6.3) ,    cos(iTime/11.3) )  ;
                    vec2 off3=6.4*vec2( sin(iTime/5.3) ,    cos(iTime/5.9) )  ;
                    vec2 off4=6.4*vec2( sin(iTime/4.9) ,    cos(iTime/4.6) )  ;
                    lp1=normalize( (  vec4( off1.x*2.0,  -1.0+off1.y,  -14.0, 1.0)         ).xyz) ; // zzzzz 2.0
                    lp2=normalize( (  vec4( off2.x*1.5+off1.x*0.5,  1.0+off2.y,  -15.0, 1.0)         ).xyz) ; // zzzzz 2.0
                    lp3=normalize( (  vec4( off3.x*2.0+off4.y,  -2.0+off3.y+off2.x,  -16.0, 1.0)         ).xyz) ; // zzzzz 2.0
                    lp4=normalize( (  vec4( off4.x*2.5,  2.0+off4.y+off1.x,  -17.0, 1.0)         ).xyz) ; // zzzzz 2.0
                } else {
                    ro = normalize( (  vec4(0.0, 0.0, 12.0, 1.0) ).xyz) ; // zzzzz 2.0
                    lp1=normalize( (  vec4(-0.25  ,-1.0 ,-5.0, 1.0)         ).xyz) ;
                    lp2=normalize( (  vec4(-0.125 ,-1.125-1.25 ,-3.0, 1.0)         ).xyz) ;
                    lp3=normalize( (  vec4( 0.125 , 1.125-0.75 ,-3.0, 1.0)         ).xyz) ;
                    lp4=normalize( (  vec4( 0.25  , 2.25 +0.0 ,-3.0, 1.0)         ).xyz) ;
                }
            }

//            lp1=normalize( (  vec4( off4.x,   0.0 -(+1.0+off1.y/8.8), off4.y, 1.0) *      gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
//            lp2=normalize( (  vec4( off2.x,   1.0 +1.0+off1.x/8.8, off2.y, 1.0) *         gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
//            lp3=normalize( (  vec4(-off4.x,   1.0 +off2.x/8.8, -off4.y, 1.0) *            gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
//            lp4=normalize( (  vec4(-off2.x,  -1.0 -(1.0+off2.y/8.8), -off2.y, 1.0) *      gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0



//            z_=3.0-gl_Position.z/3.0;
}



void main()
{
        vec4 col = gl_in[0].gl_FrontColor;
        gl_FrontColor = col;
        vec2 pos = gl_in[0].gl_Position.xy / draw_scale_new + adapt;

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

        vec3 A;
        vec3 B;
        vec3 Normal;

        if (ok==1) {

//            A = Position3.xyz - Position1.xyz;
//            B = Position2.xyz - Position1.xyz;
//            Normal = normalize(cross(A,B));
//            do_pong(Normal);

do_pong(vec2(pos.x + half_size.x, pos.y));

//            do_pong(Position_non1.xyz);

            gl_Position=Position1;
            tex_coord.xy = coord.xy+size;
            tex_coord.zw = gl_FrontColor.ba+size;
            EmitVertex();

do_pong(pos );

//            do_pong(Position_non2.xyz);

            gl_Position=Position2;
            tex_coord.xy = coord.xy + vec2(0.f, size.y);
            tex_coord.zw = gl_FrontColor.ba+ vec2(0.f, size.y);
            EmitVertex();

do_pong(pos + half_size);

//            do_pong(Position_non3.xyz);

            gl_Position=Position3;
            tex_coord.xy = coord.xy+vec2(size.x,0.f);
            tex_coord.zw = gl_FrontColor.ba+vec2(size.x,0.f);
            EmitVertex();

do_pong(vec2(pos.x , pos.y + half_size.y));

//            do_pong(Position_non4.xyz);

            gl_Position=Position4;
            tex_coord.xy = coord.xy;
            tex_coord.zw = gl_FrontColor.ba;
            EmitVertex();

            EndPrimitive();
        }

//        vec4 col = gl_in[0].gl_FrontColor;
//        if (abs(pos.y*draw_scale_new.y)>(7.0)) return;
//        if (pos.x>8.0/draw_scale_new.x) pos.x=-BITMAPS.x/draw_scale_new.x+(pos.x-BITMAPS.x/draw_scale_new.x);
//        if (abs(pos.x*draw_scale_new.x)>(8.0)) return;
//        if (pos.x>7.0/draw_scale_new.x) pos.x=-8.0/draw_scale_new.x+(pos.x-8.0/draw_scale_new.x);
//        else if (pos.x<-8.0/draw_scale_new.x) pos.x=8.0/draw_scale_new.x-(pos.x-8.0/draw_scale_new.x);


}





