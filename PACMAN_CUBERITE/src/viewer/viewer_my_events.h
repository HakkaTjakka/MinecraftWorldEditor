extern void flush_voxels();
extern void make_test_schematic();

                static bool first_m=true;

                if ((event_system==0 || load_more || load_extra ) && !exit_thread) {
                    active_window_num=win_num;
                    static FILE * file_arr;
                    static char line[200]="";
//                    while ((window.pollEvent(event)) && !exit_thread)
                    static int no_more=10;
//                    while ((window.pollEvent(event) ) && !exit_thread)
                    int flipper=0;
                    while ((window.pollEvent(event) || load_more || load_extra) && !exit_thread && flipper<50)
                    {
                        flipper++;
                        if (fly_on) {
                            if (event.mouseButton.button == sf::Mouse::Left || sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                    interface_mutex.lock();
                                    sending_new_mouse=sf::Vector2i(-1,-1);
                                    interface_mutex.unlock();
                                } else {
                                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
                                        sf::Vector2i sending_new_mouse_tmp = sf::Mouse::getPosition(window);
                                        if (!(sending_new_mouse_tmp.x >= 0 && sending_new_mouse_tmp.x <= window.getSize().x
                                                && sending_new_mouse_tmp.y >= 0 && sending_new_mouse_tmp.y <= window.getSize().y))  {
                                            interface_mutex.lock();
                                            sending_new_mouse=sf::Vector2i(-1,-1);
                                            interface_mutex.unlock();
                                        } else {
                                            interface_mutex.lock();
                                            sending_new_mouse=sending_new_mouse_tmp;
                                            interface_mutex.unlock();
                                        }
                                    } else {
                                        interface_mutex.lock();
                                        sending_new_mouse=sf::Vector2i(-1,-1);
                                        interface_mutex.unlock();
                                    }
                                }
                            }
                        }
                        if (event.type == sf::Event::MouseWheelScrolled) {
                            delta_mutex.lock();
                            mousewheel_delta=mousewheel_delta + event.mouseWheelScroll.delta;
                            delta_mutex.unlock();
//                            printf("New mousewheel_delta=%f ",mousewheel_delta);
                        }
                        event_happened=true;
    //                    if (loaded==1) printf("13-");
                        if (event.type == sf::Event::Closed) {
                            exit_code=0;
                            exit_thread = true;
                        } else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
                            if (event.type == sf::Event::MouseButtonPressed) {
//                                if (rotate_object_x!=0.0 ||rotate_object_y!=0.0 ||rotate_object_z!=0.0 ) {
                                    angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
//                                }
                            } else {
                                float r_x=rotate_object_x,r_y=rotate_object_y,r_z=rotate_object_z;
//                                if (curr_quat2[0]!=0.0 || curr_quat2[1]!=0.0 || curr_quat2[2]!=0.0 || curr_quat2[3]!=0.0) {
//                                    quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                    quat_to_angles(curr_quat2, prev_quat2, rotate_object_x,rotate_object_y, rotate_object_z);
                                    rotate_object_x+=r_x; rotate_object_y+=r_y; rotate_object_z+=r_z;
//                                }
                            }
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                if (event.type == sf::Event::MouseButtonPressed) {
        //                            printf("Pressed left\n");
                                    mouseLeftPressed2 = true;
                                    last_left_mouse = true;
                                    trackball(prev_quat2, 0.0, 0.0, 0.0, 0.0);
                                } else if (event.type == sf::Event::MouseButtonReleased) {
        //                            printf("Released left\n");
                                    mouseLeftPressed2 = false;
                                }

                            } else if (event.mouseButton.button == sf::Mouse::Right) {

                                if (event.type == sf::Event::MouseButtonPressed) {
        //                            printf("Pressed right\n");
                                    mouseRightPressed2 = true;
                                    last_right_mouse = true;
                                } else if (event.type == sf::Event::MouseButtonReleased) {
        //                            printf("Released right\n");
                                    mouseRightPressed2 = false;
                                }

                            } else if (event.mouseButton.button == sf::Mouse::Middle) {

                                if (event.type == sf::Event::MouseButtonPressed) {
                                    mouseMiddlePressed2 = true;
                                    last_middle_mouse = true;
        //                            printf("Pressed middle\n");
                                } else if (event.type == sf::Event::MouseButtonReleased) {
                                    mouseMiddlePressed2 = false;
        //                            printf("Released middle\n");
                                }

                            }
                        } else if (event.type == sf::Event::MouseMoved) {
                            double mouse_x = (double) event.mouseMove.x ;
                            double mouse_y = (double) event.mouseMove.y ;

                            if (mouseLeftPressed2)
                            {
                                trackball(prev_quat2,
                                          rotScale * (2.0f * prevMouseX2 - width2) / (float)width2,
                                          rotScale * (height2 - 2.0f * prevMouseY2) / (float)height2,
                                          rotScale * (2.0f * mouse_x - width2) / (float)width2,
                                          rotScale * (height2 - 2.0f * mouse_y) / (float)height2);

                                add_quats(prev_quat2, curr_quat2, curr_quat2);
                            }
                            else if (mouseMiddlePressed2)
                            {
                                eye2[0] -= transScale * (mouse_x - prevMouseX2) / (float)width2;
                                lookat2[0] -= transScale * (mouse_x - prevMouseX2) / (float)width2;
                                eye2[1] += transScale * (mouse_y - prevMouseY2) / (float)height2;
                                lookat2[1] += transScale * (mouse_y - prevMouseY2) / (float)height2;
                            }
                            else if (mouseRightPressed2)
                            {
                                eye2[2] += 2*transScale * (mouse_y - prevMouseY2) / (float)height2;
                                lookat2[2] +=2* transScale * (mouse_y - prevMouseY2) / (float)height2;
                            }

                            // Update mouse point
                            prevMouseX2 = mouse_x;
                            prevMouseY2 = mouse_y;


                        } else if (event.type == sf::Event::KeyPressed || load_more || load_extra) {
                            float trans=transScale;
                            float rot=rotScale;
                            static sf::Vector2u old_size1;
                            static sf::Vector2i old_pos1;
                            static sf::Vector2u old_size2=sf::Vector2u(1920/2,1080/2);
                            static sf::Vector2i old_pos2=sf::Vector2i(1920/4,1080/4);
                            static int Digs = DECIMAL_DIG;
                            static double qx,qy,qz,qw;
                            static double lx,ly,lz;
                            static double ex,ey,ez;
                            static double tx,ty,tz;
                            static double p0,p1,p2,p3;
                            static double bmin0,bmin1,bmin2;
                            static double bmax0,bmax1,bmax2;

                            static int viewport_x=0,viewport_y=0;
//                            double length;
                            static float zoom_factor=0.975;
                            int x,y;
                            int cool;
                            bool add_on=false;
                            if (event.type == sf::Event::KeyPressed) {
                                switch(event.key.code)
                                {
                                    case sf::Keyboard::A:
                                        if (event.key.control) {
                                            plot_func=!plot_func;
                                            if (plot_func) {
                                                get_one_3d_init_load_obj_data(cur_x,my_area,win_num,pac_obj2_arr_used,pac_obj2_arr, window);
                                                printf("Plotfunc=ON\n");
                                                selector_pos.x=0;
                                                selector_pos.y=0;
                                            } else {
                                                printf("Plotfunc=OFF\n");
                                                selector_pos.x=-1;
                                                selector_pos.y=-1;
                                            }
                                            break;
                                        }
                                        if (event.key.alt) {
                                            plot_quick=!plot_quick;
                                            if (plot_quick) {
                                                printf("Plot_quick=ON\n");
                                            } else {
                                                printf("Plot_quick=OFF\n");
                                            }
                                            break;
                                        }
                                        if (event.key.shift) {
                                            printf("SELECTED POS: X=%d,Y=%d %s\n",selector_pos.x,selector_pos.y,selector_dir.c_str());
                                            int x=selector_pos.x;
                                            int y=selector_pos.y;

                                            std::string filename=get_area_data(std::string() + "Models",cur_x,cur_y);
                                            filename=filename.substr(0,filename.length());
                                            std::string my_area=GetFileName(filename);
                                            my_area=my_area.substr(0,my_area.length()-4);

                                            get_area_data(my_area,x,y);
                                            char line[2000];
                                            strcpy(line,latitude_longditude.c_str());
                                            while (replace_str(line,".",","));
                                            double lat_north=0.0;
                                            double lat_south=0.0;
                                            double lon_west=0.0;
                                            double lon_east=0.0;
                                            int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                                            if (num==4) {
                                                char lat_str[100];
                                                char lon_str[100];
                                                sprintf(lat_str,"%lf",(lat_north+lat_south)/2.0); while (replace_str(lat_str,",","."));
                                                sprintf(lon_str,"%lf",(lon_east+lon_west)/2.0); while (replace_str(lon_str,",","."));
                                                if (!burn) {
                                                    printf("https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
                                                }
                                            }
                                            break;
                                        }
                                        get_view(rotate_object_z, curr_quat2,eye2,lookat2,translation,perspective,bmin,bmax,frustum_toggle);

                                        maxExtent = 0.5f * (bmax[0] - bmin[0]);
                                        if (maxExtent < 0.5f * (bmax[1] - bmin[1])) maxExtent = 0.5f * (bmax[1] - bmin[1]);
                                        if (maxExtent < 0.5f * (bmax[2] - bmin[2])) maxExtent = 0.5f * (bmax[2] - bmin[2]);
                                        break;
                                    case sf::Keyboard::B:
                                        if (event.key.control && event.key.alt) {
//todo
//                                            get_one_3d_init(cur_x,my_area,win_num,pac_obj2_arr_used,pac_obj2_arr, window);
                                            set_view_3d(cur_x,my_area,win_num,pac_obj2_arr_used,pac_obj2_arr, window);
                                            frustum=true;
//                                            plot_func=false;
                                            get_view(rotate_object_z, curr_quat2,eye2,lookat2,translation,perspective,bmin,bmax,frustum_toggle);

                                            maxExtent = 0.5f * (bmax[0] - bmin[0]);
                                            if (maxExtent < 0.5f * (bmax[1] - bmin[1])) maxExtent = 0.5f * (bmax[1] - bmin[1]);
                                            if (maxExtent < 0.5f * (bmax[2] - bmin[2])) maxExtent = 0.5f * (bmax[2] - bmin[2]);
/*
                                            printf("VIEW: q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum==%d\n",
                                                    int_q[0],int_q[1],int_q[2],int_q[3],
                                                    int_e[0],int_e[1],int_e[2],
                                                    int_l[0],int_l[1],int_l[2],
                                                    int_t[0],int_t[1],int_t[2],
                                                    int_p[0],
                                                    int_bmin[0], int_bmin[1], int_bmin[2],
                                                    int_bmax[0], int_bmax[1], int_bmax[2], int_frustum_toggle
                                                   );
*/
                                            break;
                                        }
                                        if (event.key.control) {
                                            if (burn) {
                                                burn=false;
                                                break;
                                            }
                                            while (Pacman_Objects[win_num].size()>0) {
                                                int wn=0;
                                                printf("Erasing: X=%d,Y=%d\n",Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y);
                                                erase_one_pacman_objects(Pacman_Objects[win_num][0].map_x,Pacman_Objects[win_num][0].map_y,win_num,pac_obj2_arr_used,pac_obj2_arr);
                                            }
                                            if (get_one_3d_init(cur_x,my_area,win_num,pac_obj2_arr_used,pac_obj2_arr, window)) {
                                                b_o_x=-1;
                                                b_o_y=-1;
                                                start_burn=true;
                                                burn=true;
                                                switch_to_full_screen=true;
                                                contextSettings.antialiasingLevel = 4;
                                                videomode[win_num]=1;
                                                show_text=false;
                                                frustum=true;
                                                plot_func=false;
                                                get_view(rotate_object_z, curr_quat2,eye2,lookat2,translation,perspective,bmin,bmax,frustum_toggle);
                                                maxExtent = 0.5f * (bmax[0] - bmin[0]);
                                                if (maxExtent < 0.5f * (bmax[1] - bmin[1])) maxExtent = 0.5f * (bmax[1] - bmin[1]);
                                                if (maxExtent < 0.5f * (bmax[2] - bmin[2])) maxExtent = 0.5f * (bmax[2] - bmin[2]);
/*
                                                printf("VIEW: q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum==%d\n",
                                                        int_q[0],int_q[1],int_q[2],int_q[3],
                                                        int_e[0],int_e[1],int_e[2],
                                                        int_l[0],int_l[1],int_l[2],
                                                        int_t[0],int_t[1],int_t[2],
                                                        int_p[0],
                                                        int_bmin[0], int_bmin[1], int_bmin[2],
                                                        int_bmax[0], int_bmax[1], int_bmax[2], int_frustum_toggle
                                                       );
*/
                                            }

                                        } else if (event.key.shift) {
                                            if (!frustum) {
                                                printf("No frustum set: ctrl/shift/alt-f, ctrl/shift/alt-v, ctrl/shift/alt-h\n");
                                            }
                                            else {
//changed
                                                int old=contextSettings.antialiasingLevel;
                                                contextSettings.antialiasingLevel = 0; // make shure there is no antialias, for getting colors from gpu that owns object# data (red=x, blue=y)
                                                window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                                window.setVerticalSyncEnabled(true);
                                                analyse_3d(lat, lon, my_area,cur_x,win_num,window,eye2,perspective,frustum_toggle,
                                                test, maxExtent,  lookat2,  up2,
                                                move_object_x,  move_object_y,  move_object_z, translation,
                                                curr_quat2, bmin, bmax);
                                                contextSettings.antialiasingLevel = old;
                                                window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                                window.setVerticalSyncEnabled(true);
                                            }
                                        } else if (event.key.alt) {
                                            create_nbt(my_area, window, win_num, pac_obj2_arr_used, pac_obj2_arr);
/*
                                            int old=contextSettings.antialiasingLevel;
                                            contextSettings.antialiasingLevel = 0; // make shure there is no antialias, for getting colors from gpu that owns object# data (red=x, blue=y)
                                            reanalyse_3d(cur_x,my_area,win_num,pac_obj2_arr_used,pac_obj2_arr, window);
                                            get_one_3d_init_load_obj_data(cur_x,my_area,win_num,pac_obj2_arr_used,pac_obj2_arr, window);
                                            analyse_3d(lat, lon, my_area,cur_x,win_num,window,eye2,perspective,frustum_toggle,
                                            test, maxExtent,  lookat2,  up2,
                                            move_object_x,  move_object_y,  move_object_z, translation,
                                            curr_quat2, bmin, bmax);
                                            contextSettings.antialiasingLevel = old;
                                            window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
*/

                                        } else {
                                            if (create_boundaries(my_area,window)) {
//                                                my_area="Models";
//                                                area="Models";
//                                                to_load.push_back(glm::vec2(0,0));
//                                                cur_x=0;cur_y=0;
//                                                load_more=true;
//                                                yo_combine=1;
//                                                add_on=true;
//                                                exit_code=-20;
//                                                no_new_window=true;
//                                                exit_thread = true;
                                            }
                                            break;
                                        }
                                        break;
                                    case sf::Keyboard::D:
                                        if (event.key.control) {
                                            exit_code=-20;
                                            exit_thread = true;
                                            break;
                                        }
                                        if (depth_shader_on)
                                            sf::Shader::bind(NULL);
                                        else {
                                            if (!depth_shader.loadFromFile("shaders/depth_shader.vert","shaders/depth_shader.frag"))
                                            {
                                                printf("FRAGMENT SHADER ERROR: %s\n","shaders/depth_shader.frag");
                                            } else {
//                                                depth_shader.setUniform("texture", sf::Shader::CurrentTexture);
                                                depth_shader.setUniform("the_texture", sf::Shader::CurrentTexture);
                                                depth_shader.setUniform("wave_amplitude", sf::Vector2f(5.0, 5.0));
                                                depth_shader.setUniform("WIRE_FRAME", WIRE_FRAME);
                                                depth_shader.setUniform("TEXTURE_ARRAY", TEXTURE_ARRAY);
                                                depth_shader.setUniform("COLOR_ARRAY", COLOR_ARRAY);
                                                printf("FRAGMENT SHADER LOADED: %s\n","shaders/depth_shader.frag");
                                            }
                                            sf::Shader::bind(&depth_shader);
                                        }
                                        depth_shader_on=!depth_shader_on;
                                        break;
                                    case sf::Keyboard::M:
                                        if (event.key.shift) {
                                            int x=-99999; int y=0;
                                            if (get_area_data(my_area,x,y)!="") {
                                                to_load.push_back(glm::vec2(-99999,0));
                                                load_more=true;
                                                old_cur_x=cur_x;
                                                old_cur_y=cur_y;
                                            }
                                            break;
                                        }
                                        {
                                            if (first_m) {
                                                printf("Saving object array data\n");
                                                file_arr = fopen ("OBJECT_ARRAY.TXT", "w");
                                                for (auto u : Pacman_Objects[win_num]) {
                                                    fprintf(file_arr,"X=%d Y=%d\n",u.map_x,u.map_y);
                                                    printf("X=%d Y=%d\n",u.map_x,u.map_y);
                                                }
                                                fclose(file_arr);
                                                first_m=false;
                                            }
                                        }
                                        qx=curr_quat2[0]; qy=curr_quat2[1]; qz=curr_quat2[2]; qw=curr_quat2[3];
                                        if (frustum_toggle==1) {
                                            ex=eye2[0];     ey=eye2[1];         ez=eye2[2]; //  ez=eye2[2]+3.0f; hoppa
                                            lx=lookat2[0];  ly=lookat2[1];      lz=lookat2[2];
                                        } else {
                                            ex=eye2[0];     ey=eye2[1];         ez=eye2[2];
                                            lx=lookat2[0];  ly=lookat2[1];      lz=lookat2[2];
                                        }
//                                        ex=eye2[0]; ey=eye2[1]; ez=eye2[2];
//                                        lx=lookat2[0]; ly=lookat2[1]; lz=lookat2[2];
                                        tx=translation[0]; ty=translation[1]; tz=translation[2];
                                        p0=perspective[0];p1=perspective[1];p2=perspective[2];p3=perspective[3];
                                        bmin0=bmin[0];bmin1=bmin[1];bmin2=bmin[2];
                                        bmax0=bmax[0];bmax1=bmax[1];bmax2=bmax[2];

                                        angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                        build_rotmatrix_glm(rot_mat, curr_quat2);
                                        quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);

                                        char test[1000];
                                        marker_file = fopen (marker_filename, "a"); //reopen, continue marking...
                                        fprintf(marker_file, "QUATS=%-+e %-+e %-+e %-+e EYE=%-+e %-+e %-+e LOOKAT=%-+e %-+e %-+e TRANSLATION=%-+e %-+e %-+e PERSPECTIVE=%-+e %-+e %-+e %-+e BMIN=%-+e %-+e %-+e BMAX=%-+e %-+e %-+e FRUSTUM=%d\n",
                                                  qx,   qy,  qz,  qw,
                                                  ex,   ey,  ez,
                                                  lx,   ly,  lz,
                                                  tx,   ty,  tz,
                                                  p0,   p1,  p2,  p3,
                                                  bmin0,bmin1,bmin2,
                                                  bmax0,bmax1,bmax2,frustum_toggle
                                                  );
                                        fprintf(marker_file, "MATRIX=%-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e %-+e\n",
                                                  (double)rot_arr[0], (double)rot_arr[1], (double)rot_arr[2], (double)rot_arr[3],
                                                  (double)rot_arr[4], (double)rot_arr[5], (double)rot_arr[6], (double)rot_arr[7],
                                                  (double)rot_arr[8], (double)rot_arr[9], (double)rot_arr[10],(double)rot_arr[11],
                                                  (double)rot_arr[12],(double)rot_arr[13],(double)rot_arr[14],(double)rot_arr[15],
                                                  (double)rotate_object_z+rotate_object_z_to_add);

                                        fclose(marker_file);
                                        printf("MARK: c=%d t=%-+f q0=%-+f q1=%-+f q2=%-+f q3=%-+f  e0=%-+f e1=%-+f e2=%-+f  l0=%-+f l1=%-+f l2=%-+f  t0=%-+f t1=%-+f t2=%-+f  p0=%-+f  bmin=%-+f %-+f %-+f  bmax=%-+f %-+f %-+f  frustum=%d\n",0,0,
                                                  (float)qx,   (float)qy,  (float)qz,  (float)qw,
                                                  (float)ex,   (float)ey,  (float)ez,
                                                  (float)lx,   (float)ly,  (float)lz,
                                                  (float)tx,   (float)ty,  (float)tz,
                                                  (float)p0,   // (float)p1,  (float)p2,  (float)p3,
                                                  (float)bmin0,(float)bmin1,(float)bmin2,
                                                  (float)bmax0,(float)bmax1,(float)bmax2,frustum_toggle
                                               );
                                        printf("MARK: R00=%-+f R01=%-+f R02=%-+f R03=%-+f\n",
                                                rot_arr[0], rot_arr[1], rot_arr[2], rot_arr[3]);
                                        printf("      R10=%-+f R11=%-+f R12=%-+f R13=%-+f\n",
                                                rot_arr[4], rot_arr[5], rot_arr[6], rot_arr[7]);
                                        printf("      R20=%-+f R21=%-+f R22=%-+f R23=%-+f\n",
                                                rot_arr[8], rot_arr[9], rot_arr[10],rot_arr[11]);
                                        printf("      R30=%-+f R31=%-+f R32=%-+f R33=%-+f\n",
                                                rot_arr[12],rot_arr[13],rot_arr[14],rot_arr[15]);


                                        printf("ROTATION_Z%=%-+f\n",rotate_object_z+rotate_object_z_to_add);
    /*
                                        sprintf(test, "QUATS=%-+e %-+e %-+e %-+e EYE=%-+e %-+e %-+e LOOKAT=%-+e %-+e %-+e TRANSLATION=%-+e %-+e %-+e PERSPECTIVE=%-+e %-+e %-+e %-+e\n",
                                                  qx,   qy,  qz,  qw,
                                                  ex,   ey,  ez,
                                                  lx,   ly,  lz,
                                                  tx,   ty,  tz,
                                                  p0,   p1,  p2,  p3);
                                        sscanf(test,"QUATS=%e %e %e %e EYE=%e %e %e LOOKAT=%e %e %e TRANSLATION=%e %e %e PERSPECTIVE=%e %e %e %e\n",
                                                 &qx,  &qy, &qz, &qw,
                                                 &ex,  &ey, &ez,
                                                 &lx,  &ly, &lz,
                                                 &tx,  &ty, &tz,
                                                 &p0,  &p1, &p2, &p3);
                                        fprintf(marker_file, "->\nQUATS=%-+e %-+e %-+e %-+e EYE=%-+e %-+e %-+e LOOKAT=%-+e %-+e %-+e TRANSLATION=%-+e %-+e %-+e PERSPECTIVE=%-+e %-+e %-+e %-+e\n\n",
                                                  qx,   qy,  qz,  qw,
                                                  ex,   ey,  ez,
                                                  lx,   ly,  lz,
                                                  tx,   ty,  tz,
                                                  p0,   p1,  p2,  p3);
    */
                                        if (event.key.control) {
                                            rotate_object_z_to_add+=90.0;
                                            break;
                                        }
                                        if (event.key.alt) {
                                            rotate_object_z_to_add-=90.0;
                                            break;
                                        }
                                        break;
                                    case sf::Keyboard::G:
                                        if (frustum) {
                                            frustum_count_x=frustum_size_x-1;
                                            frustum_count_y=frustum_size_y-1;
//                                            screen_width=window.getSize().x;
//                                            screen_height=window.getSize().y;
                                            show_text=false;
                                            remember_911=true;
//                                            window.setVerticalSyncEnabled(false);

                                            if (videomode[win_num]==1) {
                                                videomode[win_num]=0;
                                                old_size2=window.getSize();
                                                old_pos2=window.getPosition();
                                                old_size[win_num]=old_size2;
                                                old_pos[win_num]=old_pos2;
//                                                old_size[win_num]=sf::Vector2u(1920,1080);
//                                                old_pos[win_num]=sf::Vector2i(0,0);
                                                window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                                window.setVerticalSyncEnabled(true);

                                                hglrc[win_num] = wglGetCurrentContext();
                                                hwnd[win_num] = window.getSystemHandle();
                                                hdc[win_num] = GetDC(hwnd[win_num]) ;

//                                                window.setSize(old_size[win_num]);
//                                                window.setPosition(old_pos[win_num]);
                                                width2 = 1920.0;
                                                height2 = 1080.0;

                                                window.setActive(true);

                                                perspective[1]=1920.0/1080.0;
                                            }

                                            clock_911.restart();
//                                            loaded=1;
//                                            round=3;

                                        }
                                        break;
                                    case sf::Keyboard::H:
                                        if (frustum) {
                                            if (event.key.control) {
                                                if (rectangle.getPosition().x>10) {
                                                    rectangle.setPosition(rectangle.getPosition().x-10,rectangle.getPosition().y);
                                                } else {
                                                    rectangle.setPosition(0,rectangle.getPosition().y);
                                                }
                                            } else if (event.key.alt) {
                                                if (rectangle.getPosition().x<1920.0-10) {
                                                    if (rectangle.getPosition().x+rectangle.getSize().x<1920.0-10) {
                                                        rectangle.setPosition(rectangle.getPosition().x+10,rectangle.getPosition().y);
                                                    } else {
                                                        rectangle.setPosition(rectangle.getPosition().x+1,rectangle.getPosition().y);
                                                    }
                                                }
                                            } else if (event.key.shift) {
                                                if (frustum_size_x>1) frustum_size_x--;
                                            }  else {
                                                if ((frustum_size_x+1)*rectangle.getSize().x+rectangle.getPosition().x<1920.0-1)
                                                    frustum_size_x++;
                                                if (frustum_size_x==20) printf("Insane!!!\n");
                                            }
                                            break;
                                        }
                                    case sf::Keyboard::V:
                                        if (frustum) {
                                            if (event.key.control) {
                                                if (rectangle.getPosition().y>10) {
                                                    rectangle.setPosition(rectangle.getPosition().x,rectangle.getPosition().y-10);
                                                } else {
                                                    rectangle.setPosition(rectangle.getPosition().x,rectangle.getPosition().y-1);
                                                }
                                            } else if (event.key.alt) {
                                                if (rectangle.getPosition().y<1080.0-1) {
                                                    if (rectangle.getPosition().y+rectangle.getSize().y<1080.0-10) {
                                                        rectangle.setPosition(rectangle.getPosition().x,rectangle.getPosition().y+10);
                                                    } else {
                                                        rectangle.setPosition(rectangle.getPosition().x,rectangle.getPosition().y+1);
                                                    }
                                                }
                                            } else if (event.key.shift) {
                                                if (frustum_size_y>1) frustum_size_y--;
                                            } else {
                                                if ((frustum_size_y+1)*rectangle.getSize().y+rectangle.getPosition().y<1080.0-1)
                                                    frustum_size_y++;
                                                if (frustum_size_y==20) printf("Insane!!!\n");
                                            }
                                            break;
                                        }
                                        break;
                                    case sf::Keyboard::F3:
                                        if (event.key.shift) {
                                        } else
                                            frustum_toggle=(frustum_toggle+1)%2;
                                        break;
                                    case sf::Keyboard::F:
                                        if (!event.key.control && !event.key.alt && event.key.shift) {
                                            remember_911_2=!remember_911_2;
                                            if (remember_911_2) {
                                                printf("FRUSTUM ON: X=%d/%d , Y=%d/%d\n",frustum_count_x,frustum_size_x,frustum_count_y,frustum_size_y);
                                                get_one_3d_update_load_obj_data();
                                            }
                                            else printf("FRUSTUM OFF\n");
                                            break;
                                        }
//                                        } else {
                                        if (!event.key.control && !event.key.alt) {
                                            frustum=!frustum;
                                            static bool first=true;
                                            if (frustum && first) {
                                                rectangle.setPosition(0,0);
                                                rectangle.setSize(sf::Vector2f(1920.0/(float)fixed,1080.0/(float)fixed));
                                                frustum_size_x=fixed;
                                                frustum_size_y=fixed;
                                                show_text=true;
                                                first=false;
                                            }
                                            if (frustum) {
                                                if (videomode[win_num]==1) {
                                                    switch_to_full_screen=true;
/*
                                                    videomode[win_num]=0;
                                                    old_size[win_num]=sf::Vector2u(1920,1080);
                                                    old_pos[win_num]=sf::Vector2i(0,0);
                                                    old_size2=window.getSize();
                                                    old_pos2=window.getPosition();

                                                    window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);

                                                    window.setSize(old_size[win_num]);
                                                    window.setPosition(old_pos[win_num]);
                                                    width2 = old_size[win_num].x;
                                                    height2 = old_size[win_num].y;
                                                    window.clear(sf::Color(50,20,30,128));
                                                    window.display();

                                                    window.setActive(true);
                                                    perspective[1]=1920.0/1080.0;
*/
                                                }
                                            }
                                            break;
                                        }
                                        if (frustum) {
                                            bool c=true;
                                            if (event.key.control && event.key.shift) {
                                                if (fixed>2) { fixed--; c=false; }
                                            } else if (event.key.alt && event.key.shift) {
                                                fixed++;
                                                c=false;
                                            }
                                            if ((event.key.control && event.key.shift) || (event.key.alt && event.key.shift) && !c ) {
                                                rectangle.setPosition(0,0);
                                                rectangle.setSize(sf::Vector2f(1920.0/(float)fixed,1080.0/(float)fixed));
                                                frustum_size_x=fixed;
                                                frustum_size_y=fixed;
                                                break;
                                            }

                                            if (event.key.control) {
                                                if (rectangle.getSize().x>1 && rectangle.getSize().y>10) {
                                                    rectangle.setSize(sf::Vector2f(
                                                                                   (rectangle.getSize().x-10.0),
                                                                                   (rectangle.getSize().x-10.0)*1080.0/1920.0));
//                                                    rectangle.setSize(sf::Vector2f(rectangle.getSize().x-1,int((rectangle.getSize().x-1)*1080.0/1920.0)));
                                                }
                                                break;
                                            } else if (event.key.alt) {
//                                                if (rectangle.getPosition().x+rectangle.getSize().x<1920.0-10) {
                                                if (rectangle.getPosition().y+rectangle.getSize().y*frustum_size_y<1080.0-10.0) {
                                                    if (rectangle.getPosition().x+rectangle.getSize().x*frustum_size_x<1920.0-10.0) {
//                                                            rectangle.setSize(sf::Vector2f(rectangle.getSize().x+1,int((rectangle.getSize().x+1)*1080.0/1920.0)));
                                                        rectangle.setSize(sf::Vector2f(
                                                                                       (rectangle.getSize().x+10.0),
                                                                                       (rectangle.getSize().x+10.0)*1080.0/1920.0));

                                                    } else {
                                                        rectangle.setSize(sf::Vector2f(
                                                                                       1920.0,
                                                                                       1080.0));
                                                    }
                                                }
//                                                    if (!(rectangle.getSize().y+rectangle.getPosition().y<1080.0)) {
//                                                        rectangle.setSize(sf::Vector2f(rectangle.getSize().x,1080.0-rectangle.getPosition().y-1));
//                                                    }
//                                                }
                                                break;
                                            }
                                        }
                                    case sf::Keyboard::S:
                                        if (event.key.shift) {
                                            scale=scale*0.95;
//                                            glMatrixMode(GL_MODELVIEW);
//                                            glLoadIdentity();
//                                            glScalef(scale,scale,1.0f);
                                            printf("scale=%f       \r",scale);
                                        } else {
                                            scale=scale*(1.0/0.95);
//                                            glMatrixMode(GL_MODELVIEW);
//                                            glLoadIdentity();
//                                            glScalef(scale,scale,1.0f);
                                            printf("scale=%f       \r",scale);
                                        }
                                        break;
                                    case sf::Keyboard::O:
                                        if (event.key.shift) {
                                            printf("Setting all objects to off\n");
//                                            Pacman_Object* po=&Pacman_Object[win_num];
                                            for (std::vector<Pacman_Object>::iterator it=Pacman_Objects[win_num].begin(), end = Pacman_Objects[win_num].end(); it != end; ++it) {
                                                it->show=0;
                                                printf("X=%d Y=%d is off. ",it->map_x,it->map_y);
                                                printf("Pacman_Objects[%d].show=%d\n",win_num,it->show);
                                            }
/*
                                            for (auto u : Pacman_Objects[win_num]) {
                                                Pacman_Objects[win_num][u.arr_index].show=0;
                                                u.show=0;
                                                printf("X=%d Y=%d is on. ",u.map_x,u.map_y);
                                                printf("Pacman_Objects[%d].show=%d\n",win_num,u.show);
                                            }
*/
                                            break;
                                        } else {
                                            printf("Setting all opjects to on\n");
                                            for (std::vector<Pacman_Object>::iterator it=Pacman_Objects[win_num].begin(), end = Pacman_Objects[win_num].end(); it != end; ++it) {
                                                it->show=1;
                                                printf("X=%d Y=%d is on. ",it->map_x,it->map_y);
                                                printf("Pacman_Objects[%d].show=%d\n",win_num,it->show);
                                            }
/*
                                            for (auto u : Pacman_Objects[win_num]) {
                                                Pacman_Objects[win_num][u.arr_index].show=1;
                                                u.show=1;
                                                printf("X=%d Y=%d is on. ",u.map_x,u.map_y);
                                                printf("Pacman_Objects[%d].show=%d\n",win_num,u.show);
                                            }
*/
                                            break;
                                        }
                                    case sf::Keyboard::Z:
                                        printf("Saving object array data\n");
                                        file_arr = fopen ("OBJECT_ARRAY.TXT", "w");
                                        for (auto u : Pacman_Objects[win_num]) {
                                            fprintf(file_arr,"X=%d Y=%d\n",u.map_x,u.map_y);
                                            printf("X=%d Y=%d\n",u.map_x,u.map_y);
                                        }
                                        fclose(file_arr);
                                        break;
                                    case sf::Keyboard::X:
                                        if (0) {
                                            int num_p=0;
                                            int num_pb=0;
                                            int num_p1=0;
                                            int num_p1b=0;
                                            int num_p2=0;
                                            for (std::vector<Pacman_Object>::iterator p=Pacman_Objects[win_num].begin(), end = Pacman_Objects[win_num].end(); p != end; ++p) {

    //                                            for (auto p : Pacman_Objects[win_num]) {
                                                {
                                                    num_p1=0;
                                                    GLuint gluint_arr[p->textures.size()];
                                                    int num_com=0;
                                                    for (auto u : p->textures) {
                                                        gluint_arr[num_com++]=u.second;
                                                        if (!(num_com&0xff) || num_com==p->textures.size()) printf("object#=%d index=%d glDeleteTextures() texture#=%d\r",num_p2,p->arr_index,num_p1);
                                                        num_p++;
                                                        num_p1++;
                                                    }
                                                    glDeleteTextures((GLsizei)p->textures.size(), gluint_arr);
                                                }
                                                {

                                                    num_p1b=0;
                                                    GLuint gluint_arr[p->gDrawObjects.size()];
                                                    int num_com=0;
                                                    for (auto u : p->gDrawObjects) {
                                                        gluint_arr[num_com++]=u.vb_id;
                                                        if (!(num_com&0xff) || num_com==p->gDrawObjects.size()) {
                                                            printf("object#=%d index=%d glDeleteTextures() texture#=%d  ",num_p2,p->arr_index,num_p1);
                                                            printf("glDeleteBuffers() drawobjects#=%d\r",num_pb);
                                                        }
                                                        num_pb++;
                                                        num_p1b++;
                                                    }
                                                    glDeleteBuffers((GLsizei)p->gDrawObjects.size(), gluint_arr);
                                                }

                                                printf("object#=%d index=%d glDeleteTextures() texture#=%d  ",num_p2,p->arr_index,num_p1);
                                                printf("glDeleteBuffers() drawobjects#=%d   \n",num_p1b);
                                                p->map_x=-1;
                                                p->map_y=-1;
                                                num_p2++;

                                                pac_obj2_arr[p->arr_index].gDrawObjects.clear();
                                                pac_obj2_arr[p->arr_index].materials.clear();
                                                pac_obj2_arr[p->arr_index].textures.clear();
                                                pac_obj2_arr[p->arr_index].show=0;
                                                p->gDrawObjects.clear();
                                                p->materials.clear();
                                                p->textures.clear();
                                                p->show=0;
                                                pac_obj2_arr_used[p->arr_index]=false;
                                                pac_obj2_arr_size=0;
                                            }
                                            Pacman_Objects[win_num].clear();
                                        }
                                        to_load.clear();
                                        printf("Loading object array data\n");
                                        file_arr = fopen ("OBJECT_ARRAY.TXT", "r");
                                        while (fgets (line,200, file_arr)!=NULL ) {
                                            int num=sscanf(line,"X=%d Y=%d\n", &x, &y);
                                            if (num==2 && line[0]=='X') {
                                                x=-1;y=-1;
                                                cool=1;
                                                for (auto u : Pacman_Objects[win_num]) {
                                                    if (u.map_x==x && u.map_y==y) {
                                                        printf("X=%d Y=%d already loaded.\n",x,y);
                                                        cool=0;
                                                        break;
                                                    }
                                                }
                                                if (cool==1) {
                                                    to_load.push_back(glm::vec2(x,y));
                                                    printf("X=%d Y=%d to load list.\n",x,y);
                                                    load_more=true;
                                                }
                                            }
                                        }
                                        fclose(file_arr);
                                        break;
                                    case sf::Keyboard::L:
                                        printf("Reloading movement data\n");
                                        start_view(marker_file,marker_filename);
                                        break;
                                    case sf::Keyboard::E:
                                        char todo[100];
                                        sprintf(todo,"del %s",marker_filename);
                                        system(todo);
                                        printf("Marker file deleted\n");
                                        first_m=true;
                                        splines_loaded=false;
                                        break;
                                    case sf::Keyboard::P:
                                        if (event.key.control) {
                                            start_view(marker_file,marker_filename);
                                        } else if (event.key.shift) {
                                            if (!interpolate_on) {
                                                interpolate_on=true;
                                                    splines_loaded=false;
//                                                if (!splines_loaded) {
                                                    start_view(marker_file,marker_filename);
//                                                }
    //                                            get_view(curr_quat2,eye2,lookat2,translation,perspective);
                                            } else {
                                                stop_view();
                                            }
                                        } else {
                                            if (!interpolate_on) {
                                               if (!splines_loaded) {
                                                    start_view(marker_file,marker_filename);
                                               } else {
                                                    interpolate_spline(1);
                                                    get_view(rotate_object_z, curr_quat2,eye2,lookat2,translation,perspective,bmin,bmax,frustum_toggle);
                                               }
                                            } else {
                                                if (!splines_loaded) {
                                                    start_view(marker_file,marker_filename);
                                                } else {
                                                    interpolate_spline(1);
                                                    get_view(rotate_object_z, curr_quat2,eye2,lookat2,translation,perspective,bmin,bmax,frustum_toggle);
                                                }
                                            }
    /*
                                            qx=curr_quat2[0]; qy=curr_quat2[1]; qz=curr_quat2[2]; qw=curr_quat2[3];
                                            ex=eye2[0]; ey=eye2[1]; ez=eye2[2];
                                            lx=lookat2[0]; ly=lookat2[1]; lz=lookat2[2];
                                            tx=translation[0]; ty=translation[1]; tz=translation[2];
                                            p0=perspective[0];p1=perspective[1];p2=perspective[2];p3=perspective[3];
                                            char test[1000];
                                            printf("new=QUATS=%-+e %-+e %-+e %-+e EYE=%-+e %-+e %-+e LOOKAT=%-+e %-+e %-+e TRANSLATION=%-+e %-+e %-+e PERSPECTIVE=%-+e %-+e %-+e %-+e\n\n",
                                                      qx,   qy,  qz,  qw,
                                                      ex,   ey,  ez,
                                                      lx,   ly,  lz,
                                                      tx,   ty,  tz,
                                                      p0,   p1,  p2,  p3);
    */
                                        }
                                        break;
                                    case sf::Keyboard::Numpad7:
                                        perspective[0]=perspective[0]-1;
                                        eye2[2] = eye2[2]*(1.0/zoom_factor);
                                        lookat2[2] = lookat[2]*(1.0/zoom_factor);
                                        break;
                                    case sf::Keyboard::Numpad8:
                                        if (perspective[0]<45.0) {
                                            eye2[2] = eye2[2]*pow((zoom_factor),(perspective[0]-45.0));
                                            lookat2[2] = lookat2[2]*pow((zoom_factor),(perspective[0]-45.0));
                                        } else {
                                            eye2[2] = eye2[2]*pow((1.0/zoom_factor),(45.0-perspective[0]));
                                            lookat2[2] = lookat2[2]*pow((1.0/zoom_factor),(45.0-perspective[0]));
                                        }
                                        perspective[0]=45.0;
                                        break;
                                    case sf::Keyboard::Numpad9:
                                        perspective[0]=perspective[0]+1;
                                        eye2[2] = eye2[2]*zoom_factor;
                                        lookat2[2] = lookat[2]*zoom_factor;
                                        break;
                                    case sf::Keyboard::Numpad4:
                                        perspective[2]=perspective[2]*0.9;
                                        break;
                                    case sf::Keyboard::Numpad5:
                                        perspective[2]=0.01;
                                        break;
                                    case sf::Keyboard::Numpad6:
                                        perspective[2]=perspective[2]*(1.0/0.9);
                                        break;
                                    case sf::Keyboard::Numpad1:
                                        perspective[3]=perspective[3]*0.9;
                                        break;
                                    case sf::Keyboard::Numpad2:
                                        perspective[3]=0.01;
                                        break;
                                    case sf::Keyboard::Numpad3:
                                        perspective[3]=perspective[3]*(1.0/0.9);
                                        break;
                                    case sf::Keyboard::F2:
                                        if (event.key.control) {
                                            if (voxels_total.size()+voxels.size() > 0) {
                                                dont_clear=true;
                                                printf("Clearing all voxels from memory: Flushing all voxels to region voxel files (adding to existing)\n");
                                                flush_voxels_to_region_voxel_files();
                                                dont_clear=false;
                                                voxels.clear();
                                                voxels_total.clear();
                                            }
                                            break;
                                        }
                                        flush_voxels_to_region_voxel_files();
                                        if (event.key.shift) {
                                            printf("Plotting ../cut/r.*.*.vox region files\n");
                                            region_voxel_files_to_region_files(true);
                                        } else {
                                            printf("Converting ../cut/r.*.*.vox region files to /saves/test/region/done0/r.*.*.mca minecraft files\n");
                                            region_voxel_files_to_region_files(false);
                                        }
                                        break;
/*
                                        if (fly_on==1) {
                                            event_system = 1;
                                        }
                                        else event_system=0;
                                        break;
*/
                                    case sf::Keyboard::R:
                                        if (event.key.control && event.key.alt) {
                                            window.setActive(false);
                                            window.setVerticalSyncEnabled(true);
                                            break;
                                        }
                                        if (event.key.shift && event.key.alt) {
                                            window.setActive(false);
                                            window.setVerticalSyncEnabled(false);
                                            break;
                                        }
                                        if (event.key.control) {
                                            if (contextSettings.antialiasingLevel>0)  {
                                                contextSettings.antialiasingLevel--;
//                                                window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                                if (videomode[win_num]==0) {
                                                    window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                                }
                                                else {
                                                    window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
                                                }
                                                window.setSize(old_size[win_num]);
                                                window.setPosition(old_pos[win_num]);
                                                window.setVerticalSyncEnabled(true);
                                            }
                                            break;
                                        }
                                        if (event.key.alt) {
                                            contextSettings.antialiasingLevel++;
                                            if (videomode[win_num]==0) {
                                                window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                            }
                                            else {
                                                window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
                                            }
                                            window.setSize(old_size[win_num]);
                                            window.setPosition(old_pos[win_num]);
                                            window.setVerticalSyncEnabled(true);
                                            break;
                                        }


                                        handle_key_window(event, win_num, window);
                                        if (event.key.control) start_view(marker_file,marker_filename);
                                        break;
                                    case sf::Keyboard::F4:
                                        printf("I am here ");
                                        if (event.key.control) printf("CTRL ");
                                        if (event.key.shift) printf("SHFT ");
                                        if (event.key.alt) printf("ALT ");
                                        printf("\n");
                                        if (event.key.control) {
                                            to_load.push_back(glm::vec2(cur_x-1,cur_y));
                                            to_load.push_back(glm::vec2(cur_x+1,cur_y));
                                            to_load.push_back(glm::vec2(cur_x,cur_y-1));
                                            to_load.push_back(glm::vec2(cur_x,cur_y+1));
                                            to_load.push_back(glm::vec2(cur_x-1,cur_y-1));
                                            to_load.push_back(glm::vec2(cur_x+1,cur_y-1));
                                            to_load.push_back(glm::vec2(cur_x-1,cur_y+1));
                                            to_load.push_back(glm::vec2(cur_x+1,cur_y+1));
                                            load_more=true;
                                            break;
                                        }
                                        if (event.key.shift) {
                                            if (load_more_remember || load_more) {
                                                printf("Skipping...\n");
                                                break;
                                            }
                                            pull_off2=true;
                                            printf("pull_off2=true\n");
                                            break;
                                        }
                                        lat_lon=get_lat_lon(my_area);
                                        if (lat_lon.x!=999) {
                                            int cool=1;
                                            for (auto u : Pacman_Objects[win_num]) {
                                                if (u.map_x==lat_lon.x && u.map_y==lat_lon.y) {
                                                    cool=0;
                                                    break;
                                                }
                                            }
                                            if (cool==1) {
                                                no_new_window=true;
                                                exit_code=-20;
                                                exit_thread = true;
                                            }
                                            break;
                                        }
                                        break;
                                    case sf::Keyboard::Delete:
                                        voxels.clear();
                                        voxels_total.clear();
                                        break;
                                    case sf::Keyboard::F1:
                                        if (event.key.control && event.key.shift) {
                                            exporter2=exporter;
                                            make_schematic=true;
                                            burn=true;
                                            obj_dir=MODELS;
                                            int timenow= time(0);
                                            char fn[200];
                                            sprintf(fn,"total-%d",timenow);
                                            make_schematic_nbt(std::string() + fn,voxels_total,0,voxels_total.size());
                                            burn=false;
                                            make_schematic=false;
                                        } else if (event.key.alt) {
                                            plotting=3;
                                            strcpy(mc_text2,"");
                                            hold_voxels=true;
                                            scan_image.create(512,512,sf::Color(0,0,0,0));
                                            for (int z=10; z>=0; z--) {
                                                for (int x=10; x>=0; x--) {
                                                    scan_x=x;
                                                    scan_z=z;
                                                    sprintf(mc_text1,"R.%d.%d.MCA",x,z);
                                                    update_request=2;
                                                    while (update_request) {
                                                        sf::sleep(sf::seconds(0.005));
                                                    }
                                                }
                                            }
                                            hold_voxels=false;
                                            plotting=0;
                                        }
                                        else if (event.key.control) {
                                            rot_on=false;
                                            flush_voxels();
                                        }
                                        else if (event.key.shift) {
                                            exporter2=exporter;
                                            make_schematic=true;
//                                            make_test_schematic();
                                            burn=true;
                                            if (follow_ghost) {
                                                mazemovex_voxel=(-pos_ghostx[follow_ghost_num]+1920+maxpixelsx)%maxpixelsx;
                                                mazemovey_voxel=(-pos_ghosty[follow_ghost_num]+1080+maxpixelsy)%maxpixelsy;
//                                                mazemovex_voxel=(-pos_ghostx[follow_ghost_num]+1920+maxpixelsx)%maxpixelsx;
//                                                mazemovey_voxel=(-pos_ghosty[follow_ghost_num]+1080+maxpixelsy)%maxpixelsy;
                                            } else {
                                                mazemovex_voxel=smooth_x;
                                                mazemovey_voxel=smooth_y;
//                                                mazemovex_voxel=smooth_x;
//                                                mazemovey_voxel=smooth_y;
                                            }
                                            voxelize(Pacman_Objects[win_num]);
                                            mazemovex_voxel=0;
                                            mazemovey_voxel=0;
                                            burn=false;
                                            make_schematic=false;
                                        }
                                        else {
                                            if (rot_on) {
                                                rotate_object_x=rotate_object_x_to_add;
                                                rotate_object_y=rotate_object_y_to_add;
                                                rotate_object_z=rotate_object_z_to_add;
                                                hoppa_de_poppa=true;
                                                break;
                                            }

                                            exporter2=exporter;
                                            burn=true;

                                            if (follow_ghost) {
                                                mazemovex_voxel=(-pos_ghostx[follow_ghost_num]+1920+maxpixelsx)%maxpixelsx;
                                                mazemovey_voxel=(-pos_ghosty[follow_ghost_num]+1080+maxpixelsy)%maxpixelsy;
//                                                mazemovex_voxel=(-pos_ghostx[follow_ghost_num]+1920+maxpixelsx)%maxpixelsx;
//                                                mazemovey_voxel=(-pos_ghosty[follow_ghost_num]+1080+maxpixelsy)%maxpixelsy;
                                            } else {
//                                                mazemovex_voxel=smooth_x;
//                                                mazemovey_voxel=smooth_y;
                                                mazemovex_voxel=smooth_x;
                                                mazemovey_voxel=smooth_y;
                                            }

                                            voxelize(Pacman_Objects[win_num]);
                                            if (plot_only) {
                                                voxels.clear();
                                                voxels_total.clear();
                                            }
                                            mazemovex_voxel=0;
                                            mazemovey_voxel=0;
                                            burn=false;
                                        }

//                                        different_draw=1;
//                                        plot_only=true;
//                                        do_wuppie=1;
                                        break;
                                    case sf::Keyboard::F12:
                                        if (event.key.control) {
                                            if (winsize==false) {
                                                old_size2=window.getSize();
                                                old_pos2 =window.getPosition();
//                                                window.create(sf::VideoMode(1920*2,1080*2), window_title, sf::Style::Fullscreen, contextSettings);
                                                window.create(sf::VideoMode(1920*2,1080*2), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);

                                                window.setSize(sf::Vector2u(1920*2,1080*2));
                                                window.setPosition(sf::Vector2i(0,0));
//                                                window.setSize(sf::Vector2u(1920*2,1080*2));
//                                                window.setPosition(sf::Vector2i(-1920/2,-1080/2));
                                                old_size[win_num]=window.getSize();
                                                old_pos[win_num]= window.getPosition();
                                            } else {
                                                window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                                window.setSize(old_size2);
                                                window.setPosition(old_pos2);
                                                old_size[win_num]=window.getSize();
                                                old_pos[win_num]=window.getPosition();
                                            }
                                            window.setVerticalSyncEnabled(true);
                                            winsize=!winsize;
                                            break;
                                        }
                                        if ((isvisible==false || window.getSize()==sf::Vector2u(0,0))) {
                                                window.setVisible(true);
                                                window.setSize(old_size2);
                                                window.setPosition(old_pos2);
                                                isvisible=true;
                                                visible[win_num]=1;

                                                old_size[win_num]=window.getSize();
                                                old_pos[win_num]= window.getPosition();
                                                break;
                                        }
                                        else if (isvisible==true) {
                                            old_size2=window.getSize();
                                            old_pos2 =window.getPosition();
                                            isvisible=false;
                                            visible[win_num]=0;
                                            old_size[win_num]=window.getSize();
                                            old_pos[win_num]= window.getPosition();
                                            window.setVisible(false);
                                            break;
                                        }
                                        break;
                                    case sf::Keyboard::W:
                                        WIRE_FRAME=!WIRE_FRAME;
                                        depth_shader.setUniform("WIRE_FRAME", WIRE_FRAME);
                                        break;
                                    case sf::Keyboard::T:
                                        TEXTURE_ARRAY=!TEXTURE_ARRAY;
                                        depth_shader.setUniform("TEXTURE_ARRAY", TEXTURE_ARRAY);
                                        break;
                                    case sf::Keyboard::C:
                                        if (event.key.shift) {
                                            cubic=!cubic;
                                            break;
                                        } else {
                                            COLOR_ARRAY=!COLOR_ARRAY;
                                            depth_shader.setUniform("COLOR_ARRAY", COLOR_ARRAY);
                                            break;
                                        }
                                        break;
                                    case sf::Keyboard::F6:
                                        if (event.key.shift) {
                                            rotate_object_x=roundf(rotate_object_x/5.0)*5.0;
                                            rotate_object_y=roundf(rotate_object_y/5.0)*5.0;
                                            rotate_object_z=roundf(rotate_object_z/5.0)*5.0;
                                        } else if (event.key.alt) {
                                            rotate_object_x=0.0;
                                            break;
                                        }
                                        perspective[0]=45.0;
                                        perspective[1]=(float)window.getSize().x / (float)window.getSize().y;
                                        perspective[2]=0.01;
                                        perspective[3]=100.0f;
                                        break;
                                    case sf::Keyboard::F7:
                                        if (event.key.shift) {
                                            rotate_object_x=roundf(rotate_object_x/10.0)*10.0;
                                            rotate_object_y=roundf(rotate_object_y/10.0)*10.0;
                                            rotate_object_z=roundf(rotate_object_z/10.0)*10.0;
                                        } else if (event.key.alt) {
                                            rotate_object_y=0.0;
                                            break;
                                        }
//                                        curr_quat2[0]=0;curr_quat2[1]=0;curr_quat2[2]=0;curr_quat2[3]=1;
                                        eye2[0] = 0.0f;     eye2[1] = 0.0f;
                                        if (frustum_toggle==1) eye2[2] = 3.0f; else eye2[2] = 3.0f;
                                        lookat2[0] = 0.0f;  lookat2[1] = 0.0f;  lookat2[2] = 0.0f;
                                        up2[0] = 0.0f;      up2[1] = 1.0f;      up2[2] = 0.0f;
                                        trackball(curr_quat2, 0, 0, 0, 0);
                                        break;
                                    case sf::Keyboard::F8:
                                        if (event.key.shift) {
                                            rotate_object_x=roundf(rotate_object_x/90)*90.0;
                                            rotate_object_y=roundf(rotate_object_y/90)*90.0;
                                            rotate_object_z=roundf(rotate_object_z/90)*90.0;
                                        } else if (event.key.alt) {
                                            rotate_object_z=0.0;
                                            break;
                                        }
                                        rotate_object_x=0; rotate_object_y=0; rotate_object_z=0;
                                        rotate_object_x_cum=0; rotate_object_y_cum=0; rotate_object_z_cum=0;
                                        move_object_x=0; move_object_y=0; move_object_z=0;
//                                        trackball(curr_quat1, 0, 0, 0, 0);
                                        break;
                                    case sf::Keyboard::F5:
                                        if (event.key.shift) {
                                            rotate_object_x=roundf(rotate_object_x);
                                            rotate_object_y=roundf(rotate_object_y);
                                            rotate_object_z=roundf(rotate_object_z);
                                        } else if (event.key.control) {
                                            show_text_short=!show_text_short;
                                            break;
                                        }
                                        show_text=!show_text;
                                        break;
                                    case sf::Keyboard::Tab:
                                        whattodo++;
                                        if (whattodo>3) whattodo=0;
                                        break;
                                    case sf::Keyboard::F10:
                                        if (event.key.control) {
                                            rotate_object_x=0.0;
                                            rotate_object_y=0.0;
                                            rotate_object_z=0.0;
                                            break;
                                        } else if (event.key.alt) {
                                            rot_plot=!rot_plot;
                                            if (rot_plot && !rot_on) exporter2=exporter;
                                            break;
                                        }
                                        rot_plot=false;
                                        rot_on=!rot_on;
                                        if (rot_on) {
                                            exporter2=exporter;
                                            fps_base=fpstime;

                                            if (follow_ghost) {
                                                speed_base=sqrt(fspeed_ghostx[follow_ghost_num]*fspeed_ghostx[follow_ghost_num]+fspeed_ghosty[follow_ghost_num]*fspeed_ghosty[follow_ghost_num]);
                                                angle_base=atan2(fspeed_ghosty[follow_ghost_num], fspeed_ghostx[follow_ghost_num]);
                                                smooth_x_old=smooth_x;
                                                smooth_y_old=smooth_y;
                                           }
                                            else {
                                                speed_base=sqrt(fspeedx*fspeedx+fspeedy*fspeedy);
                                                angle_base=atan2(fspeedy, fspeedx);
                                            }
                                            rotate_object_x_base=rotate_object_x;
                                            rotate_object_y_base=rotate_object_y;
                                            rotate_object_z_base=rotate_object_z;
                                            rotate_object_x_to_add=rotate_object_x;
                                            rotate_object_y_to_add=rotate_object_y;
                                            rotate_object_z_to_add=rotate_object_z;
                                        } else {
                                            voxel_bottom=0.0;
                                        }

//                                        if (rot_on) clock.restart();

                                        break;
                                    case sf::Keyboard::F9:
                                        if (event.key.control) {
                                            angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                        }
                                        else // to angles
                                        {
                                            quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            break;
                                        }
/*
                                        if (event.key.control) {
                                            fly_visible=!fly_visible;
                                            break;
                                        } else if (event.key.shift) {
                                            printf("Recovering airplane\n");
                                            recover_crash = true;
                                            break;
                                        } else {
                                            fly_on=!fly_on;
                                            if (fly_on) {
                                                wprintf(L"\x1b[2J");
                                                delta2_mutex.lock();
                                                fly_view_start=*fly_view_pointer;
                                                fly_plane_position_start=fly_plane_position;
                                                delta2_mutex.unlock();
                                            }
                                            break;
                                        }
*/
                                        break;
                                    case sf::Keyboard::Left:
                                        if (remember_911_2) {
                                            if (frustum_count_x>0) {
                                                frustum_count_x--;
                                                get_one_3d_update_load_obj_data();
                                            }
                                            break;
                                        }
                                        if (plot_func) {
                                            if (event.key.control) {
                                                if (frustum_count_x>0) {
                                                    frustum_count_x--;
                                                    get_one_3d_update_load_obj_data();
                                                }
                                            } else if (selector_pos.x>0) {
                                                selector_pos.x--;
                                            }
//                                            printf("Selector X=%d,Y=%d\n",selector_pos.x,selector_pos.y);
                                            break;
                                        }
                                        if (event.key.shift) { trans*=5.0; rot*=5.0; }
                                        if (event.key.alt && event.key.control) { exit_code=-10;  exit_thread = true;  break; }
                                        if (event.key.alt) {
                                            rotate_object_y=rotate_object_y-1.0*rot;
                                            rotate_object_y_cum=rotate_object_y_cum-1.0*rot;
                                            break;
                                        }
                                        if (event.key.control) {
                                            angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            trackball(prev_quat2,
                                                  rot * (2.0f *  5.0) / 1000.0,
                                                  0,
                                                  rot * (2.0f * -5.0) / 1000.0,
                                                  0);
                                            add_quats(prev_quat2, curr_quat2, curr_quat2);
                                            quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            break;
                                        }
                                        if (rot_on || 1) {
                                            move_object_x=move_object_x+1.0*trans*cos(rotate_object_z*M_PI/180.0);
                                            move_object_y=move_object_y-1.0*trans*sin(rotate_object_z*M_PI/180.0);
                                        } else {
                                            move_object_x=move_object_x+5.0*trans;
                                        }
//                                        eye2[0] += trans * (5.0) / 1000.0;
//                                        lookat2[0] += trans * (5.0) / 1000.0;
                                        break;
                                    case sf::Keyboard::Right:
                                        if (remember_911_2) {
                                            if (frustum_count_x<frustum_size_x) {
                                                frustum_count_x++;
                                                get_one_3d_update_load_obj_data();
                                            }
                                            break;
                                        }
                                        if (plot_func) {
                                            if (event.key.control) {
                                                if (frustum_count_x<frustum_size_x-1) {
                                                    frustum_count_x++;
                                                    get_one_3d_update_load_obj_data();
                                                }
                                            } else {
                                                if (area=="Models" || selector_pos.x<max_x-1) selector_pos.x++;
//                                                printf("Selector X=%d,Y=%d\n",selector_pos.x,selector_pos.y);
                                            }
                                            break;
                                        }
                                        if (event.key.shift) { trans*=5.0; rot*=5.0; }
                                        if (event.key.alt && event.key.control) { exit_code=-11;  exit_thread = true;  break; }
                                        if (event.key.alt) {
                                            rotate_object_y=rotate_object_y+1.0*rot;
                                            rotate_object_y_cum=rotate_object_y_cum+1.0*rot;
                                            break;
                                        }
                                        if (event.key.control) {
                                            angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            trackball(prev_quat2,
                                                      rot * (2.0f * -5.0) / 1000.0,
                                                      0,
                                                      rot * (2.0f * +5.0) / 1000.0,
                                                      0);
                                                add_quats(prev_quat2, curr_quat2, curr_quat2);
                                            quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            break;
                                        }
                                        if (rot_on || 1) {
                                            move_object_x=move_object_x-1.0*trans*cos(rotate_object_z*M_PI/180.0);
                                            move_object_y=move_object_y+1.0*trans*sin(rotate_object_z*M_PI/180.0);
                                        } else {
                                            move_object_x=move_object_x-5.0*trans;
                                        }
                                        break;
                                    case sf::Keyboard::Up:
                                        if (remember_911_2) {
                                            if (frustum_count_y>0) {
                                                frustum_count_y--;
                                                get_one_3d_update_load_obj_data();
                                            }
                                            break;
                                        }
                                        if (plot_func) {
                                            if (event.key.control) {
                                                if (frustum_count_y>0) {
                                                    frustum_count_y--;
                                                    get_one_3d_update_load_obj_data();
                                                }
                                            } else {
                                                if (selector_pos.y>0) selector_pos.y--;
                                            }
//                                            printf("Selector X=%d,Y=%d\n",selector_pos.x,selector_pos.y);
                                            break;
                                        }
                                        if (event.key.shift) { trans*=5.0; rot*=5.0; }
                                        if (event.key.alt && event.key.control) { exit_code=-13;  exit_thread = true;  break; }
                                        if (event.key.alt) {
                                            rotate_object_x=rotate_object_x-1.0*rot;
                                            rotate_object_x_cum=rotate_object_x_cum-1.0*rot;
                                            break;
                                        }
                                        if (event.key.control) {
                                            angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            trackball(prev_quat2,
                                                      0,
                                                      rot * (2.0f * -5.0) / (float)1000,
                                                      0,
                                                      rot * (2.0f *  5.0) / (float)1000);
                                                add_quats(prev_quat2, curr_quat2, curr_quat2);
                                            quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            break;
                                        }
                                        if (rot_on || 1) {
                                            move_object_y=move_object_y-1.0*trans*cos(rotate_object_z*M_PI/180.0);
                                            move_object_x=move_object_x-1.0*trans*sin(rotate_object_z*M_PI/180.0);
                                        } else {
                                            move_object_y=move_object_y-5.0*trans;
                                        }
                                        break;
                                    case sf::Keyboard::Down:
                                        if (remember_911_2) {
                                            if (frustum_count_y<frustum_size_y) {
                                                frustum_count_y++;
                                                get_one_3d_update_load_obj_data();
                                            }
                                            break;
                                        }
                                        if (plot_func) {
                                            if (event.key.control) {
                                                if (frustum_count_y<frustum_size_y-1) {
                                                    frustum_count_y++;
                                                    get_one_3d_update_load_obj_data();
                                                }
                                            } else {
                                                if (area=="Models" || selector_pos.y<max_y-1)selector_pos.y++;
//                                                printf("Selector X=%d,Y=%d\n",selector_pos.x,selector_pos.y);
                                            }
                                            break;
                                        }
                                        if (event.key.shift) { trans*=5.0; rot*=5.0; }
                                        if (event.key.alt && event.key.control) { exit_code=-12;  exit_thread = true;  break; }
                                        if (event.key.alt) {
                                            rotate_object_x=rotate_object_x+1.0*rot;
                                            rotate_object_x_cum=rotate_object_x_cum+1.0*rot;
                                            break;
                                        }
                                        if (event.key.control) {
                                            angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            trackball(prev_quat2,
                                                      0,
                                                      rot * (2.0f *  5.0) / 1000.0,
                                                      0,
                                                      rot * (2.0f * -5.0) / 1000.0);
                                                add_quats(prev_quat2, curr_quat2, curr_quat2);
                                            quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            break;
                                        }
                                        if (rot_on || 1) {
                                            move_object_y=move_object_y+1.0*trans*cos(rotate_object_z*M_PI/180.0);
                                            move_object_x=move_object_x+1.0*trans*sin(rotate_object_z*M_PI/180.0);
                                        } else {
                                            move_object_y=move_object_y+5.0*trans;
                                        }
                                        break;
                                    case sf::Keyboard::Add:
                                        voxel_bottom=voxel_bottom+1.0;
                                        break;
                                    case sf::Keyboard::Subtract:
                                        voxel_bottom=voxel_bottom-1.0;
                                        if (voxel_bottom<0.0) voxel_bottom=0.0;
                                        break;
                                    case sf::Keyboard::PageUp:
                                        if (event.key.shift) { trans*=5.0; rot*=5.0; }
                                        if (event.key.alt) {
                                            rotate_object_z=rotate_object_z-1.0*rot;
                                            rotate_object_z_cum=rotate_object_z_cum-1.0*rot;
                                            break;
                                        }
                                        if (event.key.control) {
                                            angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            trackballz(prev_quat2,
                                                       0,
                                                      rot * (2.0f *  5.0) / 1000.0,
                                                       0,
                                                      rot * (2.0f * -5.0) / 1000.0);
                                            add_quats(prev_quat2, curr_quat2, curr_quat2);
                                            quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);

                                            break;
                                        }
                                        move_object_z=move_object_z+5.0*trans;
//                                        eye2[2] -= trans * (5.0) / 1000.0;
//                                        lookat2[2] -= trans * (5.0) / 1000.0;
                                        break;
                                    case sf::Keyboard::PageDown:
                                        if (event.key.shift) { trans*=5.0; rot*=5.0; }
                                        if (event.key.alt) {
                                            rotate_object_z=rotate_object_z+1.0*rot;
                                            rotate_object_z_cum=rotate_object_z_cum+1.0*rot;
                                            break;
                                        }
                                        if (event.key.control) {
                                            angles_to_quat(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            trackballz(prev_quat2,
                                                        0,
                                                        rot * (2.0f * -5.0) / 1000.0,
                                                        0,
                                                        rot * (2.0f *  5.0) / 1000.0);
                                            add_quats(prev_quat2, curr_quat2, curr_quat2);
                                            quat_to_angles(curr_quat2, prev_quat2, rotate_object_x, rotate_object_y, rotate_object_z);
                                            break;
                                        }
                                        move_object_z=move_object_z-5.0*trans;
//                                        eye2[2] += trans * (5.0) / 1000.0;
//                                        lookat2[2] += trans * (5.0) / 1000.0;
                                        break;
                                    case sf::Keyboard::Q:
                                        if (event.key.control) { exit_code=-1;   exit_thread = true; keep_running[win_num]=0; break; }
                                }
                            }
                            if ((event.key.system && exit_code<=-10) || exit_code==-20) {
                                no_new_window=true;
                            }
                            else if (exit_code<=-10 || load_more || load_extra || switch_to_full_screen) {
                                int x_now=cur_x,y_now=cur_y;
                                if (!load_more && !load_extra) {
                                    if (exit_code==-10) { cur_x--; if (cur_x<0) cur_x=0; }
                                    else if (exit_code==-11) { cur_x++; if (cur_x>=max_x) cur_x=max_x-1; }
                                    else if (exit_code==-12) { cur_y--; if (cur_y<0) cur_y=0; }
                                    else if (exit_code==-13) { cur_y++; if (cur_y>=max_y) cur_y=max_y-1; }
                                }
                                if (x_now!=cur_x || y_now!=cur_y || load_more || load_extra) {
                                    if (load_more && to_load.size()>0) {
                                        std::vector<glm::ivec2>::iterator it=to_load.begin();
                                        glm::ivec2 v=*it;
                                        cur_x=v.x;
                                        cur_y=v.y;
                                        to_load.erase(it);
//help
                                        if (to_load.size()==0) {
                                            load_more_remember=true;
                                            load_more_counter=60;
                                            load_more=false;
                                        }
//                                        printf("X=%d Y=%d loading.\n",v.x,v.y);
                                    } //else load_more=false;
                                    if (load_more==true) { //pipo de clown
                                        load_more_remember=true;
                                        load_more_counter=60;
                                        load_more=false;
                                    } else {
                                        load_more_remember=false;
                                    }
                                    int cool=1;
                                    for (auto u : Pacman_Objects[win_num]) {
                                        if (u.map_x==cur_x && u.map_y==cur_y) {
                                            cool=0;
                                            break;
                                        }
                                    }
                                    if (cool==0 && !add_on) {
                                        if (yo_combine==1)
                                            printf("Already loaded: %d,%d: %s\n",cur_x,cur_y,get_area_data(my_area,cur_x,cur_y).c_str());
                                        else
                                            printf("Already loaded: %d,%d: %s\n",cur_x,cur_y,get_octant_ENSCHEDE(cur_x,cur_y).c_str());

                                    } else {
                                        printf("X=%d Y=%d loading.\n",cur_x,cur_y);
                                        std::string str;
                                        on_hold=false;
                                        if (yo_combine==1)
                                            str=get_area_data(my_area,cur_x,cur_y);
    //                                        str=get_octant_Amsterdam(cur_x,cur_y);
                                        else
                                            str=get_octant_ENSCHEDE(cur_x,cur_y);
                                        if (load_extra && to_load_extra.size()>0) {
                                            std::vector<glm::ivec2> swapit;
                                            int cool;
                                            for (auto u : to_load_extra) {
                                                cool=1;
                                                for (auto p : Pacman_Objects[win_num]) {
                                                    if (p.map_x==u.x && p.map_y==u.y) {
                                                        cool=0;
                                                        break;
                                                    }
                                                }
                                                if (cool==1) {
                                                    swapit.push_back(glm::ivec2(u.x,u.y));
                                                }
                                            }
                                            to_load_extra.clear(); load_extra=false;
                                            if (swapit.size()>0) {
                                                for (auto u : swapit) {
                                                    to_load_extra.push_back(glm::ivec2(u.x,u.y));
                                                }
                                                load_extra=true;
                                            }

                                            if (load_extra && to_load_extra.size()>0) {
                                                int back=cur_x;
                                                cur_x=to_load_extra[to_load_extra.size()-1].x;
                                                to_load_extra[to_load_extra.size()-1].x=back;
                                                back=cur_y;
                                                cur_y=to_load_extra[to_load_extra.size()-1].y;
                                                to_load_extra[to_load_extra.size()-1].y=back;
                                                if (yo_combine==1)
                                                    str=get_area_data(my_area,cur_x,cur_y);
                                                else
                                                    str=get_octant_ENSCHEDE(cur_x,cur_y);

                                                for (auto u : to_load_extra) {
                                                    int cool=1;
                                                    for (auto p : Pacman_Objects[win_num]) {
                                                        if (p.map_x==u.x && p.map_y==u.y) {
                                                            cool=0;
                                                            break;
                                                        }
                                                        if (p.map_x==cur_x && p.map_y==cur_y) {
                                                            cool=0;
                                                            break;
                                                        }
                                                    }
                                                    if (cool==1) {
                                                        for (auto p : to_load) {
                                                            if (p.x==u.x && p.y==u.y) {
                                                                cool=0;
                                                                break;
                                                            }
                                                        }
                                                        if (cool==1) {
                                                            to_load.push_back(glm::vec2(u.x,u.y));
                                                            load_more=true;
                                                        }
                                                    }
                                                }
                                                load_extra=false;
                                                to_load_extra.clear();
                                            }
                                        }
                                        printf("Trying: %d,%d -> %s\n",cur_x,cur_y,str.c_str());
//huh?
//                                        int found=str.find_last_of("/\\");
//                                        if (my_area==std::string()+"Models" || test_for_pngfiles(str.substr(0,found))==true) {
                                        if (cur_x==-99999 || my_area==std::string()+"Models" || test_for_pngfiles(str)==true) {
                                            render_locker.lock();
                                            ready_to_render[win_num]=0;
                                            render_locker.unlock();

                                            window.setActive(true);

                                            int i;
                                            for (i=0; i<100; i++) {
                                                if (pac_obj2_arr_used[i]==false) {
                                                    printf("Free loc. %d ",i);
                                                    break;
                                                }
                                            }
                                            if (i==100) { printf("\nError, i>100, adapt pac_obj2_arr size > 100"); break; }

                                            char line[2000];
                                            strcpy(line,latitude_longditude.c_str());
                                            while (replace_str(line,".",","));
                                            double lat_north=0.0;
                                            double lat_south=0.0;
                                            double lon_west=0.0;
                                            double lon_east=0.0;
                                            int num=sscanf(line,"N=%lf S=%lf W=%lf E=%lf", &lat_north, &lat_south, &lon_west, &lon_east);
                                            if (num==4) {
                                                char lat_str[100];
                                                char lon_str[100];
                                                sprintf(lat_str,"%lf",(lat_north+lat_south)/2.0); while (replace_str(lat_str,",","."));
                                                sprintf(lon_str,"%lf",(lon_east+lon_west)/2.0); while (replace_str(lon_str,",","."));
                                                if (!burn) {
                                                    printf("https://www.google.com/maps/@%s,%s,17.00z\n",lat_str,lon_str);
                                                }
                                            }

                                            pac_obj2_arr[i].bmin[0] = pac_obj2_arr[i].bmin[1] = pac_obj2_arr[i].bmin[2] = std::numeric_limits<float>::max();
                                            pac_obj2_arr[i].bmax[0] = pac_obj2_arr[i].bmax[1] = pac_obj2_arr[i].bmax[2] = -std::numeric_limits<float>::max();
                                            pac_obj2_arr[i].gDrawObjects.clear();
                                            pac_obj2_arr[i].materials.clear();
                                            pac_obj2_arr[i].textures.clear();
                                            pac_obj2_arr[i].show=0;
                                            pac_obj2_arr[i].filename="";

                                            if (true == LoadObjAndConvert_window(pac_obj2_arr[i].bmin, pac_obj2_arr[i].bmax, pac_obj2_arr[i].gDrawObjects, pac_obj2_arr[i].materials, pac_obj2_arr[i].textures, (char*) str.c_str()))
                                            {
                                                pac_obj2_arr[i].map_x=cur_x;
                                                pac_obj2_arr[i].map_y=cur_y;
                                                pac_obj2_arr[i].arr_index=i;
                                                pac_obj2_arr[i].show=1;
                                                pac_obj2_arr[i].north=lat_north;
                                                pac_obj2_arr[i].south=lat_south;
                                                pac_obj2_arr[i].east=lon_east;
                                                pac_obj2_arr[i].west=lon_west;
                                                pac_obj2_arr[i].filename=str.c_str();
                                                pac_obj2_arr_used[i]=true;

                                                Pacman_Objects[win_num].push_back(pac_obj2_arr[i]);
                                                pac_obj2_arr_size=i;
                                                btot[0]=1.0;
                                                btot[1]=btot[2]=0.0;
                                                lat_min=std::numeric_limits<double>::max();
                                                lat_max=-std::numeric_limits<double>::max();
                                                lon_min=std::numeric_limits<double>::max();
                                                lon_max=-std::numeric_limits<double>::max();
                                                bmin[0] = bmin[1] = bmin[2] = std::numeric_limits<float>::max();
                                                bmax[0] = bmax[1] = bmax[2] = -std::numeric_limits<float>::max();

                                                for (auto u : Pacman_Objects[win_num]) {
                                                    bool fix_lat=false;
                                                    bool fix_lon=false;
                                                    if (u.north>lat_max) { lat_max=u.north; fix_lat=true; }
                                                    if (u.south<lat_min) { lat_min=u.south; fix_lat=true; }
                                                    if (u.west<lon_min)  { lon_min=u.west;  fix_lon=true; }
                                                    if (u.east>lon_max)  { lon_max=u.east;  fix_lon=true; }
                                                    if (fix_lat) btot[2]+=(u.bmax[2]-u.bmin[2]);
                                                    if (fix_lon) btot[1]+=(u.bmax[1]-u.bmin[1]);

                                                    if (btot[0]<u.bmax[0]-u.bmin[0]) btot[0]=u.bmax[0]-u.bmin[0];

                                                    if (u.bmin[0]<bmin[0]) bmin[0]=u.bmin[0]; if (u.bmax[0]>bmax[0]) bmax[0]=u.bmax[0];
                                                    if (u.bmin[1]<bmin[1]) bmin[1]=u.bmin[1]; if (u.bmax[1]>bmax[1]) bmax[1]=u.bmax[1];
                                                    if (u.bmin[2]<bmin[2]) bmin[2]=u.bmin[2]; if (u.bmax[2]>bmax[2]) bmax[2]=u.bmax[2];
                                                }
                                                printf("New object loaded: %d,%d: %s\n",cur_x,cur_y,str.c_str());

//                                                loaded=1;round=2;

                                                maxExtent = 0.5f * (bmax[0] - bmin[0]);
                                                if (maxExtent < 0.5f * (bmax[1] - bmin[1])) maxExtent = 0.5f * (bmax[1] - bmin[1]);
                                                if (maxExtent < 0.5f * (bmax[2] - bmin[2])) maxExtent = 0.5f * (bmax[2] - bmin[2]);
//                                                loaded=1; round=3;

                                            } else {
                                                printf("Error loading new object: %d,%d: %s\n",cur_x,cur_y,str.c_str());
                                            }
                                            window.setActive(false);

                                            reset_text(win_num);

                                            render_locker.lock();
                                            ready_to_render[win_num]=1;
                                            render_locker.unlock();

                                        } else {
                                            printf("No .png files\n");
                                        }
                                    }
                                }
                                exit_thread=false;
                                exit_code=0;
                            } else if ((event.key.code == sf::Keyboard::Escape)) {
                                exit_code=0;
                                exit_thread = true;
                            } else if ((event.key.code == sf::Keyboard::F11)) {
//                                static sf::Vector2u old_size2=sf::Vector2u(1920/2,1080/2);
//                                static sf::Vector2i old_pos2=sf::Vector2i(1920/4,1080/4);
                                if (videomode[win_num]==1) {
                                    videomode[win_num]=0;
                                    old_size[win_num]=sf::Vector2u(1920,1080);
                                    old_pos[win_num]=sf::Vector2i(0,0);
                                    old_size2=window.getSize();
                                    old_pos2=window.getPosition();
                                } else {
                                    videomode[win_num]=1;
                                    old_size[win_num]=old_size2;
                                    old_pos[win_num]=old_pos2;
                                }
                                window.clear(sf::Color(255,0,0,255));
                                window.display();
                                window.clear(sf::Color(255,255,255,255));
                                window.display();
                                window.clear(sf::Color(0,0,255,255));
                                window.display();
                                window.clear(sf::Color(255,255,0,255));
                                window.display();
                                contextSettings.minorVersion = 3;
                                contextSettings.majorVersion = 3;
                                if (videomode[win_num]==0) {
                                    window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                                }
                                else {
                                    window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
                                }
                                window.setVerticalSyncEnabled(true);

                                hglrc[win_num] = wglGetCurrentContext();
                                hwnd[win_num] = window.getSystemHandle();
                                hdc[win_num] = GetDC(hwnd[win_num]) ;

                                window.setSize(old_size[win_num]);
                                window.setPosition(old_pos[win_num]);
                                width2 = old_size[win_num].x;
                                height2 = old_size[win_num].y;
                                window.clear(sf::Color(50,20,30,128));
                                window.display();

                                auto win = window.getSystemHandle();
                                auto style = GetWindowLong(win, GWL_STYLE);
                                auto ex_style = GetWindowLong(win, GWL_EXSTYLE);

                                window.setVerticalSyncEnabled(true);
                                window.setActive(true);

                                if (window.getSize().y>0) perspective[1]=(float)window.getSize().x / (float)window.getSize().y;
                                else perspective[1]=1920.0/1080.0;
                            } else if ((event.key.code == sf::Keyboard::Enter)) {
                                if (mipmapEnabled) {
//                                    if (!texture.loadFromFile("resources/texture.jpg")) {
//                                        render_locker.lock();
//                                        ready_to_render[win_num]=0;
//                                        render_locker.unlock();
//                                        exit_code=EXIT_FAILURE;
//                                        exit_thread = true;
//                                    }
                                    mipmapEnabled = false;
                                } else {
//                                    texture.generateMipmap();
                                    mipmapEnabled = true;
                                }
                            } else if (event.key.code == sf::Keyboard::N) {
                                exit_code=-99;
                                exit_thread = true;
                            }
/*
 else if (event.key.code == sf::Keyboard::Space) {
                                old_size[win_num]=window.getSize();
                                old_pos[win_num]=window.getPosition();
                                sRgb = !sRgb;
                                exit_code=-98;
                                exit_thread = true;
    //                            window.close();
                            }
*/
                        } else if (event.type == sf::Event::Resized) {
                            if (record_window==1) {
                                printf("Recording, cannot change size....\n");
                                window.setSize(old_size[win_num]);
                                window.setPosition(old_pos[win_num]);
                            }

                            window.setActive(true);
                            glViewport(0, 0, event.size.width, event.size.height);

//                            glMatrixMode(GL_PROJECTION);
//                            glLoadIdentity();
//                            gluOrtho2D(-window.getSize().x/2, window.getSize().x/2, -window.getSize().y/2, window.getSize().y/2);
//hoppa
//                            gluPerspective(45.0, (float)event.size.width / (float)event.size.height, 0.01f, 100.0f);

//                            perspective[0]=45.0;
                            perspective[1]=(float)window.getSize().x / (float)window.getSize().y;
//                            perspective[2]=0.01;
//                            perspective[3]=100.0f;

//                            gluPerspective(45.0, (float)event.size.width / (float)event.size.height, 0.01f, 100.0f);
//                            gluPerspective(perspective[0],perspective[1],perspective[2],perspective[3]);
//                            glMatrixMode(GL_MODELVIEW);
//                            glLoadIdentity();

                            window.setActive(false);

                            width2 = event.size.width;
                            height2 =event.size.height;
    //                        ding_texture[win_num].create(window.getSize().x,window.getSize().y);
    //                        ding_sprite[win_num].setTexture(ding_texture[win_num],true);

    //                        ding_texture_render[win_num].create(window.getSize().x,window.getSize().y,true);
    //                        ding_sprite_render[win_num].setTexture(ding_texture_render[win_num].getTexture(),true);
        //                    background.setPosition(width2/2,height2/2.0);
//                            if (window.getSize().y>0) perspective[1]=(float)window.getSize().x / (float)window.getSize().y;
//                            else perspective[1]=old_size[win_num].x/old_size[win_num].y; //???
                        }
                    }
                    no_more=10;
                } else {
                }

/*
                if (!event_happened) {
                    double mouse_x;
                    double mouse_y;
                    if (last_left_mouse || (mouse_x_add_left>0.01 || mouse_y_add_left>0.01))
                    {
                        mouse_x=mouse_x_add_left/20;
                        mouse_y=mouse_y_add_left/20;
                        mouse_x_add_left-=mouse_x_add_left/20;
                        mouse_y_add_left-=mouse_y_add_left/20;
                        trackball(prev_quat2,
                                  rotScale * (2.0f * prevMouseX2 - width2) / (float)width2,
                                  rotScale * (height2 - 2.0f * prevMouseY2) / (float)height2,
                                  rotScale * (2.0f * mouse_x - width2) / (float)width2,
                                  rotScale * (height2 - 2.0f * mouse_y) / (float)height2);

                        add_quats(prev_quat2, curr_quat2, curr_quat2);
                    } else last_left_mouse=false;

                    if (last_middle_mouse || (mouse_x_add_middle>0.01 || mouse_y_add_middle>0.01))
                    {
                        mouse_x=mouse_x_add_middle/20;
                        mouse_y=mouse_y_add_middle/20;
                        mouse_x_add_middle-=mouse_x_add_middle/20;
                        mouse_y_add_middle-=mouse_y_add_middle/20;

                        eye2[0] -= transScale * (mouse_x - prevMouseX2) / (float)width2;
                        lookat2[0] -= transScale * (mouse_x - prevMouseX2) / (float)width2;
                        eye2[1] += transScale * (mouse_y - prevMouseY2) / (float)height2;
                        lookat2[1] += transScale * (mouse_y - prevMouseY2) / (float)height2;
                    } else last_middle_mouse=false;
                    if (last_right_mouse || (mouse_x_add_right>0.01 || mouse_y_add_right>0.01))
                    {
                        mouse_x=mouse_x_add_right/20;
                        mouse_y=mouse_y_add_right/20;
                        mouse_x_add_right-=mouse_x_add_right/20;
                        mouse_y_add_right-=mouse_y_add_right/20;

                        eye2[2] += 2*transScale * (mouse_y - prevMouseY2) / (float)height2;
                        lookat2[2] +=2* transScale * (mouse_y - prevMouseY2) / (float)height2;
                    } else last_right_mouse=false;

                    // Update mouse point
                    prevMouseX2 = mouse_x;
                    prevMouseY2 = mouse_y;
                }

*/
