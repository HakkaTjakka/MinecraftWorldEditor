
static void reshapeFunc(GLFWwindow* window, int w, int h)
{
    int fb_w, fb_h;
    // Get actual framebuffer size.
    glfwGetFramebufferSize(window, &fb_w, &fb_h);

    glViewport(0, 0, fb_w, fb_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.01f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    width = w;
    height = h;
}

static void keyboardFunc(GLFWwindow* window, int key, int scancode, int action,
                         int mods)
{
    (void)window;
    (void)scancode;
    (void)mods;
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        // Move camera
        float mv_x = 0, mv_y = 0, mv_z = 0;
        if (key == GLFW_KEY_K)            mv_x += 1;
        else if (key == GLFW_KEY_J)       mv_x += -1;
        else if (key == GLFW_KEY_L)       mv_y += 1;
        else if (key == GLFW_KEY_H)       mv_y += -1;
        else if (key == GLFW_KEY_P)       mv_z += 1;
        else if (key == GLFW_KEY_N)       mv_z += -1;
        // camera.move(mv_x * 0.05, mv_y * 0.05, mv_z * 0.05);
        // Close window
        if (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE)  glfwSetWindowShouldClose(window, GL_TRUE);

        // init_frame = true;
    }
}

static void clickFunc(GLFWwindow* window, int button, int action, int mods)
{
    (void)window;
    (void)mods;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            mouseLeftPressed = true;
            trackball(prev_quat, 0.0, 0.0, 0.0, 0.0);
        }
        else if (action == GLFW_RELEASE)
        {
            mouseLeftPressed = false;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            mouseRightPressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            mouseRightPressed = false;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if (action == GLFW_PRESS)
        {
            mouseMiddlePressed = true;
        }
        else if (action == GLFW_RELEASE)
        {
            mouseMiddlePressed = false;
        }
    }
}

static void motionFunc(GLFWwindow* window, double mouse_x, double mouse_y)
{
    (void)window;
    float rotScale = 1.0f;
    float transScale = 2.0f;

    if (mouseLeftPressed)
    {
        trackball(prev_quat, rotScale * (2.0f * prevMouseX - width) / (float)width,
                  rotScale * (height - 2.0f * prevMouseY) / (float)height,
                  rotScale * (2.0f * mouse_x - width) / (float)width,
                  rotScale * (height - 2.0f * mouse_y) / (float)height);

        add_quats(prev_quat, curr_quat, curr_quat);
    }
    else if (mouseMiddlePressed)
    {
        eye[0] -= transScale * (mouse_x - prevMouseX) / (float)width;
        lookat[0] -= transScale * (mouse_x - prevMouseX) / (float)width;
        eye[1] += transScale * (mouse_y - prevMouseY) / (float)height;
        lookat[1] += transScale * (mouse_y - prevMouseY) / (float)height;
    }
    else if (mouseRightPressed)
    {
        eye[2] += transScale * (mouse_y - prevMouseY) / (float)height;
        lookat[2] += transScale * (mouse_y - prevMouseY) / (float)height;
    }

    // Update mouse point
    prevMouseX = mouse_x;
    prevMouseY = mouse_y;
}


static void Init()
{
    trackball(curr_quat, 0, 0, 0, 0);

    eye[0] = 0.0f;
    eye[1] = 0.0f;
    eye[2] = 3.0f;

    lookat[0] = 0.0f;
    lookat[1] = 0.0f;
    lookat[2] = 0.0f;

    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
}


int main_viewer(int argc, char** argv);
extern int shut_up;
//extern sf::RenderWindow SFMLView1;

//OBJ_VIEWER
int do_viewer()
{
    char *m_argv[3];
    char arg1[20]="ik";
//    char arg2[]="model.3.obj";
    char arg2[]="apple.obj";

/*    char arg2[1000];
    int x=0,y=0;
    get_octant_Amsterdam(x,y);
    x=25;y=25;
    strcpy(arg2,get_octant_Amsterdam(x,y).c_str());
*/
//    char arg2[]="Sophie.remesh.uv.m";
//    char arg2[]="Alex.uv.m";

//    char arg3[]="check_1k_64.bmp";


    m_argv[0]=arg1;
    m_argv[1]=arg2;
//    m_argv[2]=arg3;
    int old_shut_up=shut_up;
    shut_up=1;

//    SFMLView1.popGLStates();
//    SFMLView1.setActive(false);
    int ret=main_viewer(2,m_argv);

//    SFMLView1.pushGLStates();

    shut_up=old_shut_up;
    return ret;
}


int VIEWER_stop=0;
int VIEWER_running=0;

void VIEWER_THREAD()
{
    printf("VIEWER thread starting\n");
    do_viewer();
    printf("VIEWER thread stopped\n");
    VIEWER_stop=0;
    VIEWER_running=0;
}

sf::Thread VIEWER(&VIEWER_THREAD);

void launch_VIEWER()
{
    if (VIEWER_running==1)
    {
        printf("VIEWER already running\n");
        return;
    }
    VIEWER_running=1;
    VIEWER.launch();

//    sf::sleep(sf::seconds(5.0));

}

void terminate_VIEWER()
{
    VIEWER.terminate();
}


int main_viewer(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Needs input.obj\n" << std::endl;
        return 0;
    }

    Init();

    if (glwf_initor==false) {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW." << std::endl;
            return -1;
        }
        glwf_initor=true;
    }

    window = glfwCreateWindow(width, height, "Obj viewer", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window. " << std::endl;
        glfwTerminate();
        return 1;
    }
//sf::Window
//sf::Context
//sf::GlResources

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Callback
    glfwSetWindowSizeCallback(window, reshapeFunc);
    glfwSetKeyCallback(window, keyboardFunc);
    glfwSetMouseButtonCallback(window, clickFunc);
    glfwSetCursorPosCallback(window, motionFunc);

    if (glew_initor==false) {
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW." << std::endl;
            return -1;
        }
        glew_initor=true;
    }

    reshapeFunc(window, width, height);

    float bmin[3], bmax[3];
    std::vector<DrawObject> gDrawObjects;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;
    if (false == LoadObjAndConvert(bmin, bmax, gDrawObjects, materials, textures,
                                   argv[1]))
    {
        return -1;
    }

    float maxExtent = 0.5f * (bmax[0] - bmin[0]);
    if (maxExtent < 0.5f * (bmax[1] - bmin[1]))
    {
        maxExtent = 0.5f * (bmax[1] - bmin[1]);
    }
    if (maxExtent < 0.5f * (bmax[2] - bmin[2]))
    {
        maxExtent = 0.5f * (bmax[2] - bmin[2]);
    }

    while (glfwWindowShouldClose(window) == GL_FALSE)
    {
        glfwPollEvents();
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        // camera & rotate
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        GLfloat mat[4][4];
        gluLookAt(eye[0], eye[1], eye[2], lookat[0], lookat[1], lookat[2], up[0],
                  up[1], up[2]);
        build_rotmatrix(mat, curr_quat);
        glMultMatrixf(&mat[0][0]);

        // Fit to -1, 1
        glScalef(1.0f / maxExtent, 1.0f / maxExtent, 1.0f / maxExtent);

        // Centerize object.
        glTranslatef(-0.5 * (bmax[0] + bmin[0]), -0.5 * (bmax[1] + bmin[1]),   -0.5 * (bmax[2] + bmin[2]));

        Draw(gDrawObjects, materials, textures);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

