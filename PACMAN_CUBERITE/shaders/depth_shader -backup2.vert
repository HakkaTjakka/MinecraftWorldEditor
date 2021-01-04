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

//out vec3 my_normal;
out vec3 kS_x_spec_;
out float diff_;


//out mat4 my_modelviewmatrix;
out vec4 out_color;
//out float z_;

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
    switch(whattodo){
        case 0 : {
            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

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

            vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( wave_phase* wave_amplitude.x*0.051  )) * wave_amplitude.x*0.5;
            vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( wave_phase* wave_amplitude.x*0.072  )) * wave_amplitude.y*0.5;
            vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( wave_phase* wave_amplitude.x*0.093  )) * wave_amplitude.y*0.5;

//            vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.x*0.5;
//            vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*0.5;
//            vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*2.5;

            gl_Position = gl_ProjectionMatrix * vertex2;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
            if (!COLOR_ARRAY && WIRE_FRAME) out_color = vec4(0.0,0.0,0.0,1.0-gl_Position.z/0.3);
            vec4 kA = vec4(0.20, 0.20, 0.20, 1.0);
            vec4 kS1 = vec4(0.5, .5, .5, 1.0);
            vec4 kS2 = vec4(0.5, 0.5, 0.5, 1.0);
            vec3 light=(  gl_ModelViewMatrix * vec4(0.25, -0.5, 0.5, 1.0)).xyz ; // zzzzz 2.0
            vec3 light2=( gl_ModelViewMatrix * vec4(-0.25, -0.5, -0.5,1.0)).xyz; // zzzzz 2.0
//            vec3 light=vec3( sin(wave_phase/1.0)*0.5, cos(wave_phase/1.0)*0.5 , 0.5 + cos(wave_phase/5.3973)*0.5  ); // zzzzz 2.0
//            vec3 light2=vec3( sin(3.14 + wave_phase/1.0)*0.5, cos(3.14 + wave_phase/1.0)*0.5 , 0.25 + cos(wave_phase/7.3973)*0.75  ); // zzzzz 2.0
            vec3 ro = vec3(.0,-1.0, 0.0);
            vec3 n=gl_Normal.xyz;

            vec3 lp = normalize(light);
            diff_ = 1.3 * clamp(dot( n,lp), 0.0, 1.);
            float spec1 = (0.5) * clamp(pow(max( dot(reflect(-lp, n), ro), 0.), 120.),0.0,0.8);

            lp = normalize(light2);
            diff_ = (diff_ + 1.3 * clamp(dot( n,lp), 0.0, 1.))/2.0;
            float spec2 = (0.5) * clamp(pow(max( dot(reflect(-lp, n), ro), 0.), 120.),0.0,0.8);

            kS_x_spec_ = kS1.xyz * spec1 + kS2.xyz * spec2 + kA.xyz;
//            kS_x_spec_ = kS1.xyz * spec1 + kA.xyz;

            break;
        }
        case 2 : {
//            vec4 c0 = gl_ModelViewMatrix[0].xyzw;
//            vec4 c1 = gl_ModelViewMatrix[1].xyzw;
//            vec4 c2 = gl_ModelViewMatrix[2].xyzw;
//            vec4 c3 = gl_ModelViewMatrix[3].xyzw;

            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
//            if (!COLOR_ARRAY && WIRE_FRAME) out_color = vec4(0.0,0.0,0.0,1.0-gl_Position.z/.3);
            if (!COLOR_ARRAY && WIRE_FRAME) out_color = vec4(gl_Color.xyz,1.0-gl_Position.z/.3);
//or
//            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//or
//            gl_Position = gl_ModelViewMatrix * gl_Vertex;
//            gl_Position = gl_ProjectionMatrix  * gl_Position;

            break;
        }
        case 3 : {
            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

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

            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;


            vec4 kA = vec4(0.00, 0.00, 0.00, 1.0);
            vec4 kS1 = vec4(1.0, 1.0, 1.0, 1.0);
            vec4 kS2 = vec4(0.5, 0.5, 0.5, 1.0);
//          vec3 light=   vec3(-1.0,  0.0,  1.50) ; // zzzzz 2.0
//            vec3 light2=  vec3( 0.0,  2.0,  0.00) ; // zzzzz 2.0

//            vec3 light=vec3(0.25, -0.5, 0.5); // zzzzz 2.0
//            vec3 light2=vec3(-0.25, -0.5, -0.5); // zzzzz 2.0
//            vec2 off=vec2( sin(wave_phase/3.0) , cos(wave_phase/3.0) )  ;
            vec2 off=vec2( -2.0 , 0.0);
//            vec3 light=(  vec4(0.25, 1.5, 0.5, 1.0) * gl_ModelViewMatrix).xyz ; // zzzzz 2.0

////            vec3 light=(   vec4(-1.0,  0.0,  1.5, 1.0) * gl_ModelViewMatrix).xyz ; // zzzzz 2.0

            vec3 light=(   vec4(-1.0,  0.0,  1.0, 1.0) * gl_ModelViewMatrix).xyz ; // zzzzz 2.0
//            vec3 light=(  vec4( 0.0,  2.0,  0.0, 1.0) * gl_ModelViewMatrix).xyz ; // zzzzz 2.0
//            vec3 light2=vec3(-0.15, -0.5, 0.0); // zzzzz 2.0
//            vec3 light2=( gl_ModelViewMatrix * vec4(-0.25, -0.5, -0.5,1.0)).xyz; // zzzzz 2.0
  //          vec3 light=vec3( sin(wave_phase/1.0)*0.5, cos(wave_phase/1.0)*0.5 , 0.5 + cos(wave_phase/5.3973)*0.5  ); // zzzzz 2.0
//            vec3 light2=vec3( sin(3.14 + wave_phase/1.0)*0.5, cos(3.14 + wave_phase/1.0)*0.5 , 0.25 + cos(wave_phase/7.3973)*0.75  ); // zzzzz 2.0
//            vec3 ro = vec3(.0,-1.0, 0.0);
            vec3 ro = vec3(.0,-1.0, 0.0);
//            vec3 ro =1.2*(  vec4(.0,-1.0, 0.0, 1.0) * gl_ModelViewMatrix).xyz ; // zzzzz 2.0

            vec3 n= normalize(gl_Normal);
//            vec3 n=normalize(  (vec4(gl_Normal,1.0) *  gl_ModelViewMatrix).xyz) ;
//            vec3 n=normalize(  (vec4(normalize(gl_Normal),1.0) *  gl_ProjectionMatrix).xyz) ;
//            vec3 n=normalize(  (vec4(gl_Normal,1.0) *  inverse(gl_ModelViewMatrix)).xyz) ;
//            vec3 n=normalize(  (vec4(gl_Normal,1.0) *  gl_ProjectionMatrix).xyz) ;
//            vec3 n=normalize(  (vec4(normalize(gl_Normal),1.0) *  gl_ModelViewMatrix).xyz) ;
//            vec3 n=normalize(  (vec4(gl_Normal,1.0) *  inverse(gl_ModelViewMatrix)).xyz) ;
//gl_ProjectionMatrix
            vec3 lp = normalize(light);
            diff_ = 1.5 * clamp(dot( n,lp), 0.2, 1.);
            float spec1 = (1.0) * clamp(pow(max( dot(reflect(-lp, n), ro), 0.), 120.),0.0,1.0);

//            lp = normalize(light2);
//            diff_ = (diff_ + 1.2 * clamp(dot( n,lp), 0.1, 1.))/1.5;
//            float spec2 = (1.3) * clamp(pow(max( dot(reflect(-lp, n), ro), 0.), 120.),0.0,1.0);

//            kS_x_spec_ = kS1.xyz * spec1 + kS2.xyz * spec2 + kA.xyz;
            kS_x_spec_ = kS1.xyz * spec1 + kA.xyz;


            break;
        }
    }
}

