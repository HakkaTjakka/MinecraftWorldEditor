
void get_3d_data() {
    GLenum format;
    GLsizei width;
    GLsizei height;
    GLenum type=GL_UNSIGNED_BYTE;
    size_t components;

    switch(format) {
    case GL_BGR:
    case GL_RGB:
        components = 3; break;

    case GL_BGRA:
    case GL_RGBA:
        components = 4; break;

    case GL_ALPHA:
    case GL_LUMINANCE:
        components = 1; break;
    }

    GLubyte *data = (GLubyte*) malloc(components * width * height);
    if( data ) {
        glReadPixels(0, 0, width, height, format, type, data);
    }
}

void display_get3d()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(5,5,5);
    glBegin(GL_QUADS);
    glColor3ub(255,0,0);
    glVertex2f(-1,-1);
    glColor3ub(0,255,0);
    glVertex2f(1,-1);
    glColor3ub(0,0,255);
    glVertex2f(1,1);
    glColor3ub(255,255,255);
    glVertex2f(-1,1);
    glEnd();

    glutSwapBuffers();
}

void mouse_get3d( int x, int y )
{
    // 4 bytes per pixel (RGBA), 1x1 bitmap
    unsigned char pixels[4];
    glFinish();
    glReadPixels
        (
        x, glutGet( GLUT_WINDOW_HEIGHT ) - y,
        1, 1,
        GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]
        );

    std::cout << "r: " << (int)pixels[0] << std::endl;
    std::cout << "g: " << (int)pixels[1] << std::endl;
    std::cout << "b: " << (int)pixels[2] << std::endl;
    std::cout << "a: " << (int)pixels[3] << std::endl;
    std::cout << std::endl;
}

int main_get3d(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    glutInitWindowSize(800,600);
    glutCreateWindow("glReadPixels()");

    glutDisplayFunc(display_get3d);
    glutPassiveMotionFunc(mouse_get3d);
    glutMainLoop();
    return 0;
}

