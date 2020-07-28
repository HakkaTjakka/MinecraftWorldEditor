

//int main_fly_de_poppa(int what, sf::RenderWindow& window5, float mousewheel_delta)

extern int playsound;
extern int playmusic;
extern int soundoff;
// Adopted/adapted from: https://github.com/amhndu/Fly


int main_fly_de_poppa()
{
    static int dw=1;
    static bool sync=true;
//    using namespace fly;
    static char *argv[]={"moi","-w","1920","-H","1080","--plane-box","-f"};
    static int argc=5;
    static bool first=true;

//    if (first) check_fly=true;

    if (first) { Log::get().setLogStream(std::cout); Log::get().setLevel(Debug); std::srand(std::time(nullptr)); }
    static Options opts = processArguments(argc, argv);
    if (first) { if (opts.showHelp) { printHelp(); return EXIT_SUCCESS; } }

    static sf::ContextSettings settings;
//    static sf::RenderWindow window;
    static unsigned int style =  sf::Style::Close | sf::Style::Resize;
    static sf::VideoMode videoMode {opts.windowWidth, opts.windowHeight};

    if (first) {
        settings.depthBits    = 24;        settings.stencilBits  = 8;       settings.antialiasingLevel = 0;
        settings.majorVersion = 3;         settings.minorVersion = 3;       settings.attributeFlags = sf::ContextSettings::Core;

        sf::VideoMode videoMode {1920.0, 1080.0};
        if (opts.fullscreen) {
            style = sf::Style::Fullscreen;
            videoMode = sf::VideoMode::getDesktopMode();
        }

    }

    static sf::RenderWindow window(videoMode, "OpenGL sandbox", style, settings);

    if (first) {

//        window.create(videoMode, "OpenGL sandbox", style, settings);
        LOG(Info) << "OpenGL context: " << window.getSettings().majorVersion << '.' << window.getSettings().minorVersion << std::endl;
        if (window.getSettings().majorVersion < 3 && window.getSettings().minorVersion < 2) { LOG(Error) << "Incapable OpenGL context" << std::endl; }

        if (opts.fullscreen) window.setMouseCursorVisible(false);
        window.setVerticalSyncEnabled(true);

        if (glew_initor==false) {
            glewExperimental = true;
            if (glewInit() != GLEW_OK) { std::cerr << "Failed to initialize GLEW." << std::endl; return -1; }
            glew_initor=true;
        }
    }

    if (first) fly_is_visible=true;
    if (first) fly_visible=false;

    if (first)  {
        glGetError();
        TextureManager::uploadFile("terrain_lookup", ".png");
        TextureManager::uploadFile("TropicalSunnyDay/TropicalSunnyDay", ".png", TextureManager::TextureCube);
        TextureManager::uploadFile("flare", ".png");
    }
    static glm::mat4 projection_matrix = glm::perspective(external_perspective[0], 1.f * window.getSize().x / window.getSize().y ,external_perspective[2],external_perspective[3]);
//    static glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 1.f * window.getSize().x / window.getSize().y, 0.05f, 50.0f);
    static Terrain terrain(15, 15);
    static Airplane aircraft;
    static ShadowMap shadowMap(aircraft);
    static Sky sky;
    static ParticleSystem particles;

    static auto& terrainRenderer  = terrain.getRenderer();
    static auto& aircraftRenderer = aircraft.getRenderer();

    if (first)  {
        terrain.generate(opts.manualSeed ? opts.seed : std::rand() % 1000 + 1.f * std::rand() / RAND_MAX);
        particles.getRenderer().setProjection(projection_matrix);
        aircraftRenderer.       setProjection(projection_matrix);
        terrainRenderer.        setProjection(projection_matrix);
        sky.                    setProjection(projection_matrix);
        aircraftRenderer.setLightDirection({-0.3f, 0.3f, 0.9f});
        terrainRenderer.setLightDirection({-0.3, 0.3, 0.9});
        shadowMap.setLightDirection({-0.3f, 0.3f, 0.9f});
    }

    static Camera camera(aircraft.getPosition(), aircraft.getForwardDirection(), aircraft.getUpDirection(), aircraft);
    static CameraController mouse_camera(window, camera);

    static std::unique_ptr<Box> box;
    if (first)  {
        if (opts.planeBox) {
            box.reset(new Box());
            box->setProjection(projection_matrix);
        }
    }

    static Controller controller(window);
    if (first)  {
        controller.setCallback(Controller::RollLeft,     std::bind(&Airplane::roll,    &aircraft, -1));
        controller.setCallback(Controller::RollRight,    std::bind(&Airplane::roll,    &aircraft, +1));
        controller.setCallback(Controller::ElevatorUp,   std::bind(&Airplane::elevate, &aircraft, -1));
        controller.setCallback(Controller::ElevatorDown, std::bind(&Airplane::elevate, &aircraft, +1));
        controller.setCallback(Controller::ThrustUp,     std::bind(&Airplane::throttle,&aircraft, +1));
        controller.setCallback(Controller::ThrustDown,   std::bind(&Airplane::throttle,&aircraft, -1));
        controller.registerRotate([&](float x, float y){ camera.rotate(x, y); });
    }

    if (first==1) {
        glEnable(GL_DEPTH_TEST);        glEnable(GL_CULL_FACE);        if (opts.wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);        glEnable(GL_BLEND);
    }

//    static auto main_frame_buffer = FrameBuffer::Builder(window.getSize().x, window.getSize().y).attachColor0("mainFrameBuffer").attachDepthTexture().build();
    static auto main_frame_buffer = FrameBuffer::Builder(1920.0,1080).attachColor0("mainFrameBuffer").attachDepthTexture().build();

//    if (first==1) particles.getRenderer().useFrameBuffer(FrameBuffer::Builder(window.getSize().x, window.getSize().y).attachColor0("particlesFrameBuffer").attachDepthTexture(main_frame_buffer.getDepthBuffer()).build());
    if (first==1) particles.getRenderer().useFrameBuffer(FrameBuffer::Builder(1920,1080).attachColor0("particlesFrameBuffer").attachDepthTexture(main_frame_buffer.getDepthBuffer()).build());
    static Sprite proxySprite;
    if (first==1) proxySprite.setTexture(TextureManager::getSampler("mainFrameBuffer"));

    static int viewport_save[4];
    if (first) glGetIntegerv(GL_VIEWPORT, viewport_save);
    static auto prev_time = std::chrono::steady_clock::now();
    static const std::chrono::steady_clock::duration frame_period(std::chrono::milliseconds(1000 / 60));
    static float frame_period_seconds = std::chrono::duration<float>(frame_period).count();
    static sf::Event event;
    static bool running = true;
    static bool focus   = true;
    static bool paused  = false;
    static glm::mat4 view(1.0f);

    if (first) {
        glm::mat4 *fly_projection_matrix_pointer=&projection_matrix;
        Terrain *fly_terrain_pointer=&terrain;
        Airplane *fly_aircraft_pointer=&aircraft;
        ShadowMap *fly_shadowMap_pointer=&shadowMap;
        Sky *fly_sky_pointer=&sky;
        ParticleSystem *fly_particles_pointer=&particles;
        Camera *fly_camera_pointer=&camera;
        CameraController *fly_mouse_camera_pointer=&mouse_camera;
        fly_paused_pointer=&paused;
        fly_focus_pointer=&focus;
        fly_frame_period_seconds_pointer=&frame_period_seconds;
        fly_controller_pointer=&controller;
        fly_view_pointer=&view;
    }
    if (fly_visible && !fly_is_visible) {
        window.setVisible(true);
        fly_is_visible=true;
    } else if (!fly_visible && fly_is_visible){
        window.setVisible(false);
        fly_is_visible=false;
    }
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
            fly_on = false;
        else if (event.key.code == sf::Keyboard::F9)
            aircraft.m_position.z+=1.0;
        else if (event.type == sf::Event::GainedFocus) {
            focus = true;
            prev_time = std::chrono::steady_clock::now(); printf("Gained focus\n");
        } else if (event.type == sf::Event::LostFocus) {
            focus = false; printf("Lost focus\n");
        } else if (focus && event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F4) {
            paused = !paused; printf("Paused=%d\n",paused);
        } else if (event.type == sf::Event::Resized) {
            glViewport(0, 0, event.size.width, event.size.height);
            glGetIntegerv(GL_VIEWPORT, viewport_save);
//            opts.windowWidth=1920;
//            opts.windowHeight=1080;
            opts.windowWidth=event.size.width;
            opts.windowHeight=event.size.height;
//            glMatrixMode(GL_PROJECTION);
//            glLoadIdentity();
            projection_matrix = glm::perspective(external_perspective[0], 1.f * window.getSize().x / window.getSize().y ,external_perspective[2],external_perspective[3]);
//            projection_matrix = glm::perspective(glm::radians(45.0f), 1.f * window.getSize().x / window.getSize().y,0.05f, 50.0f);
//            glMatrixMode(GL_MODELVIEW);
//            glLoadIdentity();

            printf("Resized\n");
        }
        if (focus) {
            if (event.type == sf::Event::MouseWheelScrolled)
                mouse_camera.passEvent(event);
        }
    }
    static float md;
    delta_mutex.lock();
    md=mousewheel_delta;
    delta_mutex.unlock();
    if (md!=0.0) {
        printf("Got mousewheel_delta=%f ",md);
        mouse_camera.passEvent2(md);
        delta_mutex.lock();
        mousewheel_delta=0.0;
        delta_mutex.unlock();
    }

    auto now = std::chrono::steady_clock::now();
    controller.takeInput(frame_period_seconds);
    if (!paused) {
        if (!crashed) {
            aircraft.update(frame_period_seconds);
            terrain.setCenter(aircraft.getPosition());
        }
        particles.update(frame_period_seconds);
    }

    if (focus)
        mouse_camera.update(frame_period_seconds);
    else {
        interface_mutex.lock();
        mouse_camera.update2(frame_period_seconds, sending_new_mouse);
        interface_mutex.unlock();
    }

    camera.updateView(frame_period_seconds);

//joepie

    delta2_mutex.lock();
    fly_plane_position=aircraft.m_position;
    delta2_mutex.unlock();

    if (camera.viewChanged()) {
        view = camera.getView();
        particles.getRenderer().setView(view);
        aircraftRenderer.setView(view);
        terrainRenderer.setView(view);
        sky.setView(view);
        if (opts.planeBox) box->setView(view);
    }

    auto&& light_space = shadowMap.update();
    terrainRenderer.setLightSpace(light_space);
    glViewport(viewport_save[0], viewport_save[1], viewport_save[2], viewport_save[3]);
    auto boundingBox = glm::translate(aircraft.getModel(), aircraft.getLocalBounds().position);

    static glm::vec3 old_pos_plane;
    static bool sound_flip=false;
    if (!crashed && terrain.above({aircraft.getLocalBounds().dimensions, boundingBox}))
    {
        printf("Aircraft crash=%f,%f,%f press shift-f9 to heal plane\n",aircraft.m_position.x,aircraft.m_position.y,aircraft.m_position.z);
        old_pos_plane=glm::vec3(aircraft.m_position.x,aircraft.m_position.y,aircraft.m_position.z+1.0);
        if (sound_flip)
            playsound=playsound|256;
        else
            playsound=playsound|512;
        sound_flip=!sound_flip;
        aircraft.crash();
        crashed = true;
//        particles.reset(4601);
        particles.reset(10000);

/*
        particles.addEmitter(Emitter::createUniformCone(
                                        650 * 1.5f,                          //float rate,
                                        aircraft.getPosition(),              //const glm::vec3& startingPosition,
                                        glm::vec3{0.001f, 0.001f, 0.0020f},  //const glm::vec3& posVariance,
                                        {0.f, 0.f, 0.023f},                  //const glm::vec3& startingVelocity,
                                        4.f, 5.f,                            //float minLife, float maxLife,
                                        1.00f, 3.00f,                        //float sizeMin, float sizeMax,
                                        PI / 4.f,                            //float angle,
                                        600                                  //int particlesToEmit
                                        ));

        particles.addEmitter(Emitter::createExplosion(
                                        aircraft.getPosition(),               //const glm::vec3& center,
                                        {0.f, 0.f, 1.f},                      //const glm::vec3& spread_up,
                                        {0.f, 0.f, -0.05f * 1.5f * 1.5f},     //const glm::vec3& gravity,
                                        0.08f * 1.5f));                       //float emitter_speed)
*/
        particles.addEmitter(Emitter::createUniformCone(
                                        650 * 1.5f,                          //float rate,
                                        aircraft.getPosition(),              //const glm::vec3& startingPosition,
                                        glm::vec3{0.005f, 0.005f, 0.0040f},  //const glm::vec3& posVariance,
                                        {0.000f, 0.000f, 0.033f},           //const glm::vec3& startingVelocity,
                                        4.f, 5.f,                            //float minLife, float maxLife,
                                        1.00f, 25.00f,                        //float sizeMin, float sizeMax,
                                        PI / 4.f,                            //float angle,
                                        1000                                  //int particlesToEmit
                                        ));

        particles.addEmitter(Emitter::createExplosion(
                                        aircraft.getPosition(),               //const glm::vec3& center,
                                        {0.0f, 0.0f, 1.5f},                      //const glm::vec3& spread_up,
                                        {0.f, 0.f, -0.05f * 1.5f * 1.5f},     //const glm::vec3& gravity,
                                        0.10f * 1.5f));                       //float emitter_speed)

        particles.addUpdater(Updater::basicPhysics);
        particles.addUpdater(Updater::lifeUpdater);
        particles.addUpdater(Updater::fireColor);
        particles.addUpdater(Updater::createLinearSize(0.001f, 0.020f));
        particles.getRenderer().setBlending(Additive);
    }

    if (recover_crash) {
        crashed=false;
        aircraft.recover();
        printf("Airplane recovered\n");
        recover_crash=false;
        aircraft.m_speed=1.0f;
        aircraft.m_position=old_pos_plane;
    }

//    plane_ready=true;

/************/

    if (fly_is_visible) {
        window.setActive(true);
        main_frame_buffer.bind();
    //    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        aircraftRenderer.draw();
        terrainRenderer.draw();
        if (opts.planeBox)
        {
            box->setTransform(glm::scale(boundingBox, aircraft.getLocalBounds().dimensions));
            box->draw();
        }

        sky.draw();
        particles.getRenderer().draw(main_frame_buffer);

        FrameBuffer::bindDefault();
        proxySprite.draw();
    //    window.setActive(false);
        window.display();

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        window.setActive(false);
    }

/*************/

    render_texture.setActive(true);
    if (first) glClearColor(0,255,0,0.0f);
    if (opts.wireframe) glClear(GL_COLOR_BUFFER_BIT); else glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    render_texture.setActive(false);

    render_texture1.setActive(true);
    if (first) glClearColor(255,0,0,0.0f);
    if (opts.wireframe) glClear(GL_COLOR_BUFFER_BIT); else glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    render_texture1.setActive(false);

    render_texture.setActive(true);
//    if (first) glClearColor(0,255,0,0.0f);
//    if (opts.wireframe) glClear(GL_COLOR_BUFFER_BIT); else glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    terrainRenderer.draw();
    sky.draw();

    render_texture.setActive(false);

/*************/

    render_texture1.setActive(true);
//    if (first) glClearColor(255,0,0,0.0f);
//    if (opts.wireframe) glClear(GL_COLOR_BUFFER_BIT); else glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    main_frame_buffer.bind();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    aircraftRenderer.draw();

    particles.getRenderer().draw(main_frame_buffer);
    FrameBuffer::bindDefault();
    render_texture1.setActive(true);
    proxySprite.draw();

    render_texture1.setActive(false);

    render_texture1.display();
    render_texture.display();

    while (doesnt_work==1) sf::sleep(sf::milliseconds(1));

    interface_mutex.lock();
    interface_texture.update(render_texture.getTexture());
    interface_texture1.update(render_texture1.getTexture());
    interface_mutex.unlock();

/*
    render_texture.setActive(true);
    if (first) glClearColor(0,255,0,0.0f);
    if (opts.wireframe) glClear(GL_COLOR_BUFFER_BIT); else glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    render_texture.setActive(false);

    render_texture1.setActive(true);
    if (first) glClearColor(255,0,0,0.0f);
    if (opts.wireframe) glClear(GL_COLOR_BUFFER_BIT); else glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    render_texture1.setActive(false);
*/

/*************/

    window.setActive(true);

//    while (doesnt_work==1) sf::sleep(sf::microseconds(5));

    if (fly_on) {
        doesnt_work=1;
        if (sync==true) {
            window.setVerticalSyncEnabled(false);
            sync=false;
        }
    } else {
        if (sync==false) {
            window.setVerticalSyncEnabled(true);
            sync=true;
        }
    }

    prev_time += frame_period;

    running=true;
    first=false;

    return EXIT_SUCCESS;
}


