#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/common.hpp>
//#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "trackball.h"

void angles_to_quat(float curr_quat2[4], float prev_quat2[4],float &rotate_object_x, float &rotate_object_y, float &rotate_object_z) {
    glm::quat myquaternion = glm::quat(glm::vec3( (rotate_object_x)*M_PI/180.0, rotate_object_y*M_PI/180.0, (rotate_object_z+0.0)*M_PI/180.0 ));
    curr_quat2[0]=-myquaternion[0]; curr_quat2[1]=-myquaternion[1]; curr_quat2[2]=myquaternion[2]; curr_quat2[3]=myquaternion[3];
    prev_quat2[0]=0; prev_quat2[1]=0; prev_quat2[2]=0; prev_quat2[3]=0;
    rotate_object_x=0.0; rotate_object_y=0.0; rotate_object_z=0.0;
}

void quat_to_angles(float curr_quat2[4], float prev_quat2[4],float &rotate_object_x, float &rotate_object_y, float &rotate_object_z) {
    glm::quat q(curr_quat2[0], curr_quat2[1], curr_quat2[2], curr_quat2[3]);
    glm::vec3 euler = glm::eulerAngles(q);
    euler.x=euler.x*(180.0/M_PI); euler.y=euler.y*(180.0/M_PI); euler.z=euler.z*(180.0/M_PI)-180.0;
    if (euler.z<=-180.0) euler.z+=360.0; if (euler.z>180.0) euler.z-=360.0;
    rotate_object_x=euler.z; rotate_object_y=euler.y; rotate_object_z=euler.x;
    trackball(curr_quat2, 0, 0, 0, 0);
}
