#version 330 compatibility


//layout(location = 0) in vec3 gl_Vertex;
//layout(location = 1) in vec3 gl_Color;
//layout(location = 2) in vec3 gl_Normal;

//out vec3 p_position;
//out vec3 p_color;
//out vec3 p_normal;

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

out vec3 my_normal;
out mat4 my_modelviewmatrix;
//out vec4 out_color;

//varying vec3 my_light;
//varying vec4 out_color;
//varying vec4 out_color;

//varying float hit_mouse;
//varying float hit_center_rot;
//varying float hit_center;

void main()
{
//    out_color = gl_Color;
//     p_position;
//     p_color;
//     p_normal;
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

            vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( wave_phase* wave_amplitude.x*0.2  )) * wave_amplitude.x*0.5;
            vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( wave_phase* wave_amplitude.x*0.3  )) * wave_amplitude.y*0.5;
            vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( wave_phase* wave_amplitude.x*0.4  )) * wave_amplitude.y*0.5;

//            vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.x*0.5;
//            vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*0.5;
//            vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*2.5;

            gl_Position = gl_ProjectionMatrix * vertex2;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
            break;
        }
        case 2 : {
//            vec4 c0 = gl_ModelViewMatrix[0].xyzw;
//            vec4 c1 = gl_ModelViewMatrix[1].xyzw;
//            vec4 c2 = gl_ModelViewMatrix[2].xyzw;
//            vec4 c3 = gl_ModelViewMatrix[3].xyzw;

            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
//or
//            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//or
//            gl_Position = gl_ModelViewMatrix * gl_Vertex;
//            gl_Position = gl_ProjectionMatrix  * gl_Position;

            break;
        }
        case 3 : {
            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
//            my_light=vec4(length(normalize(gl_Color.xyz)));
//            my_light=vec4(length(normalize(gl_Normal.xyz)));
            my_normal=gl_Normal.xyz;
//            my_modelviewmatrix=inverse(gl_ModelViewMatrix);
            my_modelviewmatrix=inverse(gl_ProjectionMatrix);
//            my_modelviewmatrix=gl_ModelViewMatrix;

//            my_modelviewmatrix=inverse(gl_ProjectionMatrix * gl_ModelViewMatrix);
//            my_light=vec4(1.0);
//            out_color = gl_Color;

//            my_light=vec4((sin(wave_phase)+1)/2.0);
            break;
        }
    }
}
