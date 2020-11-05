#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/common.hpp>

//#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <SFML/Graphics.hpp>
#include <float.h>
#include <string>
#include <cmath>

typedef struct
{
    int8_t* buffer;
    size_t length;
} BufferObject;

void ROTJE(glm::vec3 &torot, float bmin[3], float bmax[3], double lat, double lon);

void RECALC_BMIN_BMAX(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon) {

//    float curr_quat2[4];
//    trackball(curr_quat2, 0, 0, 0, 0);
//    glm::mat4 rot_matrix2(1.0f);
//    build_rotmatrix_glm(rot_matrix2, curr_quat2);

    BufferObject one_buffer;

    glm::vec3 NORMALz;
    glm::mat4 test(1.0f);

    float tx;
    float ty;
    float tz;


//    printf("(original)\n");
//    printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
//    printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
//    printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

    tx=-0.5 * (bmax[0] + bmin[0]);
    ty=-0.5 * (bmax[1] + bmin[1]);
    tz=-0.5 * (bmax[2] + bmin[2]);

//    printf("lat=%lf  lon=%lf\n",lat,lon);
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();
    NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
    NORMALz = glm::normalize(NORMALz);

//    lat = -(90.0 + lat);
//    lon = -lon;
//    lat = -lat;
//    test=glm::mat4(  cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    , sin(lon*M_PI/180.0)   ,  sin(lat*M_PI/180.0)*cos(lon*M_PI/180.0)  , 0.0,
//                    -cos(lat*M_PI/180.0)*sin(lon*M_PI/180.0)    , cos(lon*M_PI/180.0)   , -sin(lat*M_PI/180.0)*sin(lon*M_PI/180.0)  , 0.0,
//                    -sin(lat*M_PI/180.0)                        , 0.0                   ,  cos(lat*M_PI/180.0)                      , 0.0,
//                   0.0                                          , 0.0                   , 0.0                                       , 1.0);

//    lat = -(90.0 + lat);
//    lon = -lon;
    test=glm::mat4(  cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    , cos(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , sin(lat*M_PI/180.0)   , 0.0,
                    -sin(lon*M_PI/180.0)                        , cos(lon*M_PI/180.0)                       , 0.0                   , 0.0,
                    -sin(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    ,-sin(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , cos(lat*M_PI/180.0)   , 0.0,
                   0.0                                          ,0.0                                        ,0.0                    , 1.0);
//    test=glm::inverse(test);

//x = cos(ϑ) cos(φ) x' + sin(φ) y' + sin(ϑ) cos(φ) z'
//y = -cos(ϑ) sin(φ) x' + cos(φ) y' - sin(ϑ) sin(φ) z'
//z = -sin(ϑ) x' + cos(ϑ) z'


//    test = glm::rotate(test,(float)(-lat*M_PI/180.0),{1.0,0.0,0.0});
//    test = glm::rotate(test,(float)(lon*M_PI/180.0),{0.0,1.0,0.0});
//    test = glm::eulerAngleYX(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) );

//    test = glm::eulerAngleYXZ(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) , (float)(0.0));
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;

//    test = rot_matrix2 * test;
//    test=glm::inverse(test);

    for (auto u : buffers) {
        one_buffer=u;

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        float v[3][3];
//        float n[3][3];
//        float c[3][3];
//        float tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
//        float* TexCoordPointer=real_buffer + 9;


        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
//                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                }
//                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f) * test;
//normal...
//kiekeboe
                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f) * test;

//                glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;
//                hop = hop - glm::vec4(tx,ty,tz,0.0f);
//                VertexPointer[offset]=hop.x;
//                VertexPointer[offset+1]=hop.y;
//                VertexPointer[offset+2]=hop.z;
                bmin[0]=std::min(hop.x, bmin[0]);   bmax[0]=std::max(hop.x, bmax[0]);
                bmin[1]=std::min(hop.y, bmin[1]);   bmax[1]=std::max(hop.y, bmax[1]);
                bmin[2]=std::min(hop.z, bmin[2]);   bmax[2]=std::max(hop.z, bmax[2]);
//                    printf("Buffer: %3d/%3d  Face: %5d/%5d  ",i+1, tag_buffers->tag_list.size, faces+1,num_faces);
//                    printf("Offset: %7d/%7d  Vertice: %d %-+9.3f %-+9.3f %-+9.3f  ==>  %-+9.3f %-+9.3f %-+9.3f  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                            offset*sizeof(float),one_buffer.length,l,v[l][0],v[l][1],v[l][2],hop.x,hop.y,hop.z,
//                            bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
            }
        }
//            printf("Buffer: %3d/%3d  Faces: %5d  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                   i+1, tag_buffers->tag_list.size, num_faces, bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
    }

//    printf("(calculated)\n");
//    printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
//    printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
//    printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

}

void RECALC_BMIN_BMAX2(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon) {

//    float curr_quat2[4];
//    trackball(curr_quat2, 0, 0, 0, 0);
//    glm::mat4 rot_matrix2(1.0f);
//    build_rotmatrix_glm(rot_matrix2, curr_quat2);

    BufferObject one_buffer;

    glm::vec3 NORMALz;
    glm::mat4 test(1.0f);

    float tx;
    float ty;
    float tz;


//    printf("(original)\n");
//    printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
//    printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
//    printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

    tx=-0.5 * (bmax[0] + bmin[0]);
    ty=-0.5 * (bmax[1] + bmin[1]);
    tz=-0.5 * (bmax[2] + bmin[2]);

//    printf("lat=%lf  lon=%lf\n",lat,lon);
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();
    NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
    NORMALz = glm::normalize(NORMALz);


    test=glm::mat4(  cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    , cos(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , sin(lat*M_PI/180.0)   , 0.0,
                    -sin(lon*M_PI/180.0)                        , cos(lon*M_PI/180.0)                       , 0.0                   , 0.0,
                    -sin(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    ,-sin(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , cos(lat*M_PI/180.0)   , 0.0,
                    0.0                                         ,0.0                                        ,0.0                    , 1.0);

//    glm::vec4 trot=glm::vec4(-tx,-ty,-tz,1.0) * test;
//    test = glm::eulerAngleYXZ(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) , (float)(0.0));
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;

//    test = rot_matrix2 * test;
//    test=glm::inverse(test);

    for (auto u : buffers) {
        one_buffer=u;

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        float v[3][3];
//        float n[3][3];
//        float c[3][3];
//        float tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
//        float* TexCoordPointer=real_buffer + 9;


        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
//                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                }
//normal...
                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f) * test;
                VertexPointer[offset]=hop.x;
                VertexPointer[offset+1]=hop.y;
                VertexPointer[offset+2]=hop.z;

//                glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;

//                hop = hop + trot;
//                hop = hop - glm::vec4(tx,ty,tz,0.0f);

                bmin[0]=std::min(hop.x, bmin[0]);   bmax[0]=std::max(hop.x, bmax[0]);
                bmin[1]=std::min(hop.y, bmin[1]);   bmax[1]=std::max(hop.y, bmax[1]);
                bmin[2]=std::min(hop.z, bmin[2]);   bmax[2]=std::max(hop.z, bmax[2]);
//                    printf("Buffer: %3d/%3d  Face: %5d/%5d  ",i+1, tag_buffers->tag_list.size, faces+1,num_faces);
//                    printf("Offset: %7d/%7d  Vertice: %d %-+9.3f %-+9.3f %-+9.3f  ==>  %-+9.3f %-+9.3f %-+9.3f  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                            offset*sizeof(float),one_buffer.length,l,v[l][0],v[l][1],v[l][2],hop.x,hop.y,hop.z,
//                            bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
            }
        }
//            printf("Buffer: %3d/%3d  Faces: %5d  bmin=%-+9.3f %-+9.3f %-+9.3f  bmax=%-+9.3f %-+9.3f %-+9.3f\n",
//                   i+1, tag_buffers->tag_list.size, num_faces, bmin[0],bmin[1],bmin[2],bmax[0],bmax[1],bmax[2]);
    }

//    printf("(calculated)\n");
//    printf("bmin = % 24.13f, % 24.13f, % 24.13f\n", bmin[0],           bmin[1],            bmin[2]);
//    printf("bmax = % 24.13f, % 24.13f, % 24.13f\n", bmax[0],           bmax[1],            bmax[2]);
//    printf("diff = % 24.13f, % 24.13f, % 24.13f\n", bmax[0]-bmin[0],   bmax[1]-bmin[1],    bmax[2]-bmin[2]);

}


void ROTJE(glm::vec3 &torot, float bmin[3], float bmax[3], double lat, double lon) {
    glm::vec3 NORMALz;
    glm::mat4 test(1.0f);

    float tx;
    float ty;
    float tz;

    tx=-0.5 * (bmax[0] + bmin[0]);
    ty=-0.5 * (bmax[1] + bmin[1]);
    tz=-0.5 * (bmax[2] + bmin[2]);

    NORMALz = glm::vec3((float)(cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)), (float)(cos(lat*M_PI/180)*sin(lon*M_PI/180)), (float)(sin(lat*M_PI/180)));
    NORMALz = glm::normalize(NORMALz);

//    lat = -(90.0 + lat);
//    lon = -lon;
//    test=glm::mat4(  cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    , sin(lon*M_PI/180.0)   ,  sin(lat*M_PI/180.0)*cos(lon*M_PI/180.0)  , 0.0,
//                    -cos(lat*M_PI/180.0)*sin(lon*M_PI/180.0)    , cos(lon*M_PI/180.0)   , -sin(lat*M_PI/180.0)*sin(lon*M_PI/180.0)  , 0.0,
//                    -sin(lat*M_PI/180.0)                        , 0.0                   ,  cos(lat*M_PI/180.0)                      , 0.0,
//                   0.0                                          , 0.0                   , 0.0                                       , 1.0);
    test=glm::mat4(  cos(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    , cos(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , sin(lat*M_PI/180.0)   , 0.0,
                    -sin(lon*M_PI/180.0)                        , cos(lon*M_PI/180.0)                       , 0.0                   , 0.0,
                    -sin(lat*M_PI/180.0)*cos(lon*M_PI/180.0)    ,-sin(lat*M_PI/180.0)*sin(lon*M_PI/180.0)   , cos(lat*M_PI/180.0)   , 0.0,
                   0.0                                          ,0.0                                        ,0.0                    , 1.0);
    test=glm::inverse(test);
//    test = glm::eulerAngleYXZ(  (float)((lat)*M_PI/180.0) ,(float)((lon)*M_PI/180.0) , (float)(0.0));
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), glm::vec3(0.0,1.0,0.0)) ;
//    test = glm::rotate(test, float(-90.0*M_PI/180.0), {NORMALz.x,NORMALz.y,NORMALz.z} ) ;
//    test = glm::inverse(test);

    glm::vec4 hop = glm::vec4(torot.x, torot.y, torot.z, 1.0f) * test;
//    glm::vec4 hop = glm::vec4(torot.x+tx, torot.y+ty, torot.z+tz, 1.0f) * test;
//    hop = hop - glm::vec4(tx,ty,tz,0.0f);
    torot=glm::vec3(hop.x,hop.y,hop.z);
}

extern glm::mat4 exporter;
extern glm::mat4 exporter2;

extern float g_rotate_object_x;
extern float g_rotate_object_y;
extern float g_rotate_object_z;
extern float g_move_object_x;
extern float g_move_object_y;
extern float g_move_object_z;

void RECALC_BMIN_BMAX4(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon) {
    BufferObject one_buffer;

    glm::vec3 NORMALz;
    glm::mat4 test=glm::mat4(1.0f);
//    glm::mat4 test=exporter2;

    float tx;
    float ty;
    float tz;

    tx=-0.5 * (bmax[0] + bmin[0]);
    ty=-0.5 * (bmax[1] + bmin[1]);
    tz=-0.5 * (bmax[2] + bmin[2]);

//    printf("lat=%lf  lon=%lf\n",lat,lon);
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();

//                test = glm::rotate(test, float(g_rotate_object_x*M_PI/180.0), {1.0,0.0,0.0} ) ;
//                test = glm::rotate(test, float(g_rotate_object_y*M_PI/180.0), {0.0,1.0,0.0} ) ;
//                test = glm::rotate(test, float(g_rotate_object_z*M_PI/180.0), {0.0,0.0,1.0} ) ;

//    test = glm::rotate(test, float(-180.0*M_PI/180.0), {1.0,0.0,0.0} ) ;

//    test=glm::inverse(test);


    test = glm::rotate(test, float(g_rotate_object_x*M_PI/180.0), {1.0,0.0,0.0} ) ;
    test = glm::rotate(test, float(g_rotate_object_y*M_PI/180.0), {0.0,1.0,0.0} ) ;
    test = glm::rotate(test, float(-g_rotate_object_z*M_PI/180.0), {0.0,0.0,1.0} ) ;

//    test = glm::rotate(test, float(90.0*M_PI/180.0), {0.0,0.0,1.0} ) ;
//    test = glm::rotate(test, float(180.0*M_PI/180.0), {1.0,0.0,0.0} ) ;

    for (auto u : buffers) {
        one_buffer=u;

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        float v[3][3];
//        float n[3][3];
//        float c[3][3];
//        float tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
//        float* TexCoordPointer=real_buffer + 9;

        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
//                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                }

//                glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;
//                hop = hop - glm::vec4(tx,ty,tz,0.0f);


                glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;
//                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f) * test;
//                hop = glm::vec4(hop.y, hop.x, hop.z, 1.0f);

                VertexPointer[offset+1]=hop.y;
                VertexPointer[offset+2]=hop.z;
                VertexPointer[offset]=hop.x;

                bmin[0]=std::min(hop.x, bmin[0]);   bmax[0]=std::max(hop.x, bmax[0]);
                bmin[1]=std::min(hop.y, bmin[1]);   bmax[1]=std::max(hop.y, bmax[1]);
                bmin[2]=std::min(hop.z, bmin[2]);   bmax[2]=std::max(hop.z, bmax[2]);
            }
        }
    }
}

extern int follow_ghost;
extern bool hold_voxels;
extern bool rot_on;

void RECALC_BMIN_BMAX3(std::vector<BufferObject> buffers, float bmin[3], float bmax[3], double lat, double lon) {
    BufferObject one_buffer;

    glm::vec3 NORMALz;
    glm::mat4 test=exporter2;

    float tx;
    float ty;
    float tz;

    tx=-0.5 * (bmax[0] + bmin[0]);
    ty=-0.5 * (bmax[1] + bmin[1]);
    tz=-0.5 * (bmax[2] + bmin[2]);

//    printf("lat=%lf  lon=%lf\n",lat,lon);
    bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
    bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();


//    test = glm::rotate(test, float(-180.0*M_PI/180.0), {1.0,0.0,0.0} ) ;

    test=glm::inverse(test);


    test = glm::rotate(test, float(90.0*M_PI/180.0), {0.0,0.0,1.0} ) ;
    test = glm::rotate(test, float(180.0*M_PI/180.0), {1.0,0.0,0.0} ) ;

/*
    if (hold_voxels && rot_on) {
        printf("rotating %f %f %f\n",g_rotate_object_x,g_rotate_object_y,g_rotate_object_z);
        test = glm::rotate(test, float(g_rotate_object_x*M_PI/180.0), {1.0,0.0,0.0} ) ;
        test = glm::rotate(test, float(g_rotate_object_y*M_PI/180.0), {0.0,1.0,0.0} ) ;
        test = glm::rotate(test, float(g_rotate_object_z*M_PI/180.0), {0.0,0.0,1.0} ) ;
    }
*/
    for (auto u : buffers) {
        one_buffer=u;

        int num_faces=(one_buffer.length-sizeof(int)) / (3 + 3 + 3 + 2) / 3 / sizeof(float);     // 3:vtx, 3:normal, 3:col, 2:texcoord
        float v[3][3];
//        float n[3][3];
//        float c[3][3];
//        float tc[3][2];
        int stride = (3 + 3 + 2 + 3);
        float* real_buffer = (float*)(one_buffer.buffer + sizeof(int));
        float* VertexPointer=real_buffer;
//        float* NormalPointer=real_buffer + 3;
//        float* ColorPointer=real_buffer + 6;
//        float* TexCoordPointer=real_buffer + 9;

        for (int faces=0; faces<num_faces; faces++) {
            for (int l=0; l<3; l++) {
                int offset=(stride*(l+faces*3));
                for (int k=0; k<3; k++) {
                    if (offset*sizeof(float) >= one_buffer.length-sizeof(int)) {
                        printf("Error offset\n");
                        return;
                    }
                    v[l][k]=VertexPointer[offset+k];
//                    n[l][k]=NormalPointer[offset+k];
//                    c[l][k]=ColorPointer[offset+k];
//                    if (k<2) tc[l][k]=TexCoordPointer[offset+k];
                }



//                glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;
//                hop = hop - glm::vec4(tx,ty,tz,0.0f);


                glm::vec4 hop = glm::vec4(v[l][0]+tx, v[l][1]+ty, v[l][2]+tz, 1.0f) * test;
//                glm::vec4 hop = glm::vec4(v[l][0], v[l][1], v[l][2], 1.0f) * test;
//                hop = glm::vec4(hop.y, hop.x, hop.z, 1.0f);


extern int whattodo;
extern float fpstime;

                if (whattodo==1) {
                    glm::vec4 vertex = hop;
                    float z = sqrt(vertex.x*vertex.x+vertex.y*vertex.y+vertex.z*vertex.z)*5.0;
                    float cntr=1.0/(1.0+pow(z,1.5));
                    glm::vec4 vertex2;
                    vertex2.x =  vertex.x + vertex.x*cntr*(1.0+sin( fpstime* 5.0*0.2  )) * 2.5;
                    vertex2.y =  vertex.y + vertex.y*cntr*(1.0+sin( fpstime* 5.0*0.3  )) * 2.5;
                    vertex2.z =  vertex.z + vertex.z*cntr*(1.0+sin( fpstime* 5.0*0.4  )) * 2.5;
                    vertex2.w = 1.0;
                    hop = vertex2;
                }

                VertexPointer[offset]=hop.x;
                VertexPointer[offset+1]=hop.y;
                VertexPointer[offset+2]=hop.z;

                bmin[0]=std::min(hop.x, bmin[0]);   bmax[0]=std::max(hop.x, bmax[0]);
                bmin[1]=std::min(hop.y, bmin[1]);   bmax[1]=std::max(hop.y, bmax[1]);
                bmin[2]=std::min(hop.z, bmin[2]);   bmax[2]=std::max(hop.z, bmax[2]);
            }
        }
    }
}
