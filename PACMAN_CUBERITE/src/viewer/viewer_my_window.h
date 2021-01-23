            if (no_new_window==false) {
//                contextSettings.minorVersion = 3;
//                contextSettings.majorVersion = 3;
                window.setVerticalSyncEnabled(true);
                if (videomode[win_num]==0) {
//                    window2.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                    window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Fullscreen, contextSettings);
                }
                else {
//                    window2.create(sf::VideoMode(1920,1080), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
                    window.create(sf::VideoMode(1920,1080), window_title, sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close , contextSettings);
                }
//                window.setActive(false);
//                window.setFramerateLimit(60);
                window.setVisible(true);

                window.setSize(old_size[win_num]);
                window.setPosition(old_pos[win_num]);
                width2 = old_size[win_num].x;
                height2 = old_size[win_num].y;

                viewer=window.getView();
                rect = window.getViewport(viewer);
                printf("viewport=%d %d %d %d\n",rect.left, rect.top, rect.width, rect.height);

                //window.setVerticalSyncEnabled(true);
                {
                    static bool first=true;
                    if (first) {
                        texture_shit.create(1,1);
                        texture_shit.clear(sf::Color(1,1,1,1));
                        sprite_shit.setTexture(texture_shit.getTexture(),true);
                        sf::Texture::bind(&texture_test);

                        sf::ContextSettings contextSettings(0,0,2,3,0);

                        contextSettings.depthBits    = 24;
                        contextSettings.stencilBits  = 8;
                        contextSettings.antialiasingLevel = 0;
//                        contextSettings.majorVersion = 3;
//                        contextSettings.minorVersion = 3;
                        contextSettings.sRgbCapable = false;

                        between_texture.create(1920,1080,contextSettings);
                        between_sprite.setTexture(between_texture.getTexture(),true);
                        between_texture.setView(between_texture.getDefaultView());
                        between_texture.setSmooth(true);
                        sf::Texture::bind(&between_texture.getTexture());

//                        texture1_local.create(1920,1080);
//                        sf::Texture::bind(&texture1_local);
//                        sprite1_local.setTexture(texture1_local,true);
//                        render_texture1_local.create(1920,1080, contextSettings);
//                        render_texture1_local.setActive(true);
//                        sf::Texture::bind(&render_texture1_local.getTexture());

                        between_texture.setActive(true);
                        glViewport(0, 0, 1920,1080);
//                        glEnable(GL_TEXTURE_2D);
                        between_texture.setActive(false);
//                        render_texture1_local.setActive(false);
//                        render_texture1_local.pushGLStates();
                        first=false;

//    between_texture.create(1920,1080,true);
//    between_sprite.setTexture(between_texture.getTexture(),true);

                    }
                }

//                hglrc[win_num] = wglGetCurrentContext();
//                hwnd[win_num] = window.getSystemHandle();
//                hdc[win_num] = GetDC(hwnd[win_num]) ;

//                rectangle.setPosition(10.0,10.0);
//                rectangle.setSize(sf::Vector2f(20.0,20.0*window.getSize().y/window.getSize().x));
//                window_handle=window.getSystemHandle();
//                m_context_window=window.m_context;
//                RECT WorkArea;
//                WorkArea.left=0;
//                WorkArea.right=1920;
//                WorkArea.right=1920;
//                WorkArea.top=0;
//                WorkArea.bottom=1080;
                window.clear(sf::Color(50,20,30,128));
                window.display();

//                auto win = window.getSystemHandle();
//                auto style = GetWindowLong(win, GWL_STYLE);
//                auto ex_style = GetWindowLong(win, GWL_EXSTYLE);

                ShowCursor(true);
                rot_on=false;
//                window.setVerticalSyncEnabled(true);
                sync_window[win_num]=1;
                window.setActive(true);

                if (depth_shader_on) sf::Shader::bind(&depth_shader);
                else sf::Shader::bind(NULL);

                if (glew_initor==false) {
                    glewExperimental = true;
                    if (glewInit() != GLEW_OK)
                    {
                        std::cerr << "Failed to initialize GLEW." << std::endl;
                        return -1;
                    }
                    glew_initor=true;
                }
                perspective[0]=45.0;
                if (by_texture) {
                    perspective[1]=1920.0/1080.0;
                } else {
                    if (window.getSize().y>0) perspective[1]=(float)window.getSize().x / (float)window.getSize().y;
                    else perspective[1]=1920.0/1080.0;
                }
                perspective[2]=0.01f;
                perspective[3]=100.0f;

//                main_fly_de_poppa(1,window,0.0);

            } else {
                no_new_window=false;
                window.setActive(false);
                window.setActive(true);
            }
