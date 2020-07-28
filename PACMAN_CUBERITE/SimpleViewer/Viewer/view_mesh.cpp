#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include "viewer/arcball.h"                           /*  Arc Ball  Interface         */
#include "Mesh/TriangleSoup.h"
#include "bmp/RgbImage.h"
//#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
//#include <SFML/Network.hpp>
//#include <SFML/System/Mutex.hpp>
//#include <SFML/Network/IpAddress.hpp>

//compiling command
//g++ -lGL -lglut -lGLU -IMeshLib view_mesh.C -o view_mesh
int win_width, win_height;
using namespace MeshLib::TriangleSoup;

enum mesh_type{OBJ,M};

CTriangleMesh mesh;
CObject       object;

mesh_type current_mesh_type;

/* window width and height */
int gButton;
int startx,starty;
int shadeFlag   = 0 ;

/* rotation quaternion and translation vector for the object */
MeshLib::CQrot       ObjRot(0,0,1,0);
MeshLib::CPoint      ObjTrans(0,0,0);
/* arcball object */
MeshLib::CArcball arcball;

/* geometry flag */
int geometryFlag = 0;

/* texture flag */
int textureFlag =  2;
/* texture id and image */
GLuint texName;
RgbImage image;



int do3dview();

int OPENGL_stop=0;
int OPENGL_running=0;
void OPENGL_THREAD() {
    printf("OPENGL thread starting\n");
    do3dview();
    printf("OPENGL thread stopped\n");
    OPENGL_stop=0;
    OPENGL_running=0;
}

sf::Thread OPENGL(&OPENGL_THREAD);

void launch_OPENGL() {
    if (OPENGL_running==1) {
        printf("OPENGL already running\n");
        return;
    }
    OPENGL_running=1;
    OPENGL.launch();

//    sf::sleep(sf::seconds(5.0));

}

void terminate_OPENGL() {
    OPENGL.terminate();
}

int main_hoppa();
int SFMLGL_stop=0;
int SFMLGL_running=0;
void SFMLGL_THREAD() {
    printf("SFMLGL thread starting\n");
    main_hoppa();
    printf("SFMLGL thread stopped\n");
    SFMLGL_stop=0;
    SFMLGL_running=0;
}

sf::Thread SFMLGL(&SFMLGL_THREAD);

void launch_SFMLGL() {
    if (SFMLGL_running==1) {
        printf("SFMLGL already running\n");
        return;
    }
    SFMLGL_running=1;
    SFMLGL.launch();

//    sf::sleep(sf::seconds(5.0));

}

void terminate_SFMLGL() {
    SFMLGL.terminate();
}



/*! setup the object, transform from the world to the object coordinate system */
void setupObject(void)
{
    double rot[16];

    glTranslated( ObjTrans[0], ObjTrans[1], ObjTrans[2]);
    ObjRot.convert( rot );
    glMultMatrixd(( GLdouble *)  rot );
}

/*! the eye is always fixed at world z = +5 */

void setupEye(void){
  glLoadIdentity();
  gluLookAt( 0,0, 5,0,0,0,0,1,0);
}

/*! setup light */
void setupLight()
{
	//MeshLib::CPoint position(0,0,-1);
	MeshLib::CPoint position(0,0,1);
	GLfloat lightOnePosition[4]={position[0], position[1], position[2], 0};
	glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);
	MeshLib::CPoint position2(0,0,-1);
	GLfloat lightTwoPosition[4]={position2[0], position2[1], position2[2], 0};
	glLightfv(GL_LIGHT2, GL_POSITION, lightTwoPosition);
}

/*! draw mesh */
void draw_mesh()
{
	  glBindTexture(GL_TEXTURE_2D, texName);

	//glColor3f( 1.0, 1.0, 1.0 );
	//glDisable( GL_LIGHTING );
	for( size_t i = 0; i < mesh.faces().size(); i ++ )
	{
		CFace * pF = mesh.faces()[i];
  		glBegin(GL_TRIANGLES);
		if( shadeFlag == 0 )
		{
			glNormal3f( pF->m_normal[0], pF->m_normal[1], pF->m_normal[2] );
			//glNormal3f( -pF->m_normal[0], -pF->m_normal[1], -pF->m_normal[2] );
			//std::cout << pF->m_normal[0] << " " << pF->m_normal[1] << " " << pF->m_normal[2] << std::endl;
		}
		for( int j = 0; j < 3; j ++ )
		{
			CVertex * pV = pF->m_v[j];
			if( shadeFlag == 1 )
				glNormal3f( pV->m_normal[0], pV->m_normal[1], pV->m_normal[2] );


			if( mesh.m_has_uv )
			{
				MeshLib::CPoint2 uv = pV->m_uv;
				glTexCoord2d( uv[0], uv[1] );
			}

			MeshLib::CPoint skin_rgb( 235/255.0,180/255.0,173/255.0);

			if( mesh.m_has_rgb )
				glColor3f( pV->m_rgb[0], pV->m_rgb[1], pV->m_rgb[2] );
			else
				//glColor3f( 1,1,1 );
				glColor3f( skin_rgb[0], skin_rgb[1],skin_rgb[2] );

			if( geometryFlag && mesh.m_has_uv )
			{
				glVertex3d( pV->m_uv[0], pV->m_uv[1] , 0);
			}
			else
			{
				glVertex3d( pV->m_point[0], pV->m_point[1], pV->m_point[2] );
			}
		}
		glEnd();
	}

}



/*! draw object */
void draw_object()
{
	  glBindTexture(GL_TEXTURE_2D, texName);

	for( size_t i = 0; i < object.faces().size(); i ++ )
	{
		CObjFace & pF = object.faces()[i];
  		glBegin(GL_TRIANGLES);
		if( shadeFlag == 0 )
		{
			glNormal3f( pF.m_normal[0], pF.m_normal[1], pF.m_normal[2] );
		}
		for( int j = 0; j < 3; j ++ )
		{
			CObjVertex & pV = pF.m_v[j];
			if( shadeFlag == 1 )
			{
				MeshLib::CPoint n = object.normals()[ pV.m_inl ];
				glNormal3f( n[0], n[1], n[2] );
			}

			if( object.m_has_uv )
			{
				MeshLib::CPoint2 uv = object.uvs()[pV.m_iuv];
				glTexCoord2d( uv[0], uv[1] );
			}

			MeshLib::CPoint skin_rgb( 235/255.0,180/255.0,173/255.0);
			glColor3f( skin_rgb[0], skin_rgb[1],skin_rgb[2] );

			if( geometryFlag && object.m_has_uv )
			{
				MeshLib::CPoint2 uv = object.uvs()[pV.m_iuv];
				glVertex3d( uv[0], uv[1] , 0);
			}
			else
			{
				MeshLib::CPoint p = object.points()[pV.m_ipt];
				glVertex3d( p[0], p[1], p[2] );
			}
		}
		glEnd();
	}

}


/*! display call back function
*/
void display()
{
	/* clear frame buffer */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupLight();
	/* transform from the eye coordinate system to the world system */
	setupEye();
	glPushMatrix();
	/* transform from the world to the ojbect coordinate system */
	setupObject();
  	/* draw the mesh */
	switch( current_mesh_type )
	{
	case OBJ:
		draw_object();
		break;
	case M:
		draw_mesh();
		break;
	}
	glPopMatrix();
	glutSwapBuffers();
}

/*! Called when a "resize" event is received by the window. */

void reshape(int w, int h)
{
  float ar;

  win_width=w;
  win_height=h;

  ar = (float)(w)/h;
  glViewport(0, 0, w, h);               /* Set Viewport */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // magic imageing commands
  gluPerspective( 40.0, /* field of view in degrees */
		  ar, /* aspect ratio */
		  1.0, /* Z near */
		  100.0 /* Z far */);

  glMatrixMode(GL_MODELVIEW);

  glutPostRedisplay();
}

/*! helper function to remind the user about commands, hot keys */
void help()
{
  printf("w - Wireframe Display\n");

  printf("f  -  Flat Shading \n");
  printf("s  -  Smooth Shading\n");
  printf("t  -  Texture Mapping\n");
  printf("r  -  Reset the view\n" );
  printf("g  -  Toggle Geometry and UV view\n");

  printf("o  -  Save frame buffer to snap_n.bmp\n");
  printf("? -  Help Information\n");
  printf("esc - quit\n");
}

/*! Keyboard call back function */

void keyBoard(unsigned char key, int x, int y)
{

	switch( key )
	{
	case 'f':
		//Flat Shading
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		shadeFlag = 0;
		break;
	case 's':
    		//Smooth Shading
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		shadeFlag = 1;
		break;
	case 'w':
	  	//Wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;

  case 't':
    textureFlag = (textureFlag +1 )%3;
    switch( textureFlag )
    {
    case 0:
        glDisable(GL_TEXTURE_2D);
        break;
    case 1:
        glEnable(GL_TEXTURE_2D);
		    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        break;
    case 2:
       glEnable(GL_TEXTURE_2D);
		    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
       break;
    }
    break;

  case 'g':
	  geometryFlag = (geometryFlag + 1)%2;
	  break;

  case 'r':
	  	ObjRot = MeshLib::CQrot(0,0,1,0);
		ObjTrans = MeshLib::CPoint(0,0,0);
	  break;

  case '?':
    help();
    break;
  case 27:
        glutLeaveMainLoop();
//        glutDestroyWindow(glutGetWindow());
//        glClose();
//        exit(0);
        return;
		break;
	}
  glutPostRedisplay();
}

/*! setup GL states */
void setupGLstate(){

  GLfloat lightOneColor[] = {1, 1, 1, 1};
  GLfloat globalAmb[] = {.1, .1, .1, 1};
  GLfloat lightOnePosition[] = {.0,  .0, 1, 0.0};

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  //glFrontFace(GL_CW);
  glEnable(GL_DEPTH_TEST);
  //glClearColor(0,0,0,0);
  glClearColor(1.0,1.0,1.0,1.0);
  glShadeModel(GL_SMOOTH);


    glClearDepth(1.0f);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
//    gluPerspective(60.0f, 250/250, 0, 20);

  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightOneColor);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, lightOneColor);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  //glColorMaterial(GL_BACK, GL_AMBIENT_AND_DIFFUSE);

  glLightfv(GL_LIGHT1, GL_POSITION, lightOnePosition);
}

/*! mouse click call back function */
void  mouseClick(int button , int state, int x, int y){


  /* set up an arcball around the Eye's center
	  switch y coordinates to right handed system  */

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
      gButton = GLUT_LEFT_BUTTON;
	  arcball = MeshLib::CArcball( win_width, win_height,  x-win_width/2,  win_height-y-win_height/2);
  }

  if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
      startx = x;
      starty = y;
      gButton = GLUT_MIDDLE_BUTTON;
   }

  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
      startx = x;
      starty = y;
      gButton = GLUT_RIGHT_BUTTON;
   }
  return ;
}

/*! mouse motion call back function */

void mouseMove(int x, int y)
{
	MeshLib::CPoint trans;
	MeshLib::CQrot       rot;

  /* rotation, call arcball */
  if (gButton == GLUT_LEFT_BUTTON )
  {
      rot = arcball.update( x-win_width/2, win_height-y-win_height/2);
      ObjRot =  rot * ObjRot;
      glutPostRedisplay();
  }

  /*xy translation */
  if (gButton == GLUT_MIDDLE_BUTTON)
  {
	  double scale = 10./win_height;
      trans =  MeshLib::CPoint(scale*(x-startx), scale*(starty-y), 0  );
	    startx = x;
	    starty = y;
      ObjTrans = ObjTrans + trans;
      glutPostRedisplay();
  }

  /* zoom in and out */
  if (gButton == GLUT_RIGHT_BUTTON ) {
      double scale = 10./win_height;
      trans =  MeshLib::CPoint(0,0, scale*(starty-y)   );
	    startx = x;
	    starty = y;
      ObjTrans = ObjTrans+trans;
      glutPostRedisplay();
  }
}


void normalize( CTriangleMesh & mesh )
{
	MeshLib::CPoint center(0,0,0);
	for( size_t i = 0; i < mesh.vertices().size(); i ++ )
	{
		CVertex * pV = mesh.vertices()[i];
		center += pV->m_point;
	}
	center /= (double)(mesh.vertices().size());

	for( size_t i = 0; i < mesh.vertices().size(); i ++ )
	{
		CVertex * pV = mesh.vertices()[i];
		pV->m_point -= center;
	}

	double len = -1;
	for( size_t i = 0; i < mesh.vertices().size(); i ++ )
	{
		CVertex * pV = mesh.vertices()[i];
		for( int j = 0; j < 3; j ++ )
		{
			len = (len > fabs(pV->m_point[j]))? len: fabs(pV->m_point[j]);
		}
	}

	for( size_t i = 0; i < mesh.vertices().size(); i ++ )
	{
		CVertex * pV = mesh.vertices()[i];
		pV->m_point /= len;
	}

}



void normalize( CObject & object )
{
	MeshLib::CPoint center(0,0,0);
	for( size_t i = 0; i < object.points().size(); i ++ )
	{
		center += object.points()[i];
	}
	center /= (double)(object.points().size());

	for( size_t i = 0; i < object.points().size(); i ++ )
	{
		object.points()[i] -= center;
	}

	double len = -1;

	for( size_t i = 0; i < object.points().size(); i ++ )
	{
		MeshLib::CPoint p = object.points()[i];
		for( int j = 0; j < 3; j ++ )
		{
			len = (len > p[j])? len: fabs(p[j]);
		}
	}
//    len=len/10;
	for( size_t i = 0; i < object.points().size(); i ++ )
	{
		object.points()[i] /= len;
	}

}


void compute_normal( CTriangleMesh & mesh )
{
	for( size_t i = 0; i < mesh.faces().size(); i ++ )
	{
		CFace * pF = mesh.faces()[i];
		MeshLib::CPoint p[3];
		for( int j = 0; j < 3; j ++ )
		{
			p[j] = pF->m_v[j]->m_point;
		}
		MeshLib::CPoint nor = (p[1]-p[0])^(p[2]-p[0]);
		pF->m_area = nor.norm();

		nor /= nor.norm();
		pF->m_normal = nor;
	}

	for( size_t i = 0; i < mesh.faces().size(); i ++ )
	{
		CFace * pF = mesh.faces()[i];
		MeshLib::CPoint p[3];
		for( int j = 0; j < 3; j ++ )
		{
			p[j] = pF->m_v[j]->m_point;
		}
		MeshLib::CPoint nor = (p[1]-p[0])^(p[2]-p[0]);
		nor /= nor.norm();
		pF->m_normal = nor;

		for( int j = 0; j < 3; j ++ )
		{
			pF->m_v[j]->m_normal += pF->m_normal * pF->m_area;
		}
	}

	for( size_t i = 0; i < mesh.vertices().size(); i ++ )
	{
		CVertex * pV = mesh.vertices()[i];
		pV->m_normal /= pV->m_normal.norm();
	}

    for( size_t i = 0; i < mesh.vertices().size(); i ++ )
	{
		CVertex * pV = mesh.vertices()[i];
		pV->m_area = 0;
	}

    //compute the vertex area
	for( size_t i = 0; i < mesh.faces().size(); i ++ )
	{
		CFace * pF = mesh.faces()[i];
		for( int j = 0; j < 3; j ++ )
		{
			pF->m_v[j]->m_area += pF->m_area/3.0;
		}
	}
}


void compute_normal( CObject & object )
{
	for( size_t i = 0; i < object.faces().size(); i ++ )
	{
		CObjFace * pF = & object.faces()[i];

		MeshLib::CPoint p[3];
		for( int j = 0; j < 3; j ++ )
		{
			p[j] = object.points()[pF->m_v[j].m_ipt];
		}

		MeshLib::CPoint nor = (p[1]-p[0])^(p[2]-p[0]);
		pF->m_area = nor.norm();

		nor /= nor.norm();
		pF->m_normal = nor;
	}

	if( object.m_has_normal ) return;

	object.normals().resize( object.points().size() );

	for( size_t i = 0; i < object.faces().size(); i ++ )
	{
		CObjFace * pF = &object.faces()[i];

		for( int j = 0; j < 3; j ++ )
		{
			pF->m_v[j].m_inl = pF->m_v[j].m_ipt;
			object.normals()[pF->m_v[j].m_inl] += pF->m_normal * pF->m_area;
		}
	}

	for( size_t i = 0; i < object.normals().size(); i ++ )
	{
		object.normals()[i] /= object.normals()[i].norm();
	}

}

/*! initialize bitmap image texture */

void initialize_bmp_texture()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,   GL_LINEAR);

	int ImageWidth  = image.GetNumCols();
	int ImageHeight = image.GetNumRows();
	GLubyte * ptr   = (GLubyte * )image.ImageData();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
				        ImageWidth,
						ImageHeight,
				        0,
				        GL_RGB,
				        GL_UNSIGNED_BYTE,
						ptr);

    if(textureFlag == 1)
		  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    else if(textureFlag == 2)
		  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);
}


/*! main function for viewer
*/

int mainviewer(int argc, char* argv[]);

extern int shut_up;

extern sf::RenderWindow SFMLView1;

//MESH_VIEWER
int do3dview() {
    char *m_argv[3];
    char arg1[20]="ik";
//    char arg2[]="apple2.obj";
//    char arg2[]="model.2.obj";
    char arg2[]="Sophie.remesh.uv.m";
//    char arg2[]="Alex.uv.m";

    char arg3[]="check_1k_64.bmp";


    m_argv[0]=arg1;
    m_argv[1]=arg2;
    m_argv[2]=arg3;
    int old_shut_up=shut_up;
    shut_up=1;

//    SFMLView1.popGLStates();
    SFMLView1.setActive(false);
    int ret=mainviewer(2,m_argv);

//    SFMLView1.pushGLStates();

    shut_up=old_shut_up;
    return ret;
}

extern kiki();
extern int monitor_off;


int mainviewer( int argc, char * argv[] )
{

//    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
//    window.setVerticalSyncEnabled(true);
//    window.setActive(true);



	/* glut stuff */
//    pushState();
//	resetGLState();

/*
    sf::ContextSettings contextSettings(0,0,2,3,0);
    contextSettings.antialiasingLevel = 0;
    contextSettings.stencilBits = 0;
    contextSettings.depthBits=24;

    sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Close, contextSettings);
    App.setActive();
*/

//    sf::RenderWindow window(sf::VideoMode(600, 600), "OpenGL SFML", GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    window.setVerticalSyncEnabled(true);
//    window.setActive(true);
//    glPopAttrib();

	glutInit(&argc, argv);                /* Initialize GLUT */
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );


	glutInitWindowSize(600, 600);
	glutCreateWindow("Mesh Viewer");        /* Create window with given title */
	glViewport(0,0,800,800 );

	glutDisplayFunc(display);             /* Set-up callback functions */
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(keyBoard);
	setupGLstate();

	std::string name( argv[1] );
	unsigned pos = name.find_last_of(".");
	std::string type  = name.substr( pos +1 );

	if( type == "obj" )
	{
		object.read( argv[1] );
		normalize( object );
		compute_normal( object );
		current_mesh_type = OBJ;

	}
	else if( type == "m" )
	{
		mesh.read_m( argv[1] );
		normalize( mesh );
		compute_normal( mesh );
		current_mesh_type = M;
	}

	textureFlag = 0;

	if( argc > 2 )
	{
		image.LoadBmpFile( argv[2] );
	}

	if( argc > 2 )
	{
		initialize_bmp_texture();
		textureFlag = 2;
	}
	glutMainLoop();                       /* Start GLUT event-processing loop */
//    popState();

	return 0;
}





////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////


#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#ifndef GL_SRGB8_ALPHA8
#define GL_SRGB8_ALPHA8 0x8C43
#endif



////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main_hoppa()
{
    bool exit = false;
    bool sRgb = false;

    while (!exit)
    {
        // Request a 24-bits depth buffer when creating the window
        sf::ContextSettings contextSettings;
        contextSettings.depthBits = 24;
        contextSettings.sRgbCapable = sRgb;

        // Create the main window
        sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
        window.setVerticalSyncEnabled(true);

        // Create a sprite for the background
        sf::Texture backgroundTexture;
        backgroundTexture.setSrgb(sRgb);
        if (!backgroundTexture.loadFromFile("resources/background.jpg"))
            return EXIT_FAILURE;
        sf::Sprite background(backgroundTexture);

        // Create some text to draw on top of our OpenGL object
        sf::Font font;
        if (!font.loadFromFile("resources/Sansation_Regular.ttf"))
            return EXIT_FAILURE;
        sf::Text text("SFML / OpenGL demo", font);
        sf::Text sRgbInstructions("Press space to toggle sRGB conversion", font);
        sf::Text mipmapInstructions("Press return to toggle mipmapping", font);
        text.setFillColor(sf::Color(255, 255, 255, 170));
        sRgbInstructions.setFillColor(sf::Color(255, 255, 255, 170));
        mipmapInstructions.setFillColor(sf::Color(255, 255, 255, 170));
        text.setPosition(250.f, 450.f);
        sRgbInstructions.setPosition(150.f, 500.f);
        mipmapInstructions.setPosition(180.f, 550.f);

        // Load a texture to apply to our 3D cube
        sf::Texture texture;
        if (!texture.loadFromFile("resources/texture.jpg"))
            return EXIT_FAILURE;

        // Attempt to generate a mipmap for our cube texture
        // We don't check the return value here since
        // mipmapping is purely optional in this example
        texture.generateMipmap();

        // Make the window the active window for OpenGL calls
        window.setActive(true);

        // Enable Z-buffer read and write
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glClearDepth(1.f);

        // Disable lighting
        glDisable(GL_LIGHTING);

        // Configure the viewport (the same size as the window)
        glViewport(0, 0, window.getSize().x, window.getSize().y);

        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
        glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

        // Bind the texture
        glEnable(GL_TEXTURE_2D);
        sf::Texture::bind(&texture);

        // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
        static const GLfloat cube[] =
        {
            // positions    // texture coordinates
            -20, -20, -20,  0, 0,
            -20,  20, -20,  1, 0,
            -20, -20,  20,  0, 1,
            -20, -20,  20,  0, 1,
            -20,  20, -20,  1, 0,
            -20,  20,  20,  1, 1,

             20, -20, -20,  0, 0,
             20,  20, -20,  1, 0,
             20, -20,  20,  0, 1,
             20, -20,  20,  0, 1,
             20,  20, -20,  1, 0,
             20,  20,  20,  1, 1,

            -20, -20, -20,  0, 0,
             20, -20, -20,  1, 0,
            -20, -20,  20,  0, 1,
            -20, -20,  20,  0, 1,
             20, -20, -20,  1, 0,
             20, -20,  20,  1, 1,

            -20,  20, -20,  0, 0,
             20,  20, -20,  1, 0,
            -20,  20,  20,  0, 1,
            -20,  20,  20,  0, 1,
             20,  20, -20,  1, 0,
             20,  20,  20,  1, 1,

            -20, -20, -20,  0, 0,
             20, -20, -20,  1, 0,
            -20,  20, -20,  0, 1,
            -20,  20, -20,  0, 1,
             20, -20, -20,  1, 0,
             20,  20, -20,  1, 1,

            -20, -20,  20,  0, 0,
             20, -20,  20,  1, 0,
            -20,  20,  20,  0, 1,
            -20,  20,  20,  0, 1,
             20, -20,  20,  1, 0,
             20,  20,  20,  1, 1
        };

        // Enable position and texture coordinates vertex components
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
        glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);

        // Disable normal and color vertex components
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        // Make the window no longer the active window for OpenGL calls
        window.setActive(false);

        // Create a clock for measuring the time elapsed
        sf::Clock clock;

        // Flag to track whether mipmapping is currently enabled
        bool mipmapEnabled = true;

        // Start game loop
        while (window.isOpen())
        {
            // Process events
            sf::Event event;
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                {
                    exit = true;
                    window.close();
                }

                // Escape key: exit
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                {
                    exit = true;
                    window.close();
                }

                // Return key: toggle mipmapping
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
                {
                    if (mipmapEnabled)
                    {
                        // We simply reload the texture to disable mipmapping
                        if (!texture.loadFromFile("resources/texture.jpg"))
                            return EXIT_FAILURE;

                        mipmapEnabled = false;
                    }
                    else
                    {
                        texture.generateMipmap();

                        mipmapEnabled = true;
                    }
                }

                // Space key: toggle sRGB conversion
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
                {
                    sRgb = !sRgb;
                    window.close();
                }

                // Adjust the viewport when the window is resized
                if (event.type == sf::Event::Resized)
                {
                    // Make the window the active window for OpenGL calls
                    window.setActive(true);

                    glViewport(0, 0, event.size.width, event.size.height);

                    // Make the window no longer the active window for OpenGL calls
                    window.setActive(false);
                }
            }

            // Draw the background
            window.pushGLStates();
            window.draw(background);
            window.popGLStates();

            // Make the window the active window for OpenGL calls
            window.setActive(true);

            // Clear the depth buffer
            glClear(GL_DEPTH_BUFFER_BIT);

            // We get the position of the mouse cursor, so that we can move the box accordingly
            float x =  sf::Mouse::getPosition(window).x * 200.f / window.getSize().x - 100.f;
            float y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y + 100.f;

            // Apply some transformations
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(x, y, -100.f);
            glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
            glRotatef(clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
            glRotatef(clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);

            // Draw the cube
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // Make the window no longer the active window for OpenGL calls
            window.setActive(false);

            // Draw some text on top of our OpenGL object
            window.pushGLStates();
            window.draw(text);
            window.draw(sRgbInstructions);
            window.draw(mipmapInstructions);
            window.popGLStates();

            // Finally, display the rendered frame on screen
            window.display();
        }
    }

    return EXIT_SUCCESS;
}
