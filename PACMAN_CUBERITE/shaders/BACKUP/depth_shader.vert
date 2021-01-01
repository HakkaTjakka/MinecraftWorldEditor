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
varying vec4 out_color;
//varying float hit_mouse;
varying float hit_center_rot;
varying float hit_center;
varying float light;

void main()
{
    switch(whattodo){
        case 0 : {
            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
            gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

            vec4 vertex4 = gl_ModelViewMatrix * gl_Vertex;
            hit_center_rot =sqrt( pow(vertex4.x,2.0) + pow(vertex4.y,2.0) + pow(vertex4.z,2.0) ) ;
            hit_center =sqrt( pow(vertex4.x-move.x/maxExtent-add_xyz.x,2.0) + pow(vertex4.y-move.y/maxExtent-add_xyz.x,2.0)  ) ;
            out_color = gl_Color;
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
            break;
        }
        case 2 : {
            vec4 c0 = gl_ModelViewMatrix[0].xyzw;
            vec4 c1 = gl_ModelViewMatrix[1].xyzw;
            vec4 c2 = gl_ModelViewMatrix[2].xyzw;
            vec4 c3 = gl_ModelViewMatrix[3].xyzw;

            gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
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
            light=abs(length(normalize(gl_Normal.xyz)));
            break;
        }
    }
}
