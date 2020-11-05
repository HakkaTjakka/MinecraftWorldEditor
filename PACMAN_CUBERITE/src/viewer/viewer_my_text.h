#define PRINTIT draw2_all(window,(char*)to_print,0,i,sf::Color(0,0,255,255),sf::Color::White,24); i+=26;
#define PRINTIT_RED draw2_all(window,(char*)to_print,0,i,sf::Color(255,0,0,255),sf::Color::White,24); i+=26;
#define PRINTIT_BIG draw2_all(window,(char*)to_print,0,i,sf::Color(0,0,255,255),sf::Color::White,38); i+=40;
#define PRINTIT_RED_BIG draw2_all(window,(char*)to_print,0,i,sf::Color(255,0,0,255),sf::Color::White,38);i+=40;



                    static float enschede_x=3875099.0;
                    static float enschede_y=468154.0;
                    static float enschede_z=5035344.0;

                    char to_print[1000];
                    if (!remember_911) {
                        if (show_text || frustum) {
                            window.pushGLStates();
                            int i=0;
                            float playbackspeed=0.005;

                            if (frustum) {
        //                        window.draw(rectangle);
                                sf::Vector2f p_o=rectangle.getPosition();
                                sf::Vector2f p_s=rectangle.getSize();
                                rectangle.setSize(sf::Vector2f(rectangle.getSize().x-2,rectangle.getSize().y-2));
                                static bool flop=true;
                                flop=!flop;
                                for (int y=0; y<frustum_size_y; y++) {
                                    for (int x=0; x<frustum_size_x; x++) {
                                        if (videomode[win_num]==1) {
                                            rectangle.setOutlineColor(sf::Color(255,0,0,255));
                                        } else {
                                            rectangle.setOutlineColor(sf::Color(128,255,128,255));
                                        }
                                        rectangle.setPosition(
                                                              p_o.x+(float)x*p_s.x+1,
                                                              p_o.y+(float)y*p_s.y+1
                                                              );
                                        window.draw(rectangle);
                                    }
                                }
                                int y=frustum_count_y;
                                int x=frustum_count_x;
                                if (y<frustum_size_y && x<frustum_size_x) {
                                    if (flop)
                                        rectangle.setOutlineColor(sf::Color(128,128,0,255));
                                    else
                                        rectangle.setOutlineColor(sf::Color(0,0,128,255));
                                    rectangle.setPosition(
                                                          p_o.x+(float)x*p_s.x+1,
                                                          p_o.y+(float)y*p_s.y+1
                                                          );
                                    window.draw(rectangle);
                                }

                                rectangle.setPosition(p_o);
                                rectangle.setSize(p_s);

                                if (show_text) {
                                    sprintf(to_print,"FRUSTUMS=",remember_911_3 ? "ON" : "OFF");                    PRINTIT
                                    sprintf(to_print,"FRUSTUM COUNT X: %d/%d",frustum_count_x,frustum_size_x);              PRINTIT
                                    sprintf(to_print,"FRUSTUM COUNT Y: %d/%d",frustum_count_y,frustum_size_y);              PRINTIT
                                    sprintf(to_print,"FRUSTUM POS X:  %f",rectangle.getPosition().x);              PRINTIT
                                    sprintf(to_print,"FRUSTUM POS Y:  %f",rectangle.getPosition().y);              PRINTIT
                                    sprintf(to_print,"FRUSTUM SIZE X: %f",rectangle.getSize().x);              PRINTIT
                                    sprintf(to_print,"FRUSTUM SIZE Y: %f",rectangle.getSize().y);              PRINTIT
                                    sprintf(to_print,"FRUSTUM TOT.SIZE X: %f",rectangle.getSize().x*frustum_size_x);              PRINTIT
                                    sprintf(to_print,"FRUSTUM TOT.SIZE Y: %f",rectangle.getSize().y*frustum_size_y);              PRINTIT
                                    sprintf(to_print,"WINDOW SIZE X: %d",window.getSize().x);              PRINTIT
                                    sprintf(to_print,"WINDOW SIZE Y: %d",window.getSize().y);              PRINTIT
                                    sprintf(to_print,"TOT. SIZE X: %d",int(window.getSize().x*frustum_size_x));              PRINTIT
                                    sprintf(to_print,"TOT. SIZE Y: %d",int(window.getSize().y*frustum_size_y));              PRINTIT
                                }
                            }

                            if (show_text) {
                                if (do_model) {
                                        sprintf(to_print,"SECONDS:   %.2f   FPS: %.2f   CPU: %3.2f%%   MISSES: %d",render_time,render_fps, cpu_usage*100.0, misses);          PRINTIT
                                        sprintf(to_print,"ANGELS:    % 10.6f % 10.6f % 10.6f",rotate_object_x,rotate_object_y,rotate_object_z);                    PRINTIT_BIG
                                        glm::quat myquaternion = glm::quat(glm::vec3( (rotate_object_x)*M_PI/180.0, rotate_object_y*M_PI/180.0, (rotate_object_z+0.0)*M_PI/180.0 ));
                                        myquaternion[0]=-myquaternion[0]; myquaternion[1]=-myquaternion[1];
                                        sprintf(to_print,"TO QUAT:   % 10.6f % 10.6f % 10.6f% 10.6f",myquaternion[0],myquaternion[1],myquaternion[2],myquaternion[3]);                    PRINTIT_BIG

                                        i+=20;
                                        sprintf(to_print,"QUAT:      % 10.6f % 10.6f % 10.6f% 10.6f",curr_quat2[0],curr_quat2[1],curr_quat2[2],curr_quat2[3]);                    PRINTIT_BIG
                                        i+=20;
                                        sprintf(to_print,"TRANSLATE: % 10.6f % 10.6f % 10.6f%",move_object_x, move_object_y, move_object_z);                    PRINTIT_BIG

                                        glm::quat q=glm::quat(curr_quat2[0], curr_quat2[1], curr_quat2[2], curr_quat2[3]);
                                        glm::vec3 euler = glm::eulerAngles(q);
                                        euler.x=euler.x*(180.0/M_PI); euler.y=euler.y*(180.0/M_PI); euler.z=euler.z*(180.0/M_PI);
                                        euler.z-=180.0;
                                        if (euler.z<=-180.0) euler.z+=360;
                                        sprintf(to_print,"TO ANGLES: % 10.6f % 10.6f % 10.6f",euler.z,euler.y,euler.x);                    PRINTIT_BIG

                                        i+=20;
                                        sprintf(to_print,"Max schematic size: %10d",(int)schematic_size);           PRINTIT_BIG
                                        i+=20;
                                        sprintf(to_print,"REGIONS:   F1 voxelize, CTRL-F1 finish them all to region files");           PRINTIT
                                        sprintf(to_print,"SCHEMATIC: SHIFT-F1 Create schematic from object (destroys F1 made...)");           PRINTIT
                                        sprintf(to_print,"      CTRL+SHIFT-F1 Create schematic from object plot with F1");           PRINTIT
                                        sprintf(to_print,"CTRL+SYSTEM+SHIFT + left/right prev/next model (see ../models/list.txt)");           PRINTIT
                                        sprintf(to_print,"CTRL+SHIFT + left|right ADD prev/next model");           PRINTIT
                                        sprintf(to_print,"ANGLES: ALT + left|right|up|down|pgup|pgdn rotate x/y/z");           PRINTIT
                                        sprintf(to_print,"QUATS: CTRL + left|right|up|down|pgup|pgdn rotate x/y/z");           PRINTIT
                                        sprintf(to_print,"F5 Text on/of  F6|F7|F8 reset view");           PRINTIT
                                        sprintf(to_print,"ALT-F6|ALT-F7|ALT-F8 reset angle x|y|z");           PRINTIT
                                        sprintf(to_print,"F11 Full screen / window");           PRINTIT
                                        sprintf(to_print,"SHIFT-F5 Round Angles(1)  SHIFT-F6(5)  SHIFT-F7(10)  SHIFT-F8(90)");           PRINTIT
                                        sprintf(to_print,"ALT-F1 Plot regions on canvas window  DELETE Clear voxels (from F1)");           PRINTIT
                                        sprintf(to_print,"CANVAS WINDOW: ALT+DEL(3x) Clear screen  SHIFT-D foreground/background screen");           PRINTIT
                                        sprintf(to_print,"F2: WRITE REGION.VOX VOXEL FILES TO REGION.MCA FILES  CTRL-F2: FLUSH VOXELS TO REGION VOXEL FILES");           PRINTIT
                                        sprintf(to_print,"SHIFT-F2: PLOT REGION.VOX VOXEL FILES");           PRINTIT
                                        sprintf(to_print,"F10: Rotate on  ALT-F10: Plot when rotate on");           PRINTIT
                                        if (voxel_bottom!=0.0) {
                                            sprintf(to_print,"+/- Voxel bottom=%d",(int)voxel_bottom);           PRINTIT_RED_BIG
                                        }
                                        else {
                                            sprintf(to_print,"+/- Voxel bottom=%d",(int)voxel_bottom);           PRINTIT
                                        }

                                        if (voxels.size()) { sprintf(to_print,"VOXELS:       %10d",voxels.size());           PRINTIT_RED_BIG }
                                        else { sprintf(to_print,"VOXELS:       %10d",voxels.size());           PRINTIT_BIG }

                                        if (voxels_total.size()) { sprintf(to_print,"VOXELS TOTAL: %10d",voxels_total.size());           PRINTIT_RED_BIG }
                                        else { sprintf(to_print,"VOXELS TOTAL: %10d",voxels_total.size());           PRINTIT_BIG }

                                        if (rot_plot) { sprintf(to_print,"Plotting on  Voxel_bottom=%6.3f%%  Max size: %3d (Rot: %3d)",voxel_bottom*100, (int)schematic_size,(flipflop>0)*180);           PRINTIT_RED_BIG }
                                        if (cubic) { sprintf(to_print,"CUBIC (SHIFT+c) = ON (don't trim, make floors)");           PRINTIT_BIG }
                                        else { sprintf(to_print,"CUBIC (SHIFT+c) = OFF (trim y<0 & y>255");           PRINTIT_BIG }

                                } else {
                                    if (do_wuppie) {
                                        sprintf(to_print,"WUPPIE READY!");                    PRINTIT_RED_BIG
                                    }
                                    if (interpolate_on) { sprintf(to_print,"PLAYBACKSPEED: % 10.3f frames/marker",1.0/playbackspeed);                    PRINTIT }
                                    sprintf(to_print,"SECONDS: %.2f   FPS: %.2f   CPU: %3.2f%%   MISSES: %d",render_time,render_fps, cpu_usage*100.0, misses);                    PRINTIT
                                    if (!show_text_short) {
                                        sprintf(to_print,"CURENT:  X=%d  Y=%d",cur_x,cur_y);                    PRINTIT
                                        sprintf(to_print,"EYE:     % 10.3f % 10.3f % 10.3f",eye2[0],eye2[1],eye2[2]);                    PRINTIT
                                        sprintf(to_print,"LOOKAT:  % 10.3f % 10.3f % 10.3f",lookat2[0],lookat2[1],lookat2[2]);                    PRINTIT
                                        sprintf(to_print,"UP:      % 10.3f % 10.3f % 10.3f",up2[0],up2[1],up2[2]);                    PRINTIT
                                        sprintf(to_print,"QUAT2:   % 10.3f % 10.3f % 10.3f% 10.3f",curr_quat2[0],curr_quat2[1],curr_quat2[2],curr_quat2[3]);                    PRINTIT
                                        sprintf(to_print,"TRANSL.: % 10.3f % 10.3f % 10.3f",translation[0],translation[1],translation[2]);                    PRINTIT
                                        sprintf(to_print,"MOVE:    % 10.3f % 10.3f % 10.3f",move_object_x,move_object_y,move_object_z);                    PRINTIT
                                        sprintf(to_print,"ADD:     % 10.3f % 10.3f % 10.3f",add_xyz.x, add_xyz.y, add_xyz.z );                    PRINTIT
                                        sprintf(to_print,"TOT:     % 10.3f % 10.3f % 10.3f",btot[0],btot[1],btot[2] );                    PRINTIT
                                        sprintf(to_print,"LAT:     % 10.6f TO % 10.6f  CENTER: % 10.6f  DIFF: % 10.6f",(float)lat_max,(float)lat_min,(float)(lat_max+lat_min)/2.0,(float)(lat_max-lat_min) );                   PRINTIT_BIG
                                        sprintf(to_print,"LON:     % 10.6f TO % 10.6f  CENTER: % 10.6f  DIFF: % 10.6f",(float)lon_min,(float)lon_max,(float)(lon_max+lon_min)/2.0,(float)(lon_max-lon_min) );                    PRINTIT_BIG

                                        if (btot[0]!=0.0 && btot[1]!=0.0 && btot[2]!=0.0 ) {
                //                            sprintf(to_print,"%:       % 16.12f  % 16.12f  % 16.12f",
                //                                            (double)move_object_z/((double)bmax[0] - (double)bmin[0])   ,
                //                                            (double)move_object_x/((double)bmax[1] - (double)bmin[1])   ,
                //                                            (double)move_object_y/((double)bmax[2] - (double)bmin[2])   ); PRINTIT
                                            sprintf(to_print,"%:       % 16.12f  % 16.12f",
                                                            (double)move_object_x/((double)btot[1])   ,
                                                            (double)move_object_y/((double)btot[2])   ); PRINTIT
                //                            double ctr_lat=((lat_max-lat_min)*(  -(double)move_object_y/((double)bmax[2] - (double)bmin[2])  )) + (lat_max+lat_min)/2.0;
                //                            double ctr_lon=((lon_max-lon_min)*(  -(double)move_object_x/((double)bmax[1] - (double)bmin[1])  )) + (lon_max+lon_min)/2.0;
                //                            double ctr_lat=((lat_max-lat_min)*(  -(double)move_object_y/((double)btot[2])  )) + (lat_max+lat_min)/2.0;
                //                            double ctr_lon=((lon_max-lon_min)*(  -(double)move_object_x/((double)btot[1])  )) + (lon_max+lon_min)/2.0;
                                            sprintf(to_print,"CTR LAT: % 16.12f",ctr_lat);
                                            if (ctr_lat>lat_min && ctr_lat<lat_max) { PRINTIT_BIG } else { PRINTIT_RED_BIG }
                                            sprintf(to_print,"CTR LON: % 16.12f",ctr_lon);
                                            if (ctr_lon>lon_min && ctr_lon<lon_max) { PRINTIT_BIG } else { PRINTIT_RED_BIG }
                                            double test_move_object_y = - (double)(btot[2]) * ( ctr_lat - (lat_max+lat_min)/2.0 ) / (lat_max-lat_min);
                                            double test_move_object_x = - (double)(btot[1]) * ( ctr_lon - (lon_max+lon_min)/2.0 ) / (lon_max-lon_min);
                //                            double test_move_object_y = - (double)(bmax[2] - bmin[2]) * ( ctr_lat - (lat_max+lat_min)/2.0 ) / (lat_max-lat_min);
                //                            double test_move_object_x = - (double)(bmax[1] - bmin[1]) * ( ctr_lon - (lon_max+lon_min)/2.0 ) / (lon_max-lon_min);
                                            sprintf(to_print,"TEST:    % 16.12f % 16.12f",test_move_object_x,test_move_object_y);                    PRINTIT

                                        }


                //                        sprintf(to_print,"TEST:    % 10.3f % 10.3f % 10.3f",test_pos.x, test_pos.y, test_pos.z );                    PRINTIT
                                        sprintf(to_print,"ROTATE:  % 10.3f % 10.3f % 10.3f",rotate_object_x,rotate_object_y,rotate_object_z);                    PRINTIT
                                        sprintf(to_print,"QUAT1:   % 10.3f % 10.3f % 10.3f% 10.3f",curr_quat1[0],curr_quat1[1],curr_quat1[2],curr_quat1[3]);                    PRINTIT
                                        sprintf(to_print,"SCALE:   % 10.3f",scale);                    PRINTIT
                                        sprintf(to_print,"EXTENT:  % 10.3f",maxExtent);                PRINTIT
                                        i++;
                                        sprintf(to_print,"CENTER/REL X: % 12.3f   SIZE X: % 12.3f   REAL CENTER AT % 9.1f",   -0.5 * (bmax[0] + bmin[0]),     ((double)bmax[0] - (double)bmin[0]) ,     (double)enschede_x  );   PRINTIT
                                        sprintf(to_print,"CENTER/REL Y: % 12.3f   SIZE Y: % 12.3f   REAL CENTER AT % 9.1f",   -0.5 * (bmax[1] + bmin[1]),     ((double)bmax[1] - (double)bmin[1]) ,     (double)enschede_y  );   PRINTIT
                                        sprintf(to_print,"CENTER/REL Z: % 12.3f   SIZE Z: % 12.3f   REAL CENTER AT % 9.1f",   -0.5 * (bmax[2] + bmin[2]),     ((double)bmax[2] - (double)bmin[2]) ,     (double)enschede_z  );   PRINTIT
                                        i++;
                                        sprintf(to_print,"BMIN[0]: % 10.6f  BMAX[0]: % 10.6f  DIFF: % 10.6f  CNTR: % 10.6f",bmin[0],bmax[0],bmax[0]-bmin[0],(bmin[0]+bmax[0])/2.0);                    PRINTIT
                                        sprintf(to_print,"BMIN[1]: % 10.6f  BMAX[1]: % 10.6f  DIFF: % 10.6f  CNTR: % 10.6f",bmin[1],bmax[1],bmax[1]-bmin[1],(bmin[1]+bmax[1])/2.0);                    PRINTIT
                                        sprintf(to_print,"BMIN[2]: % 10.6f  BMAX[2]: % 10.6f  DIFF: % 10.6f  CNTR: % 10.6f",bmin[2],bmax[2],bmax[2]-bmin[2],(bmin[2]+bmax[2])/2.0);                    PRINTIT
                                        i++;
                                        sprintf(to_print,"PERSPECTIVE ANGLE: % 10.6f",perspective[0]);                    PRINTIT
                                        sprintf(to_print,"PERSPECTIVE RATIO: % 10.6f",perspective[1]);                    PRINTIT
                                        sprintf(to_print,"PERSPECTIVE MIN:   % 10.6f",perspective[2]);                    PRINTIT
                                        sprintf(to_print,"PERSPECTIVE MAX:   % 10.6f",perspective[3]);                    PRINTIT
                                        i++;
                                        sprintf(to_print,"AREA: %s / %s",my_area.c_str(),area.c_str());                    PRINTIT
                                        sprintf(to_print,"LAT=% 13.9f  LON=% 13.9f",(float)lat,(float)lon);                    PRINTIT
                                        sprintf(to_print,"911 %s",remember_911 ? "true" : "false");                    PRINTIT
                                        sprintf(to_print,"911 2) %s",remember_911_2 ? "true" : "false");                    PRINTIT
                                        sprintf(to_print,"911 3) %s",remember_911_3 ? "true" : "false");                    PRINTIT
                                        sprintf(to_print,"MOUSE: %d,%d",mi.x,mi.y);           PRINTIT
                                        sprintf(to_print,"MOUSE: %8.6f,%8.6f",mf.x,mf.y);           PRINTIT

                                        sprintf(to_print,"antialiasingLevel: %d",contextSettings.antialiasingLevel);           PRINTIT
                                        sprintf(to_print,"Max schematic size: %10d",(int)schematic_size);           PRINTIT
                                        if (winsize) {
                                            sprintf(to_print,"4K");           PRINTIT
                                        }
                                    }
                                }
                            }


                            window.popGLStates();
                        } else {
                            if (frustum==false || (frustum==true && frustum_count_x==frustum_size_x-1 && frustum_count_y==frustum_size_y-1)) {
                                window.pushGLStates();
                                text_mutex.lock();
                                text_text->setPosition( 266,(float)(1080-30));
                                window.draw(*text_text);
                                text_mutex.unlock();
                                window.popGLStates();
                            }
    //                        sprintf(to_print,"PACMAN GRAPHICS(c)");             draw2_all(window,(char*)to_print,1920-16*16,1080-40,sf::Color(50,50,255,64),sf::Color::White);
                        }

                    }


