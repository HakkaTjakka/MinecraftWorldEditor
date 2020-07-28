

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

double step = 10;
double scale = 1.2;

double win_w, win_h;

double pan_x = 0.0;
double pan_y = 0.0;
double zoom_k = 200.0;

void error(const char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(1);
}

void load_tex(const char *filename)
{
    FILE *fp;
    int magic, w, h, maxval;
    int bytes;
    void *data;
    GLuint tex;

    int comp;

/*
    fp = fopen(filename, "rb");
    if (!fp)
	error("unable to open image file");
    if (fscanf(fp, "P%d", &magic) != 1 || magic != 6)
	error("invalid header");
    if (fscanf(fp, "%d %d", &w, &h) != 2 || w < 1 || h < 1)
	error("invalid header");
    if (fscanf(fp, "%d", &maxval) != 1 || maxval != 255)
	error("invalid header");

    bytes = w * h * 3;
    data = malloc(bytes);
    if (fread(data, 1, bytes, fp) != bytes)
	error("invalid header");

    fclose(fp);
*/
    data = stbi_load("test.bmp", &w, &h, &comp, STBI_default);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    if (comp == 3) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else if (comp == 4) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        assert(0);  // TODO
    }

//    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

//    free(data);
}

void reset(void)
{
    pan_x = 0.0;
    pan_y = 0.0;
    zoom_k = 200.0;
}

void draw_object_zoom(void)
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glTexCoord2f(.0, 1.0);
    glVertex2f(.0, 1.0);
    glEnd();
}

void zoom(double factor)
{
    zoom_k *= factor;
}

void pan(double dx, double dy)
{
    pan_x += dx / zoom_k;
    pan_y += dy / zoom_k;
}

void zoom_at(double x, double y, double factor)
{
    pan(-x, -y);
    zoom(factor);
    pan(x, y);
}

void key(unsigned char key, int x, int y)
{
    if (key == '\033')
        exit(0);
}

void special(int k, int x, int y)
{
    if (k == GLUT_KEY_HOME)
        reset();
    else if (k == GLUT_KEY_LEFT)
        pan(-step, 0);
    else if (k == GLUT_KEY_RIGHT)
        pan( step, 0);
    else if (k == GLUT_KEY_DOWN)
        pan(0, -step);
    else if (k == GLUT_KEY_UP)
        pan(0, step);

    glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{
    if (s != GLUT_DOWN)
        return;

    y = win_h - 1 - y;

    if (b == GLUT_LEFT_BUTTON)
        zoom_at(x, y, scale);
    else if (b == GLUT_RIGHT_BUTTON)
        zoom_at(x, y, 1/scale);

    glutPostRedisplay();
}

void draw_zoom(void)
{
    glClearColor(0.5, 0.5, 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom_k, zoom_k, 1);
    glTranslatef(pan_x, pan_y, 0);

    draw_object_zoom();

    glutSwapBuffers();
}

void resize(int w, int h)
{
    if (h == 0)
        h = 1;

    win_w = w;
    win_h = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

int main_zoom(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640, 512);

    glutCreateWindow("Zoom/Pan Test");

    glutDisplayFunc(draw_zoom);
    glutReshapeFunc(resize);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);

    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    load_tex("test.ppm");

    reset();

    glutMainLoop();

    return 0;
}

