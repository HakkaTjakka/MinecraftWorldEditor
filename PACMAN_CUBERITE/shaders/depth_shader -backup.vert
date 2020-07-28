uniform int whattodo;
uniform float wave_phase;
uniform vec2 wave_amplitude;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float ratio;
uniform float maxExtent;
uniform vec2 move;
uniform vec4 add_xyz;
uniform vec3 translation;
varying vec4 out_color;
//varying float hit_mouse;
varying float hit_center_rot;
varying float hit_center;

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
            vertex.z-=0.2;
            vertex = gl_ModelViewMatrix*gl_Vertex;
            vec4 vertex2 = vertex;
            float z = sqrt(vertex.x*vertex.x+vertex.y*vertex.y+vertex.z*vertex.z)*10.0;
            float cntr=1.0/(1.0+pow(z,1.5));
            vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.x*0.5;
            vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*0.5;
            vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*2.5;
            gl_Position = gl_ProjectionMatrix * vertex2;
            gl_Position = gl_Position * gl_ProjectionMatrix;
            break;
        }
        case 2 : {
            break;
        }
        case 3 : {
            break;
        }
    }
/*
    vec4 vertex = gl_Vertex;
    vertex.z-=0.2;
    vertex = gl_ModelViewMatrix*gl_Vertex;
    vec4 vertex2 = vertex;
    float z = sqrt(vertex.x*vertex.x+vertex.y*vertex.y+vertex.z*vertex.z)*10.0;
    float cntr=1.0/(1.0+pow(z,1.5));
    vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.x*0.5;
    vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*0.5;
    vertex2.z =  vertex.z + (vertex.z)*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*2.5;
    gl_Position =  gl_ProjectionMatrix * vertex2;
    gl_Position = gl_Position * gl_ProjectionMatrix;

*/

////    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
////    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;


//    vec4 vertex4 = gl_Vertex;

////    vec4 vertex4 = gl_ModelViewMatrix * gl_Vertex;
////    hit_center_rot =sqrt( pow(vertex4.x,2.0) + pow(vertex4.y,2.0) + pow(vertex4.z,2.0) ) ;

//    hit_center =sqrt( pow(vertex4.x,2.0) + pow(vertex4.y,2.0)+ pow(vertex4.z,2.0)  );
//    hit_center =sqrt( pow(move.x,2.0) + pow(move.y,2.0)  );
//    hit_center =sqrt( pow(vertex4.x-move.x/resolution.x,2.0) + pow(vertex4.y-move.y/resolution.y,2.0)  );
//    hit_center =sqrt( pow(vertex4.x,2.0) + pow(vertex4.y,2.0) + pow(vertex4.z,2.0) );
//    hit_center =sqrt( pow(gl_Vertex.x,2.0) + pow(gl_Vertex.y,2.0) + pow(gl_Vertex.z,2.0) );
//    vertex4 = gl_ModelViewMatrix * vec4(gl_Position.x-move.x,gl_Position.y-move.y, 0.0,1.0) * gl_ProjectionMatrix;
//    hit_center =sqrt( pow(vertex4.x,2.0) + pow(vertex4.y,2.0)*ratio  );
//    hit_mouse =( sqrt(pow(gl_Position.x / gl_Position.w-mouse.x,2.0)+pow((gl_Position.y / gl_Position.w - mouse.y)*ratio,2.0)) );
//    hit_mouse =( sqrt(pow(gl_Position.x / gl_Position.w-mouse.x,2.0)+pow((gl_Position.y / gl_Position.w - mouse.y)*ratio,2.0)) );

////    hit_center =sqrt( pow(vertex4.x-move.x/maxExtent-add_xyz.x,2.0) + pow(vertex4.y-move.y/maxExtent-add_xyz.x,2.0)  ) ;
////    out_color = gl_Color;

//    gl_FrontColor = gl_Color;

}
