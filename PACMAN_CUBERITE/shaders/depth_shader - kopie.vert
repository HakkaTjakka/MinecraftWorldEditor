uniform float wave_phase;
uniform vec2 wave_amplitude;


varying vec4 out_color;

void main()
{
    vec4 vertex = gl_ModelViewMatrix*gl_Vertex;
    vec4 vertex2 = vertex;
//    vec4 vertex = gl_ModelViewProjectionMatrix * gl_Vertex;


    float z = sqrt(vertex.x*vertex.x+vertex.y*vertex.y+vertex.z*vertex.z)*10.0;
//    float cntr=1.0;

//    float cntr=.005;
    float cntr=1.0/(1.0+pow(z,1.5));


//    if ( vertex2.x>-0.3 && vertex2.x<0.3 && vertex2.y>-0.3 && vertex2.y<0.3 && (vertex2.z)>-0.3 && (vertex2.z)<0.3 ) {
        vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.x*0.5;
        vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*0.5;
        vertex2.z =  vertex.z + (vertex.z)*cntr*(1.0+sin( wave_phase*1.2  )) * wave_amplitude.y*2.5;

//        vertex2.x =  vertex.x + cntr*(cos( wave_phase*1.2 + vertex.x*(12.0+sin(wave_phase*0.3)*3) )  + sin( wave_phase*1.2 + vertex.y*(12.0+sin(wave_phase*0.3)*3)) + cos( wave_phase*1.2 + (vertex.z-0.5)*(12.0+sin(wave_phase*0.3)*3))   ) * wave_amplitude.x*0.5;
//        vertex2.y =  vertex.y + cntr*(sin( wave_phase*1.2 + vertex.x*(12.0+sin(wave_phase*0.3)*3) )  + cos( wave_phase*1.2 + vertex.y*(12.0+sin(wave_phase*0.3)*3)) + cos( wave_phase*1.2 + (vertex.z-0.5)*(12.0+sin(wave_phase*0.3)*3))   ) * wave_amplitude.y*0.5;
//        vertex2.z =  vertex.z + cntr*(sin( wave_phase*1.2 + vertex.x*(12.0+sin(wave_phase*0.3)*3) )  + cos( wave_phase*1.2 + vertex.y*(12.0+sin(wave_phase*0.3)*3)) + cos( wave_phase*1.2 + (vertex.z-0.5)*(12.0+sin(wave_phase*0.3)*3))   ) * wave_amplitude.y*0.5;

//        vertex2.x =  vertex.x + cntr*(cos( wave_phase*1.2 + vertex.x*(12.0+sin(wave_phase*0.3 )*3) )  + sin( wave_phase*1.0 + vertex.y*(12.0+sin(wave_phase*0.38)*3)) + cos( wave_phase*1.25 + vertex.z*(12.0+sin(wave_phase*0.34)*3))   ) * wave_amplitude.x*0.5;
//        vertex2.y =  vertex.y + cntr*(sin( wave_phase*1.3 + vertex.x*(12.0+sin(wave_phase*0.35)*3) )  + cos( wave_phase*0.9 + vertex.y*(12.0+sin(wave_phase*0.36)*3)) + cos( wave_phase*1.45 + vertex.z*(12.0+sin(wave_phase*0.31)*3))   ) * wave_amplitude.y*0.5;
//        vertex2.z =  vertex.z + cntr*(sin( wave_phase*1.4 + vertex.x*(12.0+sin(wave_phase*0.4 )*3) )  + cos( wave_phase*0.8 + vertex.y*(12.0+sin(wave_phase*0.33)*3)) + cos( wave_phase*1.35 + vertex.z*(12.0+sin(wave_phase*0.43)*3))   ) * wave_amplitude.y*0.5;

//        vertex2.w =  vertex.w;
//    }


//    vertex.x =  vertex.x + (cos( wave_phase * 50.0)  + sin( wave_phase * 50.0) * 0.3 ) * wave_amplitude.x*2.0;
//    vertex.y =  vertex.y + (sin( wave_phase * 50.0)  + cos( wave_phase * 50.0) * 0.3 ) * wave_amplitude.y*2.0;


//    gl_Position = vertex2;
//    gl_Position = gl_ModelViewProjectionMatrix * vertex2;

    gl_Position =  gl_ProjectionMatrix * vertex2;
//    gl_Position = gl_ProjectionMatrix * vertex2;
//    vertex2 = gl_ModelViewProjectionMatrix * vertex2;
//    vertex = vertex2;

//    if ( vertex2.x>-.5 && vertex2.x<0.5) {
//    if ( vertex2.x>0.3 && vertex2.x<0.7 && vertex2.y>0.3 && vertex2.y<0.7 && (vertex2.z)>-0.3 && (vertex2.z)<0.3 ) {
//        vertex2.x =  vertex2.x + cntr*(cos( wave_phase*1.2 + vertex.x*(12.0))  + sin( wave_phase*1.0 + vertex.y*(12.0)) + cos( wave_phase*1.25 + vertex.z*(12.0))   ) * wave_amplitude.x*0.5;
//        vertex2.y =  vertex2.y + cntr*(sin( wave_phase*1.3 + vertex.x*(12.0))  + cos( wave_phase*0.9 + vertex.y*(12.0)) + cos( wave_phase*1.45 + vertex.z*(12.0))   ) * wave_amplitude.y*0.5;
//        vertex2.z =  vertex2.z + cntr*(sin( wave_phase*1.4 + vertex.x*(12.0))  + cos( wave_phase*0.8 + vertex.y*(12.0)) + cos( wave_phase*1.35 + vertex.z*(12.0))   ) * wave_amplitude.y*0.5;
//        gl_Position.w =  vertex2.w;
//    }

//    gl_Position = vertex2;

//    gl_Position = gl_ModelViewProjectionMatrix * vertex;

//    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    out_color = gl_Color;
}
