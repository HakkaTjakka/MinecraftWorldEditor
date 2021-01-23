#version 460 compatibility


//layout(location = 0) in vec3 gl_Vertex;
//layout(location = 1) in vec3 gl_Color;
//layout(location = 2) in vec3 gl_Normal;

//out vec3 p_position;
//out vec3 p_color;
//out vec3 p_normal;

uniform bool WIRE_FRAME;
uniform bool TEXTURE_ARRAY;
uniform bool COLOR_ARRAY;
uniform int whattodo;
uniform float wave_phase;
uniform vec2 wave_amplitude;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float ratio;
uniform float maxExtent;
uniform vec3 move;
uniform vec4 add_xyz;
uniform vec3 translation;

//float time_phase=wave_phase/10.0;
float time_phase=wave_phase;
//out vec3 my_normal;

out vec3 kS_x_spec_;
out float diff_;
out vec3 ro;
out vec3 n;
out vec3 lp1;
out vec3 lp2;
out vec3 lp3;
out vec3 lp4;



//out mat4 my_modelviewmatrix;
out vec4 out_color;
out float z_;

//varying vec3 my_light;
//varying vec4 out_color;
//varying vec4 out_color;

//varying float hit_mouse;
//varying float hit_center_rot;
//varying float hit_center;

void main()
{
//    my_normal=gl_Normal.xyz;
//     p_position;
//     p_color;
//     p_normal;
    out_color = gl_Color;
//    gl_Position.x=-gl_Position.x;
//    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0);
//    mat4 m=gl_TextureMatrix[0];
//    m[3][1]=-m[3][1];
//    gl_TextureMatrix[0][0]=gl_TextureMatrix[0][0];
//    vec4 c=gl_MultiTexCoord0;
//    gl_MultiTexCoord0[0]=1.0 - gl_MultiTexCoord0[0];
//    c.x=0.5-c.x;
//    gl_TexCoord[0] = m * c;
//    gl_TexCoord[0].x=--gl_TexCoord[0].x;

    gl_TexCoord[0] = gl_MultiTexCoord0;
//    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

//    vec4 newTCoord = gl_TexCoord[0];
//    newTCoord.x = 1.0 - newTCoord.x;
//    gl_TexCoord[0] =newTCoord;

    switch(whattodo){
        case 0 : {
            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

//            vec4 vertex4 = gl_ModelViewMatrix * gl_Vertex;
//            hit_center_rot =sqrt( pow(vertex4.x,2.0) + pow(vertex4.y,2.0) + pow(vertex4.z,2.0) ) ;
//            hit_center =sqrt( pow(vertex4.x-move.x/maxExtent-add_xyz.x,2.0) + pow(vertex4.y-move.y/maxExtent-add_xyz.x,2.0)  ) ;
            break;
        }
        case 1 : {
            vec4 vertex = gl_Vertex;
//            vertex.z-=0.5;

            vertex = gl_ModelViewMatrix*gl_Vertex;

            vec4 vertex2 = vertex;
            float z = sqrt(vertex.x*vertex.x+vertex.y*vertex.y+vertex.z*vertex.z)*5.0;
            float cntr=1.0/(1.0+pow(z,1.5));
            float p1=(1.0+0.2*vertex.x*sin( time_phase* 0.931));
            float p2=(1.0+0.2*vertex.y*sin( time_phase* 0.719+p1/2.0));
            float p3=(1.0+0.2*vertex.z*sin( time_phase* 1.219+p2/2.0));
            float p4=(1.0+0.2*(vertex.z+vertex.y)*sin( time_phase* 0.819+p3/2.0));
            vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( p1+(p4+12)/(p4+12.2)*time_phase* wave_amplitude.x*0.151  )) * wave_amplitude.x*0.5;
            vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( p2+(p1+12)/(p1+13)*time_phase* wave_amplitude.x*0.172  )) * wave_amplitude.y*0.5;
            vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( p3+(p2+12)/(p2+11)*time_phase* wave_amplitude.x*0.193  )) * wave_amplitude.y*0.5;

//            vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( time_phase*1.2  )) * wave_amplitude.x*0.5;
//            vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( time_phase*1.2  )) * wave_amplitude.y*0.5;
//            vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( time_phase*1.2  )) * wave_amplitude.y*2.5;

            gl_Position = gl_ProjectionMatrix * vertex2;
//            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

            ro = normalize( (  vec4(0.0, .0, -1.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0
            n = normalize(gl_Normal);

//            vec2 off1=vec2( sin(time_phase/3.0) , cos(time_phase/3.0) )  ;

            vec2 off1=7.4*vec2( sin(time_phase/9.3) ,           cos(time_phase/9.3)        )  ;
            vec2 off2=7.4*vec2( sin(time_phase/7.6+off1.x) ,    cos(time_phase/7.6+off1.y) )  ;
            vec2 off3=7.4*vec2( sin(time_phase/9.3+off2.x/4.8) ,           cos(time_phase/9.3+off2.y/3.5)        )  ;
            vec2 off4=7.4*vec2( sin(time_phase/7.6+off3.x/2.5) ,    cos(time_phase/7.6+off3.y/1.9) )  ;

            lp1=normalize( (  vec4(off4.x,  0.0-(+1.0+off1.y/8.8), off4.y, 1.0) *      gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
            lp2=normalize( (  vec4(off2.x,  2.0+1.0+off1.x/8.8, off2.y, 1.0) *         gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
            lp3=normalize( (  vec4(-off4.x, 2.0+off2.x/8.8, -off4.y, 1.0) *            gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
            lp4=normalize( (  vec4(-off2.x,  -2.0-(1.0+off2.y/8.8), -off2.y, 1.0) *    gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
//            vec3 lp1=normalize( (  vec4(-4.0,  0.0, 0.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0
//            vec3 lp2=normalize( (  vec4( 0.0,  1.0, 0.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0



//            vec3 lp1=normalize( (  vec4(-4.0,  0.0, 0.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0
//            vec3 lp2=normalize( (  vec4( 0.0,  1.0, 0.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0

/*
            float spec1 = (2.0) * clamp(pow(max( dot(reflect(lp1, n), ro), 0.), 120.),0.0,1.0);
            float spec2 = (2.0) * clamp(pow(max( dot(reflect(lp2, n), ro), 0.), 120.),0.0,1.0);
            float spec3 = (2.0) * clamp(pow(max( dot(reflect(lp3, n), ro), 0.), 120.),0.0,1.0);
            float spec4 = (2.0) * clamp(pow(max( dot(reflect(lp4, n), ro), 0.), 120.),0.0,1.0);

            float diff1 = 1.5 * clamp(dot( n,lp1), 0.1, 1.);
            float diff2 = 1.5 * clamp(dot( n,lp2), 0.2, 1.);
            float diff3 = 1.5 * clamp(dot( n,lp3), 0.05,1.);
            float diff4 = 1.5 * clamp(dot( n,lp4), 0.0, 1.);

//            diff_ = (diff1+diff2)/2.0;
//            diff_ = diff1;
//            diff_ = diff2;
            diff_=diff1;
            if (diff2>diff_) diff_=diff2;
            if (diff3>diff_) diff_=diff3;
            if (diff4>diff_) diff_=diff4;


            if (spec1>spec2) kS_x_spec_ =  spec1*vec3(1.0, 1.0, 1.0) + vec3(0.10, 0.10, 0.10);
            else             kS_x_spec_ =  spec2*vec3(1.0, 1.0, 1.0) + vec3(0.10, 0.10, 0.10);

//            kS_x_spec_ =  spec1 + spec2 + vec3(0.10, 0.10, 0.10);
//            kS_x_spec_ = spec1 + vec3(0.10, 0.10, 0.10);
//            kS_x_spec_ = spec2 + vec3(0.10, 0.10, 0.10);
*/

            z_=1.0;
//            z_=1.0-gl_Position.z/3.0;
            break;
        }
        case 2 : {
//            if (!COLOR_ARRAY && WIRE_FRAME) out_color = vec4(gl_Color.xyz,1.0-gl_Position.z/.3);

            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

            if (!COLOR_ARRAY && WIRE_FRAME) {
//                if ( (gl_VertexID%3)==0 ) out_color=vec4(1.0,0.0,0.0,0.5);
//                else if ( (gl_VertexID%3)==1 ) out_color=vec4(0.0,1.0,0.0,0.5);
//                else if ( (gl_VertexID%3)==2 ) out_color=vec4(0.0,0.0,1.0,0.5);
//                if (  (gl_VertexID%6)==0 || (gl_VertexID%6)==1 || (gl_VertexID%6==2) ) {
                    out_color =- vec4(1.0,0.2,0.8,-2.5+gl_Position.z/0.3);
//                    out_color =- vec4(1.0,0.2,0.8,1.0-gl_Position.z/0.3);
//                    out_color = vec4(0.0,0.0,0.0,1.0);
//                } else {
//                    out_color = vec4(0.0,0.0,0.0,1.0-gl_Position.z/.3);
//                    out_color = vec4(0.0,0.0,0.0,0.0);
//                }
            }

//            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

            ro = normalize( (  vec4(0.0, .0, -1.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0
            n = normalize(gl_Normal);

            vec2 off1=6.4*vec2( sin(time_phase/9.3) ,           cos(time_phase/9.3)        )  ;
            vec2 off2=6.4*vec2( sin(time_phase/7.6+off1.x) ,    cos(time_phase/7.6+off1.y) )  ;
            vec2 off3=6.4*vec2( sin(time_phase/9.3+off2.x/4.8) ,           cos(time_phase/9.3+off2.y/3.5)        )  ;
            vec2 off4=6.4*vec2( sin(time_phase/7.6+off3.x/2.5) ,    cos(time_phase/7.6+off3.y/1.9) )  ;

            lp1=normalize( (  vec4(off4.x,  0.0-(+1.0+off1.y/8.8), off4.y, 1.0) *      gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
            lp2=normalize( (  vec4(off2.x,  1.0+1.0+off1.x/8.8, off2.y, 1.0) *         gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
            lp3=normalize( (  vec4(-off4.x, 1.0+off2.x/8.8, -off4.y, 1.0) *            gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0
            lp4=normalize( (  vec4(-off2.x,  -1.0-(1.0+off2.y/8.8), -off2.y, 1.0) *    gl_ModelViewMatrix  ).xyz) ; // zzzzz 2.0

/*
            float spec1 = (2.0) * clamp(pow(max( dot(reflect(lp1, n), ro), 0.), 120.),0.0,1.0);
            float spec2 = (2.0) * clamp(pow(max( dot(reflect(lp2, n), ro), 0.), 120.),0.0,1.0);
            float spec3 = (2.0) * clamp(pow(max( dot(reflect(lp3, n), ro), 0.), 120.),0.0,1.0);
            float spec4 = (2.0) * clamp(pow(max( dot(reflect(lp4, n), ro), 0.), 120.),0.0,1.0);

            float diff1 = 1.5 * clamp(dot( n,lp1), 0.1, 1.);
            float diff2 = 1.5 * clamp(dot( n,lp2), 0.2, 1.);
            float diff3 = 1.5 * clamp(dot( n,lp3), 0.05,1.);
            float diff4 = 1.5 * clamp(dot( n,lp4), 0.0, 1.);

//            diff_ = (diff1+diff2)/2.0;
//            diff_ = diff1;
//            diff_ = diff2;
            diff_=diff1;
            if (diff2>diff_) diff_=diff2;
            if (diff3>diff_) diff_=diff3;
            if (diff4>diff_) diff_=diff4;


            if (spec1>spec2) kS_x_spec_ =  spec1*vec3(1.0, 1.0, 1.0) + vec3(0.10, 0.10, 0.10);
            else             kS_x_spec_ =  spec2*vec3(1.0, 1.0, 1.0) + vec3(0.10, 0.10, 0.10);
*/

//            kS_x_spec_ =  spec1 + spec2 + vec3(0.10, 0.10, 0.10);
//            kS_x_spec_ = spec1 + vec3(0.10, 0.10, 0.10);
//            kS_x_spec_ = spec2 + vec3(0.10, 0.10, 0.10);

//            z_=1.3-gl_Position.z/3.5;
//            z_=2.0-gl_Position.z/6.0;
//            z_=1.0-gl_Position.z/6.0;
            z_=1.0-gl_Position.z/6.0;
//            z_=1.0;
            break;
        }
        case 3 : {
            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

//            mat4 m=gl_ModelViewMatrix;
//            gl_Position = gl_ProjectionMatrix * m * gl_Vertex;
//            gl_Position.x=1.0-gl_Position.x;

//            mat4 m=gl_ProjectionMatrix;
//            gl_Position = m * gl_ModelViewMatrix * gl_Vertex;

//            m[3][0]=-m[3][0];
//            m[0][0]=-m[0][0];
//            m[1][1]=-m[1][1];
//            m[2][2]=-m[2][2];
//            gl_Position = gl_ModelViewMatrix*gl_Vertex;
//            gl_Position = gl_ProjectionMatrix * gl_Position;

//            gl_Position.x = - gl_Position.x;
//            gl_Position.y = 1.0 - gl_Position.y;
//            gl_Position.z = 1.0 - gl_Position.z;
            if (!COLOR_ARRAY && WIRE_FRAME) {
//                if ( (gl_VertexID%3)==0 ) out_color=vec4(1.0,0.0,0.0,0.5);
//                else if ( (gl_VertexID%3)==1 ) out_color=vec4(0.0,1.0,0.0,0.5);
//                else if ( (gl_VertexID%3)==2 ) out_color=vec4(0.0,0.0,1.0,0.5);
//                if (  (gl_VertexID%6)==0 || (gl_VertexID%6)==1 || (gl_VertexID%6==2) ) {
                    out_color = vec4(0.0,0.0,0.0,1.0-gl_Position.z/.3);
//                } else {
//                    out_color = vec4(0.0,0.0,0.0,1.0-gl_Position.z/.3);
//                    out_color = vec4(0.0,0.0,0.0,0.0);
//                }
            }

//            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;


            ro = normalize( (  vec4(0.0, .0, -1.0, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0
            n = normalize(gl_Normal);

            vec2 off1=vec2( sin(time_phase/3.0) , cos(time_phase/3.0) )  ;

            lp1=normalize( (  vec4(1.4,   -1.8, -0.7, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0
            lp2=normalize( (  vec4(-1.4,  -1.5, 1.4, 1.0) * gl_ModelViewMatrix).xyz) ; // zzzzz 2.0

/*
            float spec1 = (1.0) * clamp(pow(max( dot(reflect(lp1, n), ro), 0.), 120.),0.1,1.0);
            float spec2 = (1.0) * clamp(pow(max( dot(reflect(lp2, n), ro), 0.), 120.),0.0,1.0);

            float diff1 = 1.5 * clamp(dot( n,lp1), 0.2, 1.);
            float diff2 = 1.5 * clamp(dot( n,lp2), 0.2, 1.);

//            diff_ = (diff1+diff2)/2.0;
//            diff_ = diff1;
//            diff_ = diff2;
            if (diff1>diff2) diff_=diff1;
            else             diff_=diff2;

            vec3 kS_x_spec_1 =  spec1*vec3(0.5, .5, .5) + vec3(0.10, 0.10, 0.10);
            vec3 kS_x_spec_2 =  spec2*vec3(.5, .5, .5) + vec3(0.10, 0.10, 0.10);
            kS_x_spec_ = (kS_x_spec_1+kS_x_spec_2)/2.0;

//            if (spec1>spec2) kS_x_spec_ =  spec1*vec3(0.5, .5, .5) + vec3(0.10, 0.10, 0.10);
//            else             kS_x_spec_ =  spec2*vec3(.5, .5, .5) + vec3(0.10, 0.10, 0.10);

//            kS_x_spec_ =  spec1 + spec2 + vec3(0.10, 0.10, 0.10);
//            kS_x_spec_ = spec1 + vec3(0.10, 0.10, 0.10);
//            kS_x_spec_ = spec2 + vec3(0.10, 0.10, 0.10);
*/
//            z_=2.0-gl_Position.z/2.5;
            z_=1.0-gl_Position.z/6.0;
//            z_=1.0;
            break;
        }
    }
}
