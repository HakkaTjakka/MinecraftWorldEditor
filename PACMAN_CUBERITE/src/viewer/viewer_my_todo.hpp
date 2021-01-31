extern sf::Color color_behind;

void reset_text(int win_num) {
    text_mutex.lock();
        if (font_window!=NULL) delete font_window;
        font_window = new sf::Font();
        font_window->loadFromFile("resources/consolab.ttf");

        if (text_window!=NULL) delete text_window;
        text_window = new sf::Text();
        text_window->setCharacterSize(24);
        text_window->setFont(*font_window);
        text_window->setFillColor(sf::Color::White);


//        if (!backgroundTexture[win_num]==NULL) delete backgroundTexture[win_num];
        if (backgroundTexture[win_num]==NULL) {
            backgroundTexture[win_num] = new sf::Texture();
            sf::Image sub;
            if (!sub.loadFromFile("resources/background.png")) {
                printf("error loading resources/background.png\n");
                return;
            }
            color_behind=sub.getPixel(0,0);
            printf("COLOR=(%d,%d,%d,%d)\n",color_behind.r,color_behind.g,color_behind.b,color_behind.a);
            backgroundTexture[win_num]->loadFromImage(sub);
        }

//        sf::Image sub;
//        sub.loadFromFile("resources/background.png");
//        sf::Image sub2;
//        sub2.create(1922,1082,sf::Color(0,0,0,0));
//        sub2.copy(sub,1,1);
//        backgroundTexture[win_num]->loadFromImage(sub2);


        backgroundTexture[win_num]->setSrgb(sRgb);
        backgroundTexture[win_num]->setSmooth(false);

        if (backgroundSprite[win_num]==NULL) delete backgroundSprite[win_num];
        backgroundSprite[win_num] = new sf::Sprite();
        backgroundSprite[win_num]->setTexture(*backgroundTexture[win_num],true);
        backgroundSprite[win_num]->setPosition(0,0);

//        backgroundSprite[win_num]->setOrigin(backgroundTexture[win_num]->getSize().x/2,backgroundTexture[win_num]->getSize().y/2);
//        backgroundSprite[win_num]->setPosition(1920.0/2.0,1080.0/2.0);


        if (font_text!=NULL) delete font_text;
        font_text = new sf::Font();
        font_text->loadFromFile("resources/Sansation_Regular.ttf");
//        sprintf(hoppa,"Pacman Graphics(c) / Stichting Surplus - Lasondersingel 133 - 7514 BP Enschede - Tel: +31(0)53-2068200 - info@st-surplus.nl");
        sprintf(hoppa,"Pacman Graphics(c)");


        if (text_text!=NULL) delete text_text;
        text_text = new sf::Text();
        text_text->setString(hoppa);
        text_text->setFont(*font_window);
        text_text->setCharacterSize(24);
        text_text->setOutlineThickness(1.0);
        text_text->setFillColor(sf::Color(255, 255, 255, 255));
        text_text->setOutlineColor(sf::Color(100,150, 255, 150));


        if (sRgbInstructions!=NULL) delete sRgbInstructions;
        sRgbInstructions = new sf::Text();
        sRgbInstructions->setString("Press n to load next object conversion");
        sRgbInstructions->setFont(*font_window);
        sRgbInstructions->setCharacterSize(48);
        sRgbInstructions->setOutlineThickness(2.0);
        sRgbInstructions->setFillColor(sf::Color(255, 255, 255, 170));
        sRgbInstructions->setOutlineColor(sf::Color(0, 0, 0, 255));

        if (mipmapInstructions!=NULL) delete mipmapInstructions;
        mipmapInstructions = new sf::Text();
        mipmapInstructions->setString("Use mouse left, middle and right button");
        mipmapInstructions->setFont(*font_window);
        mipmapInstructions->setCharacterSize(48);
        mipmapInstructions->setOutlineThickness(2.0);
        mipmapInstructions->setFillColor(sf::Color(255, 255, 255, 170));
        mipmapInstructions->setOutlineColor(sf::Color(0, 0, 0, 255));

        text_text->setPosition(1920-1700, 1080-50);
        sRgbInstructions->setPosition(0.f, 700.f);
        mipmapInstructions->setPosition(0.f, 750.f);

    text_mutex.unlock();
}

void draw2_all(sf::RenderWindow& window,char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer, int text_size)
{
    text_mutex.lock();
    text_window->setString(towrite);
    text_window->setOutlineColor(outer);
    text_window->setOutlineThickness(1.0);
    text_window->setFillColor(inner);
    text_window->setPosition(xpos,ypos);
    text_window->setCharacterSize(text_size);
    window.draw(*text_window);
    text_mutex.unlock();
}

void draw2_all_texture(sf::RenderTexture& window,char *towrite, int xpos, int ypos, sf::Color inner, sf::Color outer, int text_size)
{
    text_mutex.lock();
    text_window->setString(towrite);
    text_window->setOutlineColor(outer);
    text_window->setOutlineThickness(1.0);
    text_window->setFillColor(inner);
    text_window->setPosition(xpos,ypos);
    text_window->setCharacterSize(text_size);
    window.draw(*text_window);
    text_mutex.unlock();
}

glm::mat4 my_rotate(float rotate_object_x, float rotate_object_y, float rotate_object_z) {
    float c_x = cos(rotate_object_x*M_PI/180.0);
    float s_x = sin(rotate_object_x*M_PI/180.0);
    float c_y = cos(rotate_object_y*M_PI/180.0);
    float s_y = sin(rotate_object_y*M_PI/180.0);
    float c_z = cos(-rotate_object_z*M_PI/180.0);
    float s_z = sin(-rotate_object_z*M_PI/180.0);

    float aspect = 1.0;
//              float aspect = 1920.0 / 1080.0;

    return
        glm::mat4(  glm::vec4(1,            0,          0,              0),         //x
                    glm::vec4(0,            c_x,        -s_x/aspect,    0),
                    glm::vec4(0,            s_x*aspect, c_x,            0),
                    glm::vec4(0,            0,          0,              1) ) *

        glm::mat4(  glm::vec4( c_y,         0,          s_y,            0),         //y
                    glm::vec4(   0,         1,          0,              0),
                    glm::vec4(-s_y,         0,          c_y,            0),
                    glm::vec4(   0,         0,          0,              1) ) *

        glm::mat4(  glm::vec4(       c_z,   -s_z*aspect,0,              0),         //z
                    glm::vec4(s_z/aspect,   c_z,        0,              0),
                    glm::vec4(         0,   0,          1,              0),
                    glm::vec4(         0,   0,          0,              1  ) );
}

glm::mat4 my_rotate_zyx(float rotate_object_z, float rotate_object_y, float rotate_object_x) {
    float c_x = cos(rotate_object_x*M_PI/180.0);
    float s_x = sin(rotate_object_x*M_PI/180.0);
    float c_y = cos(rotate_object_y*M_PI/180.0);
    float s_y = sin(rotate_object_y*M_PI/180.0);
    float c_z = cos(-rotate_object_z*M_PI/180.0);
    float s_z = sin(-rotate_object_z*M_PI/180.0);

    float aspect = 1.0;
//              float aspect = 1920.0 / 1080.0;

    return
        glm::mat4(  glm::vec4(       c_z,   -s_z*aspect,0,              0),         //z
                    glm::vec4(s_z/aspect,   c_z,        0,              0),
                    glm::vec4(         0,   0,          1,              0),
                    glm::vec4(         0,   0,          0,              1) ) *

        glm::mat4(  glm::vec4( c_y,         0,          s_y,            0),         //y
                    glm::vec4(   0,         1,          0,              0),
                    glm::vec4(-s_y,         0,          c_y,            0),
                    glm::vec4(   0,         0,          0,              1) ) *

        glm::mat4(  glm::vec4(1,            0,          0,              0),         //x
                    glm::vec4(0,            c_x,        -s_x/aspect,    0),
                    glm::vec4(0,            s_x*aspect, c_x,            0),
                    glm::vec4(0,            0,          0,              1) ) ;

}

glm::mat4 my_rotate2(float rotate_object_x, float rotate_object_y, float rotate_object_z) {
    float c_x = cos(rotate_object_x*M_PI/180.0);
    float s_x = sin(rotate_object_x*M_PI/180.0);
    float c_y = cos(rotate_object_y*M_PI/180.0);
    float s_y = sin(rotate_object_y*M_PI/180.0);
    float c_z = cos(-rotate_object_z*M_PI/180.0);
    float s_z = sin(-rotate_object_z*M_PI/180.0);

    float aspect = 1.0;
//              float aspect = 1920.0 / 1080.0;

    return
        glm::mat4(  glm::vec4(c_y*c_z,          -s_z*aspect,    s_y,            0),
                    glm::vec4(s_z/aspect,       c_x*c_z,        -s_x/aspect,    0),
                    glm::vec4(-s_y,             s_x*aspect,     c_x*c_y,        0),
                    glm::vec4(0,                0,              0,              1) );
}





/*
v{x,y,z}	=	 cos(lat)·cos(lon)
                cos(lat)·sin(lon)
                sin(lat)
*/

void build_rotmatrix_glm(glm::mat4& m, const float q[4]) {
    m={
        1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]),
        2.0 * (q[0] * q[1] - q[2] * q[3]),
        2.0 * (q[2] * q[0] + q[1] * q[3]),
        0.0,

        2.0 * (q[0] * q[1] + q[2] * q[3]),
        1.0 - 2.0 * (q[2] * q[2] + q[0] * q[0]),
        2.0 * (q[1] * q[2] - q[0] * q[3]),
        0.0,

        2.0 * (q[2] * q[0] - q[1] * q[3]),
        2.0 * (q[1] * q[2] + q[0] * q[3]),
        1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]),
        0.0,

        0.0,
        0.0,
        0.0,
        1.0
    };
}

struct obj_loader_struct {
    float bmin[3];
    float bmax[3];
    std::vector<DrawObject> drawObjects;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;
    char* filename;
    int win_num;
    sf::RenderWindow* window;
};

int OBJLOADER_stop=0;
int OBJLOADER_running=0;
bool obj_laucher_ready=false;
bool obj_laucher_return=false;
struct obj_loader_struct loader_struct;

HGLRC loaderContext;

void OBJLOADER_THREAD()
//void OBJLOADER_THREAD(struct obj_loader_struct loader_struct)
{
    wglMakeCurrent(hdc[loader_struct.win_num], loaderContext);

    printf("OBJLOADER thread starting\n");

    obj_laucher_return=LoadObjAndConvert_window(
        loader_struct.bmin,
        loader_struct.bmax,
        loader_struct.drawObjects,
        loader_struct.materials,
        loader_struct.textures,
        loader_struct.filename
    );
    glFinish();
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(loaderContext);

//    do_OBJLOADER();
    printf("OBJLOADER thread stopped.\n");// sf::sleep(sf::seconds(10));
    OBJLOADER_stop=0;
    OBJLOADER_running=0;
    obj_laucher_ready=true;
}


sf::Thread OBJLOADER(&OBJLOADER_THREAD);
extern HWND hWndMain2;

bool launch_OBJLOADER(float bmin[3], float bmax[3], std::vector<DrawObject>& drawObjects, std::vector<tinyobj::material_t>& materials, std::map<std::string, GLuint>& textures, char* filename, int win_num)
{

//      hglrc[win_num] = wglGetCurrentContext();
////      hdc[win_num] = wglGetCurrentDC() ;
//      hdc[win_num] = GetDC(window);

//        hdc_thread = GetDC(hwnd[win_num]);

//    HGLRC mainContext = wglGetCurrentContext();
//    HGLRC loaderContext = wglCreateContext(hdc);
//    wglShareLists(loaderContext, mainContext); // Order matters

//    HGLRC mainContext = hglrc[win_num];
//    HGLRC loaderContext = wglCreateContext(hdc[win_num]);
//    wglShareLists(loaderContext, mainContext); // Order matters


    loaderContext = wglCreateContext(hdc[win_num]);
    wglShareLists(loaderContext, hglrc[win_num]); // Order matters

    if (OBJLOADER_running==1)
    {
        printf("OBJLOADER already running\n");
        return false;
    }

    loader_struct.bmin[0]=bmin[0];
    loader_struct.bmin[1]=bmin[1];
    loader_struct.bmin[2]=bmin[2];
    loader_struct.bmax[0]=bmax[0];
    loader_struct.bmax[1]=bmax[1];
    loader_struct.bmax[2]=bmax[2];
    loader_struct.drawObjects=drawObjects;
    loader_struct.materials=materials;
    loader_struct.textures=textures;
    loader_struct.filename=filename;
    loader_struct.win_num=win_num;

    obj_laucher_ready=false;
    OBJLOADER_running=1;

    OBJLOADER.launch();


    printf("OBJLOADER lauched, say your prayers now! Waiting for ready...\n");
    while (obj_laucher_ready==false) sf::sleep(sf::seconds(1));
    printf("OBJLOADER ready! Return=%d\n",obj_laucher_return);

    wglMakeCurrent(hdc[win_num], hglrc[win_num]);

    bmin[0]=loader_struct.bmin[0];
    bmin[1]=loader_struct.bmin[1];
    bmin[2]=loader_struct.bmin[2];
    bmax[0]=loader_struct.bmax[0];
    bmax[1]=loader_struct.bmax[1];
    bmax[2]=loader_struct.bmax[2];
    drawObjects=loader_struct.drawObjects;
    materials  =loader_struct.materials;
    textures   =loader_struct.textures;

    printf("loader_struct.drawObjects.size()=%d\n",loader_struct.drawObjects.size());
    printf("drawObjects.size()=%d\n",drawObjects.size());

    printf("loader_struct.materials.size()=%d\n",loader_struct.materials.size());
    printf("materials.size()=%d\n",materials.size());

    printf("loader_struct.textures.size()=%d\n",loader_struct.textures.size());
    printf("textures.size()=%d\n",textures.size());

    printf("bmin[0]=%f\n",bmin[0]);
    printf("bmax[0]=%f\n",bmax[0]);

    return obj_laucher_return;
//    sf::sleep(sf::seconds(5.0));

}

void terminate_OBJLOADER()
{
    OBJLOADER.terminate();
}

