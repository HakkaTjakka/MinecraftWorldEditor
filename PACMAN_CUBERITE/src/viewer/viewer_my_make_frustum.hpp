//int frustum_size_x=1;
//int frustum_size_y=1;
//rectangle

//        printf("PICTURE %d,%d FROM %d,%d TO %d,%d => FROM %30.15f %30.15f TO %30.15f  %30.15f\n",
//               frustum_count_x,frustum_count_y,
//               screen_x_start,screen_y_start,screen_x_end,screen_y_end,
//               screen_x_start_d,screen_y_start_d,screen_x_end_d,screen_y_end_d);

//        double frust_start_x=-width+part_x*frustum_count_x;
//        double frust_start_y=-height+part_y*frustum_count_y;
//        double frust_end_x=-width+part_x*(frustum_count_x+1.0);
//        double frust_end_y=-height+part_y*(frustum_count_y+1.0);

//        printf("DIFF=%30.15f  %30.15f  %30.15f  %30.15f\n",screen_x_start_d-frust_start_x,screen_y_start_d-frust_start_y,
//               screen_x_end_d-frust_end_x,screen_y_end_d-frust_end_y);
//        printf("FULL SIZE: FROM %30.15f %30.15f TO %30.15f %30.15f  \n",-width,width,-height,height);
//         glFrustum(-width, width, -height, height, front, back);
//    double part_x=tot_width/frustum_size_x;
//    double part_y=tot_height/frustum_size_y;
    // params: left, right, bottom, top, near, far


/*
void makeFrustum(double fovY, double aspectRatio, double front, double back, int frustum_toggle, float eye2[3])
{
    static const double DEG2RAD = 3.14159265 / 180;

    double tangent = tan(fovY/2 * DEG2RAD);   // tangent of half fovY
    double height = front * tangent;          // half height of near plane
    double width = height * aspectRatio;      // half width of near plane

    double tot_width = width*2.0;      // half width of near plane
    double tot_height = height*2.0;
    double start_x,start_y;
    double end_x,end_y;
    if (remember_911 || remember_911_2) {

        double screen_x_start=  rectangle.getPosition().x+(float)frustum_count_x*rectangle.getSize().x;
        double screen_x_end=    rectangle.getPosition().x+((float)frustum_count_x+1.0)*rectangle.getSize().x;
        double screen_y_start=  rectangle.getPosition().y+(float)frustum_count_y*rectangle.getSize().y;
        double screen_y_end=    rectangle.getPosition().y+((float)frustum_count_y+1.0)*rectangle.getSize().y;

//
//        if (frustum_count_x==frustum_size_x-1 && frustum_count_y==frustum_size_y-1) {
//            printf("\nTOT PICTURE %4d,%4d FROM %4d,%4d TO %4d,%4d => FROM %30.15f %30.15f TO %30.15f  %30.15f\n\n",
//                   frustum_size_x,frustum_size_y,
//                   int(rectangle.getPosition().x),
//                   int(rectangle.getPosition().y),
//                   int(rectangle.getPosition().x+(frustum_size_x)*rectangle.getSize().x),
//                   int(rectangle.getPosition().y+(frustum_size_y)*rectangle.getSize().y),
//
//                   -width+tot_width*rectangle.getPosition().x/1920.0,
//                   -height+tot_height*rectangle.getPosition().y/1080.0,
//                   -width+tot_width*(rectangle.getPosition().x+(frustum_size_x)*rectangle.getSize().x)/1920.0,
//                   -height+tot_height*(rectangle.getPosition().y+(frustum_size_y)*rectangle.getSize().y)/1080.0);
//        }
//
//
//        screen_width=screen_x_end-screen_x_start;
//        screen_height=screen_y_end-screen_y_start;

        start_x=-width+tot_width*screen_x_start/1920.0;
        start_y=height-tot_height*screen_y_start/1080.0;
//        start_y=-height+tot_height*screen_y_start/1080.0;

        end_x=-width+tot_width*screen_x_end/1920.0;
        end_y=height-tot_height*screen_y_end/1080.0;
//        end_y=-height+tot_height*screen_y_end/1080.0;

//        tot_width=tot_width*screen_width/1920.0;
//        tot_height=tot_height*screen_height/1080.0;


        double screen_x_start_d=start_x;
        double screen_y_start_d=end_y;
//        double screen_y_start_d=start_y;
        double screen_x_end_d=end_x;
        double screen_y_end_d=start_y;
//        double screen_y_end_d=end_y;


        if (remember_911_3)
            printf("PICTURE %4d,%4d FROM %14.10f,%14.10f TO %14.10f,%14.10f => FROM %14.10f %14.10f TO %14.10f  %14.15f\n",
                    frustum_count_x,frustum_count_y,
                    screen_x_start,screen_y_start,screen_x_end,screen_y_end,
                    screen_x_start_d,screen_y_start_d,screen_x_end_d,screen_y_end_d);
//        if (!remember_911_2) printf("\n");



//        double screen_x_start_d=start_x+screen_x_start*tot_width/screen_width;
//        double screen_y_start_d=start_y+screen_y_start*tot_height/screen_height;
//        double screen_x_end_d=start_x+screen_x_end*tot_width/screen_width;
//        double screen_y_end_d=start_y+screen_y_end*tot_height/screen_height;
//        double screen_x_start_d=-width+screen_x_start*tot_width/screen_width;
//        double screen_y_start_d=-height+screen_y_start*tot_height/screen_height;
//        double screen_x_end_d=-width+screen_x_end*tot_width/screen_width;
//        double screen_y_end_d=-height+screen_y_end*tot_height/screen_height;


        if (frustum_toggle==0)
            glFrustum(screen_x_start_d, screen_x_end_d, screen_y_start_d, screen_y_end_d, front, back);
        else if (frustum_toggle==1)
            glOrtho(screen_x_start_d*(100.0+eye2[2]*25.0),
                    screen_x_end_d*(100.0+eye2[2]*25.0),
                    screen_y_start_d*(100.0+eye2[2]*25.0),
                    screen_y_end_d*(100.0+eye2[2]*25.0),
                    front, back);
//            glOrtho(-screen_x_start_d*(100.0+eye2[2]*25),
//                     screen_x_end_d*(100.0+eye2[2]*25),
//                     -screen_y_start_d*(100.0+eye2[2]*25),
//                     screen_y_end_d*(100.0+eye2[2]*25),
//                     front, back);

//            glOrtho(-width*(100.0+eye2[2]*25), width*(100.0+eye2[2]*25), -height*(100.0+eye2[2]*25), height*(100.0+eye2[2]*25), front, back);


//        frustum_count_x--;
//        if (frustum_count_x<0) {
//            frustum_count_x=frustum_size_x-1;
//            frustum_count_y--;
//            printf("\n");
//            if (frustum_count_y<0) {
//                frustum_count_x=frustum_size_x-1;
//                frustum_count_y=frustum_size_y-1;
//                remember_911_set_off=true;
//            }
//        }
//

    } else {
        if (frustum_toggle==0)
            glFrustum(-width, width, -height, height, front, back);
        else if (frustum_toggle==1)
            glOrtho(-width*(100.0+eye2[2]*25.0), width*(100.0+eye2[2]*25.0), -height*(100.0+eye2[2]*25.0), height*(100.0+eye2[2]*25.0), front, back);
    }
}

*/
