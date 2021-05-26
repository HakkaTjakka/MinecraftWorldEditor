
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Effect.hpp"
#include <vector>
#include <cmath>
#define PI 3.141592653589793
//#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#define GLM_FORCE_RADIANS
#include <SFML/OpenGL.hpp>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <algorithm>
extern bool WIRE_FRAME;

extern sf::Texture texture_from_internet;

struct handler_struct {
    int blending;
    int plot_front;
    int show;
    int tile;
    int shader;
};

#define FFMPEG_SELECT 0
#define INTERNET_SELECT 1
#define MOVIE_SELECT 2
#define MOVIE2_SELECT 3
#define CANVAS_SELECT 4

#define BLENDING_SELECT 0
#define PLOT_FRONT_SELECT 1
#define SHOW_SELECT 2
#define TILE_SELECT 3
#define SHADER_SELECT 4

float iZoom=10.0;
extern struct handler_struct handler[];
extern int plot_cubes;
extern int selector;
extern int selector_item;

extern int draw_model;
extern float plot_all_translate_x;
extern float plot_all_translate_y;
extern float plot_all_translate_z;
extern float plot_all_rotate_x;
extern float plot_all_rotate_y;
extern float plot_all_rotate_z;

float plot_all_znear=0.1;
float plot_all_zfar=10.0;
float plot_all_fovyInDegrees=90.0;

extern int plot_all;
extern sf::Texture sfml_mazedot;
extern sf::Texture sfml_mazedot2;
extern sf::Texture texture_cube;
extern int yellow;
extern int maxpixelsx;
extern int maxpixelsy;
extern int new_verschilx;
extern int new_verschily;
extern int new_verschilx2;
extern int new_verschily2;
extern int render_picturex;
extern int render_posx;
extern int render_picturey;
extern int render_posy;
extern int picturex;
extern int posx;
extern int picturey;
extern int posy;
extern int old_number;
extern int connected;
extern int playerleft;
extern sf::Mutex mutje;
extern int cool;
extern sf::BlendMode MyBlendMode[];

sf::RenderWindow shader_window;
extern sf::RenderWindow SFMLView1;
sf::RenderTexture overlay;
extern float fpstime;
extern sf::Sprite sprite_from_ffmpeg;
extern sf::Sprite sprite_from_canvas;
extern sf::Sprite sprite_from_internet;

const sf::Font* Effect::s_font = NULL;
extern float fpstime;
extern sf::RenderTexture *texturemaxinmempoint[];
extern int  **used2;
int radar=0;
extern float rotation_ffmpeg;
extern float rotation_canvas;
extern float rotation_internet;
extern double smooth_x,smooth_y;
extern float shader_map_angle;

void glhFrustumf2(float *matrix, float left, float right, float bottom, float top,
                  float znear, float zfar)
{
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;

    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;

    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;

    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
}
glm::mat4 Model_pers;

void glhPerspectivef2_other2(float *matrix, float fovyInDegrees, float aspectRatio,
                      float znear, float zfar) {
    double D2R = M_PI / 180.0;
    float y_scale = (float)((1 / tan( D2R*(double) fovyInDegrees / 2)))*aspectRatio;
    float x_scale = y_scale / aspectRatio;
    float frustum_length = zfar - znear;
    Model_pers=glm::mat4(   glm::vec4(x_scale,0,0,0),
                            glm::vec4(0,y_scale,0,0),
                            glm::vec4(0,0,-((zfar + znear) / frustum_length),-1),
                            glm::vec4(0,0,-((2 * znear * zfar) / frustum_length),0) );
}

void glhPerspectivef2_other(float *matrix, float fovyInDegrees, float aspectRatio,
                      float znear, float zfar)
{
    double D2R = M_PI / 180.0;
    double yScale = 1.0 / tan(D2R * (double)fovyInDegrees / 2.0);
    double xScale = yScale / (double) aspectRatio;
    double nearmfar = (double)(znear - zfar);

    matrix[0] = (float) xScale;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;

    matrix[4] = 0.0;
    matrix[5] = (float) yScale;
    matrix[6] = 0.0;
    matrix[7] = 0.0;

    matrix[8] = 0.0;
    matrix[9] = 0.0;
    matrix[10] = (float) ((zfar + znear) / nearmfar);
    matrix[11] = -1.0;

    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (float) (2*zfar*znear / nearmfar);
    matrix[15] = 0.0;
}

void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio,
                      float znear, float zfar)
{
    float ymax, xmax;
//    float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
    // ymin = -ymax;
    // xmin = -ymax * aspectRatio;
    xmax = ymax * aspectRatio;
    glhFrustumf2(matrix, -xmax/iZoom, xmax/iZoom, -ymax/iZoom, ymax/iZoom, znear, zfar);
}

////////////////////////////////////////////////////////////
// "Pixelate" fragment shader
////////////////////////////////////////////////////////////
class Pixelate : public Effect
{
public:

    Pixelate() :
    Effect("pixelate")
    {
    }

    bool onLoad()
    {
        // Load the texture and initialize the sprite
        if (!m_texture.loadFromFile("shaders/background.jpg"))
            return false;
//        m_texture.setRepeated(true);
        m_sprite.setTexture(m_texture,true);

        // Load the shader
        if (!m_shader.loadFromFile("shaders/pixelate.frag", sf::Shader::Fragment))
            return false;
        m_shader.setUniform("texture", sf::Shader::CurrentTexture);
//        m_sprite.setScale((float)1920.0/(float)m_texture.getSize().x , (float)1080.0/(float)m_texture.getSize().y) ;

        return true;
    }

    void onUpdate(float, float x, float y)
    {
        m_shader.setUniform("pixel_threshold", (x + y) / 30);
        m_sprite.setScale((float)1920.0/(float)m_texture.getSize().x , (float)1080.0/(float)m_texture.getSize().y) ;
//        m_sprite.setScale((float)shader_window.getSize().x/(float)m_texture.getSize().x , (float)shader_window.getSize().y/(float)m_texture.getSize().y) ;
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.shader = &m_shader;
        target.draw(m_sprite, states);
    }

private:

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Shader m_shader;
};


////////////////////////////////////////////////////////////
// "Wave" vertex shader + "blur" fragment shader
////////////////////////////////////////////////////////////
class WaveBlur : public Effect
{
public:

    WaveBlur() :
    Effect("wave + blur")
    {
    }

    bool onLoad()
    {
        // Create the text
        m_text.setString("Praesent suscipit augue in velit pulvinar hendrerit varius purus aliquam.\n"
                         "Mauris mi odio, bibendum quis fringilla a, laoreet vel orci. Proin vitae vulputate tortor.\n"
                         "Praesent cursus ultrices justo, ut feugiat ante vehicula quis.\n"
                         "Donec fringilla scelerisque mauris et viverra.\n"
                         "Maecenas adipiscing ornare scelerisque. Nullam at libero elit.\n"
                         "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.\n"
                         "Nullam leo urna, tincidunt id semper eget, ultricies sed mi.\n"
                         "Morbi mauris massa, commodo id dignissim vel, lobortis et elit.\n"
                         "Fusce vel libero sed neque scelerisque venenatis.\n"
                         "Integer mattis tincidunt quam vitae iaculis.\n"
                         "Vivamus fringilla sem non velit venenatis fermentum.\n"
                         "Vivamus varius tincidunt nisi id vehicula.\n"
                         "Integer ullamcorper, enim vitae euismod rutrum, massa nisl semper ipsum,\n"
                         "vestibulum sodales sem ante in massa.\n"
                         "Vestibulum in augue non felis convallis viverra.\n"
                         "Mauris ultricies dolor sed massa convallis sed aliquet augue fringilla.\n"
                         "Duis erat eros, porta in accumsan in, blandit quis sem.\n"
                         "In hac habitasse platea dictumst. Etiam fringilla est id odio dapibus sit amet semper dui laoreet.\n");
        m_text.setFont(getFont());
        m_text.setCharacterSize(44);
        m_text.setPosition(30, 20);

        // Load the shader
//extern bool file_exists(const char * filename);
//    if (file_exists("shaders/wave.vert")) printf("exists!!!\n");

        if (!m_shader.loadFromFile("shaders/wave.vert", "shaders/blur.frag"))
            return false;

        return true;
    }

    void onUpdate(float time, float x, float y)
    {
        m_shader.setUniform("wave_phase", time);
        m_shader.setUniform("wave_amplitude", sf::Vector2f(x * 40, y * 40));
        m_shader.setUniform("blur_radius", (x + y) * 0.008f);
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.shader = &m_shader;
        target.draw(m_text, states);
    }

private:

    sf::Text m_text;
    sf::Shader m_shader;
};


////////////////////////////////////////////////////////////
// "Storm" vertex shader + "blink" fragment shader
////////////////////////////////////////////////////////////
class StormBlink : public Effect
{
public:

    StormBlink() :
    Effect("storm + blink")
    {
    }

    bool onLoad()
    {
        // Create the points
        m_points.setPrimitiveType(sf::Points);
        for (int i = 0; i < 40000; ++i)
        {
            float x = static_cast<float>(std::rand() % 1920);
            float y = static_cast<float>(std::rand() % 1080);
            sf::Uint8 r = std::rand() % 255;
            sf::Uint8 g = std::rand() % 255;
            sf::Uint8 b = std::rand() % 255;
            m_points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(r, g, b)));
        }

        // Load the shader
        if (!m_shader.loadFromFile("shaders/storm.vert", "shaders/blink.frag"))
            return false;

        return true;
    }

    void onUpdate(float time, float x, float y)
    {
        float radius = 200 + std::cos(time) * 150;
        m_shader.setUniform("storm_position", sf::Vector2f(x * 1920, y * 1080));
        m_shader.setUniform("storm_inner_radius", radius / 3);
        m_shader.setUniform("storm_total_radius", radius);
        m_shader.setUniform("blink_alpha", 0.5f + std::cos(time * 3) * 0.25f);
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.shader = &m_shader;
        target.draw(m_points, states);
    }

private:

    sf::VertexArray m_points;
    sf::Shader m_shader;
};


////////////////////////////////////////////////////////////
// "Edge" post-effect fragment shader
////////////////////////////////////////////////////////////
class Edge : public Effect
{
public:

    Edge() :
    Effect("edge post-effect")
    {
    }

    bool onLoad()
    {
        // Create the off-screen surface
        if (!m_surface.create(1920, 1080))
            return false;
        m_surface.setSmooth(true);

        // Load the textures
        if (!m_backgroundTexture.loadFromFile("shaders/sfml.png"))
            return false;
        m_backgroundTexture.setSmooth(true);
        if (!m_entityTexture.loadFromFile("shaders/devices.png"))
            return false;
        m_entityTexture.setSmooth(true);

        // Initialize the background sprite
        m_backgroundSprite.setTexture(m_backgroundTexture);
        m_backgroundSprite.setPosition(135, 100);

        // Load the moving entities
        for (int i = 0; i < 6; ++i)
        {
            sf::Sprite entity(m_entityTexture, sf::IntRect(96 * i, 0, 96, 96));
            m_entities.push_back(entity);
        }

        // Load the shader
        if (!m_shader.loadFromFile("shaders/edge.frag", sf::Shader::Fragment))
            return false;
        m_shader.setUniform("texture", sf::Shader::CurrentTexture);

        return true;
    }

    void onUpdate(float time, float x, float y)
    {
        m_shader.setUniform("edge_threshold", 1 - (x + y) / 2);

        // Update the position of the moving entities
        for (std::size_t i = 0; i < m_entities.size(); ++i)
        {
            sf::Vector2f position;
            position.x = std::cos(0.25f * (time * i + (m_entities.size() - i))) * (1920/2.0-96/2.0) + 1920/2.0-96/2.0;
            position.y = std::sin(0.25f * (time * (m_entities.size() - i) + i)) * (1080/2.0-96/2.0) + 1080/2.0-96/2.0;
            m_entities[i].setPosition(position);
        }

        // Render the updated scene to the off-screen surface
        m_surface.clear(sf::Color::White);
        m_surface.draw(m_backgroundSprite);
        for (std::size_t i = 0; i < m_entities.size(); ++i)
            m_surface.draw(m_entities[i]);
        m_surface.display();
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.shader = &m_shader;
        target.draw(sf::Sprite(m_surface.getTexture()), states);
    }

private:

    sf::RenderTexture m_surface;
    sf::Texture m_backgroundTexture;
    sf::Texture m_entityTexture;
    sf::Sprite m_backgroundSprite;
    std::vector<sf::Sprite> m_entities;
    sf::Shader m_shader;
};


extern int BITMAPSX;
extern int BITMAPSY;
extern int MAXGHOSTS;
extern int number;
extern int *pos_ghostx;
extern int *pos_ghosty;
////////////////////////////////////////////////////////////
// "Geometry" geometry shader example
////////////////////////////////////////////////////////////


sf::VertexArray m_pointCloud3(sf::Points,1);

extern sf::Vector2f fixit;
extern float scale_factor;

class Geometry3 : public Effect
{
public:

    Geometry3() :
        Effect("geometry shader billboards") //,  m_pointCloud(sf::Points, number)
//        Effect("geometry shader billboards"),
//        m_pointCloud(sf::Points, number)
    {
    }
    bool onLoad()
    {
        // Check if geometry shaders are supported
        if (!sf::Shader::isGeometryAvailable())
            return false;

        // Load the texture
        if (!m_logoTexture.loadFromFile("shaders/logo.png"))
            return false;

        // Load the shader

        if (!m_shader.loadFromFile("shaders/billboard3.vert", "shaders/billboard3.geom", "shaders/billboard3.frag"))
            return false;

        m_shader.setUniform("texture", texture_cube);
        m_shader.setUniform("resolution", sf::Vector2f(1920.0,1080.0));
        m_shader.setUniform("resolution_source_texture" , sf::Vector2f(texture_cube.getSize()) );
        m_shader.setUniform("wave_amplitude", sf::Vector2f(5.0, 5.0));

        return true;
    }


    void onUpdate(float time, float x, float y)
    {
        static float array[16];
        glhPerspectivef2(array, plot_all_fovyInDegrees, 1.0, plot_all_znear, plot_all_zfar);
        sf::Glsl::Mat4 matrix(array);
        m_shader.setUniform("perspective", matrix);

        m_transform = sf::Transform::Identity;

        m_shader.setUniform("wave_phase", (float) (fpstime));
        if ((plot_all==0 || handler[CANVAS_SELECT].show==0)) {
            m_shader.setUniform("draw_mode", (int)2); // radar
        } else {
            m_shader.setUniform("draw_mode", (int)2); // radar
        }
//        x=x*scale_factor;y=y*scale_factor;



        m_shader.setUniform("draw_scale", sf::Vector2f(x*scale_factor,y*scale_factor)); // scale BITMAPSX,BITMAPSY

        if (draw_model!=0 && plot_all)
            m_transform.scale( 1.0/(x),1.0/(y)).translate((1920.0*x/2.0-1920.0/2.0),(1080.0*y/2.0-1080.0/2.0)); // Better... looks more normal.
        else
            m_transform.scale( 1.0/(x),1.0/(y)).translate((1920.0*x/2.0-1920.0/2.0),(1080.0*y/2.0-1080.0/2.0)); // Better... looks more normal.


        m_shader.setUniform("iTime", (float) (fpstime/2.0));

        m_shader.setUniform("texture", texture_cube);

        m_shader.setUniform("size", sf::Vector2f(256.0,256.0));  // size texture in pixels.

        m_shader.setUniform("render_pos", sf::Vector2f(smooth_x,smooth_y));  // size texture in pixels.

//        m_shader.setUniform("render_pos", sf::Vector2f(render_picturex*1920-render_posx,render_picturey*1080-render_posy));  // size texture in pixels.

        sf::Glsl::Vec3 vector;
        vector.x=-plot_all_translate_x; vector.y=-plot_all_translate_y; vector.z=plot_all_translate_z;
        m_shader.setUniform("translate", vector);
        vector.x=0.0; vector.y=0.0; vector.z=shader_map_angle/180.0*PI;
//        vector.x=0.3*shader_map_angle/180.0*PI; vector.y=0.67*shader_map_angle/180.0*PI; vector.z=shader_map_angle/180.0*PI;
        vector.x+=plot_all_rotate_x/180.0*PI; vector.y+=plot_all_rotate_y/180.0*PI; vector.z+=plot_all_rotate_z/180.0*PI;
        m_shader.setUniform("rotate", vector); // radar
        m_shader.setUniform("draw_model", draw_model);
        m_shader.setUniform("fixit", fixit);
        m_shader.setUniform("iZoom", iZoom);


        int add=0;
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Prepare the render state

        states.shader = &m_shader;
        states.texture = &m_logoTexture;
        states.transform = m_transform;
   // Draw the point cloud
        target.draw(m_pointCloud3, states);
    }

private:

    sf::Texture m_logoTexture;
    sf::Transform m_transform;
    sf::Shader m_shader;
};


sf::VertexArray m_pointCloud(sf::Points,1);

class Geometry : public Effect
{
public:

    Geometry() :
        Effect("geometry shader billboards") //,  m_pointCloud(sf::Points, number)
//        Effect("geometry shader billboards"),
//        m_pointCloud(sf::Points, number)
    {
    }
    bool onLoad()
    {
        // Check if geometry shaders are supported
        if (!sf::Shader::isGeometryAvailable())
            return false;

        // Load the texture
        if (!m_logoTexture.loadFromFile("shaders/logo.png"))
            return false;

        // Load the shader

        if (!m_shader.loadFromFile("shaders/billboard.vert", "shaders/billboard.geom", "shaders/billboard.frag"))
            return false;
        if (yellow==1)
            m_shader.setUniform("texture", sfml_mazedot2);
        else
            m_shader.setUniform("texture", sfml_mazedot);
//        m_shader.setUniform("texture_from", sfml_mazedot);

        // Set the render resolution (used for proper scaling)
        m_shader.setUniform("resolution", sf::Vector2f(1920.0,1080.0));
        m_shader.setUniform("resolution_source_texture" , sf::Vector2f(sfml_mazedot.getSize()) );
        m_shader.setUniform("wave_amplitude", sf::Vector2f(5.0, 5.0));

        return true;
    }


    void onUpdate(float time, float x, float y)
    {
        static float array[16];
        glhPerspectivef2(array, plot_all_fovyInDegrees, 1.0, plot_all_znear, plot_all_zfar);
        sf::Glsl::Mat4 matrix(array);
        m_shader.setUniform("perspective", matrix);

        m_transform = sf::Transform::Identity;

        if (radar==1 && 0) {
                // scale = 1.0  normal screen drawing
                if (x>8.0) x=8.0;
                if (y>8.0) y=8.0;
                m_transform.scale( 1.0/(x),1.0/(y)).translate(1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0); // Better... looks more normal.
                m_shader.setUniform("draw_scale", sf::Vector2f(x,y));
                m_shader.setUniform("wave_phase", (float)0.0);
                m_shader.setUniform("draw_mode", (int)0); // main screen
                m_shader.setUniform("texture", sfml_mazedot2);
                m_shader.setUniform("size", sf::Vector2f(64.0-18.0,72.0-28.0));  // size texture in pixels.

        } else {
                // scale = 1.0/BITMAPSX,1.0/BITMAPSY radar screen drawing. draw_scale=BITMAPSX,BITMAPSY !!! (matrix = 1.0/(total number of screens to compress)
                m_shader.setUniform("wave_phase", (float) (fpstime));
                if (plot_all==0 || handler[CANVAS_SELECT].show==0) {
                    m_shader.setUniform("draw_mode", (int)1); // radar
                } else {
                    m_shader.setUniform("draw_mode", (int)2); // radar
                }
                m_shader.setUniform("draw_scale", sf::Vector2f(x,y)); // scale BITMAPSX,BITMAPSY
                if (draw_model!=0 && plot_all)
//koekoek
                    m_transform.scale( 1.0/(x),1.0/(y)).translate(1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0); // Better... looks more normal.
//                    m_transform.scale( 1.0/(x),1.0/(y)).translate(1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0+72.0); // Better... looks more normal.
                else
                    m_transform.scale( 1.0/(x),1.0/(y)).translate(1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0); // Better... looks more normal.
                m_shader.setUniform("iTime", (float) (fpstime/2.0));
                if (yellow==1)
                    m_shader.setUniform("texture", sfml_mazedot2);
                else
                    m_shader.setUniform("texture", sfml_mazedot);
        }
        m_shader.setUniform("render_pos", sf::Vector2f(smooth_x,smooth_y));  // size texture in pixels.
//        m_shader.setUniform("render_pos", sf::Vector2f(render_picturex*1920-render_posx,render_picturey*1080-render_posy));  // size texture in pixels.
        if (connected==1 && playerleft==0) m_shader.setUniform("num_pacman", 2); // multiplayer
        else m_shader.setUniform("num_pacman", 1);  // alone
//        m_shader.setUniform("size", sf::Vector2f(64.0-18.0,72.0-20.0));  // size texture in pixels.
//        m_shader.setUniform("size", sf::Vector2f(64.0,72.0));  // size texture in pixels.
        m_shader.setUniform("BITMAPS", sf::Vector2f(BITMAPSX,BITMAPSY));
        sf::Glsl::Vec3 vector;
        vector.x=-plot_all_translate_x; vector.y=-plot_all_translate_y; vector.z=plot_all_translate_z;
        m_shader.setUniform("translate", vector);
        vector.x=0.0; vector.y=0.0; vector.z=shader_map_angle/180.0*PI;
//        vector.x=0.3*shader_map_angle/180.0*PI; vector.y=0.67*shader_map_angle/180.0*PI; vector.z=shader_map_angle/180.0*PI;
        vector.x+=plot_all_rotate_x/180.0*PI; vector.y+=plot_all_rotate_y/180.0*PI; vector.z+=plot_all_rotate_z/180.0*PI;
        m_shader.setUniform("rotate", vector); // radar
        m_shader.setUniform("draw_model", draw_model);
//        m_shader.setUniform("iZoom", iZoom);

        int add=0;
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Prepare the render state

        states.shader = &m_shader;
        states.texture = &m_logoTexture;
        states.transform = m_transform;
   // Draw the point cloud
        target.draw(m_pointCloud, states);
    }

private:

    sf::Texture m_logoTexture;
    sf::Transform m_transform;
    sf::Shader m_shader;
};


class Geometry2 : public Effect
{
public:

    Geometry2() :
        Effect("geometry shader billboards") //,  m_pointCloud(sf::Points, number)
//        Effect("geometry shader billboards"),
//        m_pointCloud(sf::Points, number)
    {
    }
    bool onLoad()
    {
        // Check if geometry shaders are supported
        if (!sf::Shader::isGeometryAvailable())
            return false;

        // Load the texture
        if (!m_logoTexture.loadFromFile("shaders/logo.png"))
            return false;

        // Load the shader

        if (!m_shader.loadFromFile("shaders/billboard.vert", "shaders/billboard.geom", "shaders/billboard.frag"))
            return false;
        if (yellow==1)
            m_shader.setUniform("texture", sfml_mazedot2);
        else
            m_shader.setUniform("texture", sfml_mazedot);
//        m_shader.setUniform("texture_from", sfml_mazedot);

        // Set the render resolution (used for proper scaling)
        m_shader.setUniform("resolution", sf::Vector2f(1920.0,1080.0));
        m_shader.setUniform("resolution_source_texture" , sf::Vector2f(sfml_mazedot.getSize()) );
        m_shader.setUniform("wave_amplitude", sf::Vector2f(5.0, 5.0));

        return true;
    }


    void onUpdate(float time, float x, float y)
    {
        static float array[16];
        glhPerspectivef2(array, plot_all_fovyInDegrees, 1.0, plot_all_znear, plot_all_zfar);
        sf::Glsl::Mat4 matrix(array);
        m_shader.setUniform("perspective", matrix);

        m_transform = sf::Transform::Identity;

        if (radar==1) {
                // scale = 1.0  normal screen drawing
                if (x>8.0) x=8.0;
                if (y>8.0) y=8.0;
                m_transform.scale( 1.0/(x),1.0/(y)).translate(1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0); // Better... looks more normal.
                m_shader.setUniform("draw_scale", sf::Vector2f(x,y));
                m_shader.setUniform("wave_phase", (float)0.0);
                m_shader.setUniform("draw_mode", (int)0); // main screen
                m_shader.setUniform("texture", sfml_mazedot2);
                m_shader.setUniform("size", sf::Vector2f(64.0-9.0,72.0-10.0));  // size texture in pixels.
//                m_shader.setUniform("iZoom", (float)1.0);

        } else {
                // scale = 1.0/BITMAPSX,1.0/BITMAPSY radar screen drawing. draw_scale=BITMAPSX,BITMAPSY !!! (matrix = 1.0/(total number of screens to compress)
                m_shader.setUniform("wave_phase", (float) (fpstime));
                if (plot_all==0 || handler[CANVAS_SELECT].show==0) {
                    m_shader.setUniform("draw_mode", (int)1); // radar
                } else {
                    m_shader.setUniform("draw_mode", (int)2); // radar
                }
                m_shader.setUniform("draw_scale", sf::Vector2f(x,y)); // scale BITMAPSX,BITMAPSY
                m_transform.scale(1.0/(x),1.0/(y)).translate(1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0); // Better... looks more normal.
                m_shader.setUniform("iTime", (float) (fpstime/2.0));
                if (yellow==1)
                    m_shader.setUniform("texture", sfml_mazedot2);
                else
                    m_shader.setUniform("texture", sfml_mazedot);
//                m_shader.setUniform("iZoom", iZoom);
        }
        m_shader.setUniform("render_pos", sf::Vector2f(smooth_x,smooth_y));  // size texture in pixels.
//        m_shader.setUniform("render_pos", sf::Vector2f(render_picturex*1920-render_posx,render_picturey*1080-render_posy));  // size texture in pixels.
        if (connected==1 && playerleft==0) m_shader.setUniform("num_pacman", 2); // multiplayer
        else m_shader.setUniform("num_pacman", 1);  // alone
//        m_shader.setUniform("size", sf::Vector2f(64.0-18.0,72.0-20.0));  // size texture in pixels.
//        m_shader.setUniform("size", sf::Vector2f(64.0,72.0));  // size texture in pixels.
        m_shader.setUniform("BITMAPS", sf::Vector2f(BITMAPSX,BITMAPSY));
        sf::Glsl::Vec3 vector;
        vector.x=-plot_all_translate_x; vector.y=-plot_all_translate_y; vector.z=plot_all_translate_z;
        m_shader.setUniform("translate", vector);
        vector.x=0.0; vector.y=0.0; vector.z=shader_map_angle/180.0*PI;
//        vector.x=0.3*shader_map_angle/180.0*PI; vector.y=0.67*shader_map_angle/180.0*PI; vector.z=shader_map_angle/180.0*PI;
        vector.x+=plot_all_rotate_x/180.0*PI; vector.y+=plot_all_rotate_y/180.0*PI; vector.z+=plot_all_rotate_z/180.0*PI;
        m_shader.setUniform("rotate", vector); // radar
        m_shader.setUniform("draw_model", draw_model);

        int add=0;
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // Prepare the render state

        states.shader = &m_shader;
        states.texture = &m_logoTexture;
        states.transform = m_transform;
   // Draw the point cloud
        target.draw(m_pointCloud, states);
    }

private:

    sf::Texture m_logoTexture;
    sf::Transform m_transform;
    sf::Shader m_shader;
};


extern sf::VertexArray m_pointCloud_maps[2][2];
extern sf::VertexArray m_pointCloud_map0;
extern sf::VertexArray m_hoppa;
int mappos_x,mappos_y;
extern sf::VertexArray m_pointCloud_map1;


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
std::vector<Effect*> effects;
std::size_t current = 4;

extern void ShowTaskBar(bool show);

Effect* mapper_effect;
Effect* cube_effect;

extern int blank_maze;
extern void update_map(int totalx, int totaly);
extern int ffmpegfile;
extern int internetfile;
extern float the_time;
extern int shade_main;
extern sf::RenderTexture texture_final;
extern int blending;
extern sf::RenderStates picture_states;
extern int blendit;

extern sf::BlendMode MyBlendingMode;
sf::Vector3f check_to_plot(int mappos_x, int mappos_y);
extern int F2;
//    if (F2==1) check_to_plot(x,y);


struct Interval
{
    glm::vec3 plot_all_pos_out;
    glm::ivec2 plot_all_pos_in;
};

Interval myInterval[450];

int plot_all_count=0;
void shader_map(int x,int y);

bool compareInterval(const Interval &i1, const Interval &i2)
{
    return (i1.plot_all_pos_out.z < i2.plot_all_pos_out.z);
}
extern void RenderBlit2(float xdest, float ydest, int xsource, int ysource, int width, int height);

#include<bits/stdc++.h>
//using namespace std;
void plot_it(int plot_front) {

/*
    if (F2==1) {
        printf("BEFORE:\n");
        for (int cnt=0; cnt<plot_all_count; cnt++) {
            printf("mx=%2d,my=%2d px=%f,py=%f,pz=%f\n",
                   myInterval[cnt].plot_all_pos_in.x,myInterval[cnt].plot_all_pos_in.y,
                   myInterval[cnt].plot_all_pos_out.x,myInterval[cnt].plot_all_pos_out.y,myInterval[cnt].plot_all_pos_out.z
                   );
        }
    }
*/

    if (plot_front==0)
        std::sort(myInterval,myInterval+plot_all_count,compareInterval);

/*
    if (F2==1) {
        printf("AFTER:\n");
        for (int cnt=0; cnt<plot_all_count; cnt++) {
            printf("mx=%2d,my=%2d px=%f,py=%f,pz=%f\n",
                   myInterval[cnt].plot_all_pos_in.x,myInterval[cnt].plot_all_pos_in.y,
                   myInterval[cnt].plot_all_pos_out.x,myInterval[cnt].plot_all_pos_out.y,myInterval[cnt].plot_all_pos_out.z
                   );
        }
    }
*/
//    static int cc=60;
//    if (plot_front==0) cc--;
//    if (cc==0) {
//        if (plot_front==0) printf("plot=%d: ",plot_front);
//        else printf("   plot=%d: ",plot_front);
//    }
    for (int cnt=0; cnt<plot_all_count; cnt++) {
        if ((plot_front==1 && myInterval[cnt].plot_all_pos_out.z>-1.0) || (plot_front==0 && myInterval[cnt].plot_all_pos_out.z<=-1.0) ) {
            shader_map(myInterval[cnt].plot_all_pos_in.x,myInterval[cnt].plot_all_pos_in.y);
//            if (cc==0) printf("(%d=%3.2f)",cnt,myInterval[cnt].plot_all_pos_out.z);
        }

/*
        extern sf::Sprite spritedot;
        extern sf::Sprite spritedot2;
        spritedot.setScale(1.0/myInterval[cnt].plot_all_pos_out.z,1.0/myInterval[cnt].plot_all_pos_out.z);
        spritedot2.setScale(1.0/myInterval[cnt].plot_all_pos_out.z,1.0/myInterval[cnt].plot_all_pos_out.z);
        RenderBlit2(  (1.0+myInterval[cnt].plot_all_pos_out.x)*(960.0)-23/myInterval[cnt].plot_all_pos_out.z,
                      (1.0-myInterval[cnt].plot_all_pos_out.y)*(540.0)-26/myInterval[cnt].plot_all_pos_out.z,
                      9,
                      72+10,
                      64-18,
                      72-20);
        spritedot.setScale(1.0,1.0);
        spritedot2.setScale(1.0,1.0);
*/
    }
    if (plot_front==1) {
        plot_all_count=0;
//        if (cc==0) {
//            cc=60;
//            printf("\n");
//        }
    }
}

void shader_map_init(int x,int y) {
    sf::Vector3f ret;
    myInterval[plot_all_count].plot_all_pos_in=glm::ivec2(x,y);
    ret=check_to_plot(x,y);
    myInterval[plot_all_count].plot_all_pos_out=glm::vec3(ret.x,ret.y,ret.z);
    plot_all_count++;
}

void shader_map(int x,int y) {
//    update_map(x,y);
    if (handler[CANVAS_SELECT].show==0) return;
    mappos_x=x;mappos_y=y;

    if (plot_all==1 || plot_cubes==1)
//    if (internetfile==0)
        mapper_effect->update(the_time, 1.0/sprite_from_canvas.getScale().x, 1.0/sprite_from_canvas.getScale().y);
//        mapper_effect->update(the_time, 1.0/sprite_from_internet.getScale().x, 1.0/sprite_from_internet.getScale().y);
    else
        mapper_effect->update(the_time, 1.0, 1.0);


    if (blending>=1 || shade_main!=0 || blendit==1) {
//        if ((blending>=1 && handler[INTERNET_SELECT].blending==0) || handler[INTERNET_SELECT].blending>=1) {
//            if (blending<2 && handler[INTERNET_SELECT].blending==2) {
        if ((blending>=1 && handler[CANVAS_SELECT].blending==0) || handler[CANVAS_SELECT].blending>=1) {
            if (blending<2 && handler[CANVAS_SELECT].blending==2) {
                sf::BlendMode old_mode=picture_states.blendMode;
                picture_states.blendMode=MyBlendMode[4];
                texture_final.draw(*mapper_effect,picture_states);
                picture_states.blendMode=old_mode;
            } else
                texture_final.draw(*mapper_effect,picture_states);
        } else {
            texture_final.draw(*mapper_effect);
//            texture_final.draw(*mapper_effect,picture_states);
        }
    }
    else SFMLView1.draw(*mapper_effect);
}

int mul_mat(int m, int n, float *first, int p, int q, float *second, float *multiply);
extern int CapsLock;

class MAPPER : public Effect
{
public:

    MAPPER() : Effect("MAPPER") {}
    bool onLoad() {
        if (!sf::Shader::isGeometryAvailable()) return false;
        if (!m_logoTexture.loadFromFile("shaders/logo.png")) return false;
        m_logoTexture.generateMipmap();
        if (!m_shader.loadFromFile("shaders/billboard2.vert", "shaders/billboard2.geom", "shaders/billboard2.frag")) return false;
        m_shader.setUniform("resolution", sf::Vector2f(1920.0,1080.0));
//        m_shader.setUniform("resolution_source_texture" , sf::Vector2f(sfml_mazedot.getSize()) );
        return true;
    }


    void onUpdate(float time, float x, float y)
    {

        static float array[16];
        glhPerspectivef2(array, plot_all_fovyInDegrees, 1.0, plot_all_znear, plot_all_zfar);
        sf::Glsl::Mat4 matrix(array);
        m_shader.setUniform("perspective", matrix);

        m_transform = sf::Transform::Identity;
        m_shader.setUniform("iTime", (float) (fpstime/2.0));

        static int old_position_y;
        int arx,ary;
        if (draw_model==6) {
            old_position_y=(render_picturey*1080-render_posy);
            int position_y=old_position_y;
            if (CapsLock==1)
                arx=1;
            else
                arx=0;
//            render_posx=0+960+(mappos_x)*500;
//            render_posx=0+960;//+(mappos_x)*500;
//            render_posx=0+960-(mappos_x+0.5)*500;
//            render_posx=0-(mappos_x+0.5)*500;
            render_posx=0-(mappos_x)*500;
            render_picturex=(mappos_x+BITMAPSX)%BITMAPSX;

//            int position_x=0-(mappos_x+0.5)*500+mappos_x*1920;
//            position_x=(position_x+maxpixelsx)%maxpixelsx;
//            render_picturex=position_x/1920;
//            render_posx=position_x-1920*render_picturex;
//            render_posx=-render_posx;


//            extra_y=fpstime*(mappos_y+2);
//            position_y+=1080*(mappos_x+2);
extern int y_bar[];
            position_y=y_bar[mappos_x+2];

//            position_y+=(2160+160*fpstime)*(mappos_x+2);
            position_y=(position_y+maxpixelsy)%maxpixelsy;
            render_picturey=position_y/1080;
            render_posy=position_y-1080*render_picturey;
            render_posy=-render_posy;
        } else {
            arx=(render_picturex+mappos_x+BITMAPSX)%BITMAPSX;
        }
        ary=(render_picturey+mappos_y+BITMAPSY)%BITMAPSY;
        int flash;
        if ( sin(5.0*fpstime*3.1415)>0.0 && ( (ary+(int)mappos_x+20+(int)(fpstime/2.0)%6)%(1+(int)(fpstime)%4)==0  || (ary+(int)(fpstime/4.0)%3)%(1+20+(int)mappos_x+(int)(fpstime)%5)==0 ) ) flash=1;
        else flash=0;
        m_shader.setUniform("flash", flash); // scale BITMAPSX,BITMAPSY


        float offsetx;
        float offsety;
        if (draw_model==0) {
            offsetx=(float)mappos_x*1920.0+(float)render_posx-(float)smooth_x+(float)((int)smooth_x);
            offsety=(float)mappos_y*1080.0+(float)render_posy-(float)smooth_y+(float)((int)smooth_y);
        } else {
            offsetx=(float)mappos_x*1920.0+(float)render_posx-(float)smooth_x+(float)((int)smooth_x);
            offsety=72+1080.0+(float)mappos_y*1080.0+(float)render_posy-(float)smooth_y+(float)((int)smooth_y);
        }

//        m_transform.scale( 1.0,1.0).translate(0.0,0.0);

//        m_transform.
//            scale( 1.0/(x),-1.0/(y)).
//            translate((offsetx+1920.0*x/2.0-1920.0/2.0),(-offsety-1080.0*y/2.0+1080.0/2.0)); // Better... looks more normal.

        m_transform.
            scale( 1.0,1.0).
            translate(0.0,0.0); // Better... looks more normal.

//        m_shader.setUniform("ar", sf::Vector2f((float)arx,(float)ary) ); // total map, BITMAPSX x BITMAPSY;
//        m_shader.setUniform("mappos", sf::Vector2f((float)mappos_x+3.0,(float)mappos_y+3.0) ); // plot_all 8x8

        m_shader.setUniform("draw_scale", sf::Vector2f(x,-y)); // scale BITMAPSX,BITMAPSY

        m_shader.setUniform("draw_translate",  sf::Vector2f( (offsetx+1920.0*x/2.0-1920.0/2.0),(-offsety-1080.0*y/2.0+1080.0/2.0) ) );

        m_shader.setUniform("render_pos", sf::Vector2f(render_picturex*1920-render_posx,render_picturey*1080-render_posy));  // size texture in pixels.

//        m_shader.setUniform("BITMAPS", sf::Vector2f(BITMAPSX,BITMAPSY));

//slots
        if (draw_model==6) {
            render_picturey=old_position_y/1080;
            render_posy=old_position_y-1080*render_picturey;
            render_posy=-render_posy;
        }

        m_shader.setUniform("texture_plot", texturemaxinmempoint[used2[arx][ary]]->getTexture());
        m_shader.setUniform("texture_plot2", texturemaxinmempoint[used2[0][ary]]->getTexture());

        int add=0;

//        float radius = .600 + std::cos(time) * .450;
        float xx = static_cast<float>(sf::Mouse::getPosition(SFMLView1).x) / SFMLView1.getSize().x;
        float yy = static_cast<float>(sf::Mouse::getPosition(SFMLView1).y) / SFMLView1.getSize().y;
//        m_shader.setUniform("storm_position", sf::Vector2f(xx-0.5 , -yy+0.5 ));

        sf::Glsl::Vec3 vector;

        vector.x=-plot_all_translate_x; vector.y=-plot_all_translate_y; vector.z=plot_all_translate_z;
        m_shader.setUniform("translate", vector);

        vector.x=0.0; vector.y=0.0; vector.z=shader_map_angle/180.0*PI;
        vector.x+=plot_all_rotate_x/180.0*PI; vector.y+=plot_all_rotate_y/180.0*PI; vector.z+=plot_all_rotate_z/180.0*PI;
        m_shader.setUniform("rotate", vector);

        m_shader.setUniform("draw_model", draw_model);
        if (draw_model==0) {
            m_shader.setUniform("size", sf::Vector2f(1920.0,1080.0));  // size texture in pixels.
        } else {
            m_shader.setUniform("size", sf::Vector2f(64.0,72.0));  // size texture in pixels.
        }
//        m_shader.setUniform("iZoom", iZoom);
    }

    void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.shader = &m_shader;
//        int arx=(render_picturex+mappos_x+BITMAPSX)%BITMAPSX;
//        int ary=(render_picturey+mappos_y+BITMAPSY)%BITMAPSY;
        states.texture = &m_logoTexture;
        states.transform = m_transform;
        if (draw_model==0)
            target.draw(m_pointCloud_map1, states);
        else
            target.draw(m_pointCloud_map0, states);
//        target.draw(m_pointCloud_maps[mappos_x][mappos_y], states);
    }

private:
    sf::Texture m_logoTexture;
    sf::Transform m_transform;
    sf::Shader m_shader;
};


void set_mapper() {
    static int first=1;
    if (first==1) mapper_effect = new MAPPER;
    first=0;
    mapper_effect->load();
}

void set_cube() {
    static int first=1;
    if (first==1) cube_effect = new Geometry3;
    first=0;
    cube_effect->load();
}


void mul_mat2( int row1, int col1, float *a,  int row2, int col2, float *b, float *d);

sf::Vector3f make_vertex(sf::Vector2f pos);
float * pers;
float array_perspective2[16];
float array_rotate[16];

int ok;

float * array_rotx_glob;
float * array_roty_glob;
float * array_rotz_glob;
sf::Glsl::Mat4 * matrix_glob;
glm::mat4 Projection(1.0f);
glm::mat4 rotateXYZ;
glm::mat4 translateXYZ;
sf::Vector2f draw_scale;
float aspect;

glm::vec2 render_pos;
float iTime;

sf::Vector3f check_to_plot(int mappos_x, int mappos_y) {
    float x,y;

    if (plot_all==1) {
        x=1.0/sprite_from_canvas.getScale().x;
        y=1.0/sprite_from_canvas.getScale().y;
    } else {
        x=1.0;
        y=1.0;
    }
    iTime=fpstime/2.0;
    render_pos=glm::vec2(render_picturex*1920-render_posx,render_picturey*1080-render_posy);

    sf::Vector2f offset;
    if (draw_model==0) {
        offset.x=(float)mappos_x*1920.0+(float)render_posx-(float)smooth_x+(float)((int)smooth_x);
        offset.y=1080.0+(float)mappos_y*1080.0+(float)render_posy-(float)smooth_y+(float)((int)smooth_y);
    } else {
        offset.x=(float)mappos_x*1920.0+(float)render_posx-(float)smooth_x+(float)((int)smooth_x);
        offset.y=-72+1080.0+(float)mappos_y*1080.0+(float)render_posy-(float)smooth_y+(float)((int)smooth_y);
    }

    draw_scale.x=x;
    draw_scale.y=-y;

    sf::Vector2f draw_translate;
    draw_translate=sf::Vector2f(offset.x+1920.0*x/2.0-1920.0/2.0,-offset.y-1080.0*y/2.0+1080.0/2.0) ;

    sf::VertexArray m_pointCloud_map;
    int xn,yn;
    sf::Vector2f size;
    float xnn,ynn;
    if (draw_model==0) {
        xn=1;yn=1;
        xnn=0.5;ynn=0.5;
        m_pointCloud_map=m_pointCloud_map1;
        size.x=1920.0;size.y=1080.0;
    } else {
        xn=30;yn=15;
        xnn=15.0;ynn=7.5;
        m_pointCloud_map=m_pointCloud_map0;
//        printf("size=%d\n",m_pointCloud_map.getVertexCount());
        size.x=64.0;size.y=72.0;
    }

    sf::Vector3f rotate;
    rotate.x=0.0;
    rotate.y=0.0;
    rotate.z=  shader_map_angle*PI/180.0;
    rotate.x+=plot_all_rotate_x*PI/180.0;
    rotate.y+=plot_all_rotate_y*PI/180.0;
    rotate.z+=plot_all_rotate_z*PI/180.0;

    sf::Vector3f c;
    sf::Vector3f s;

    c.x = (float)cos(rotate.x);
    s.x = (float)sin(rotate.x);
    c.y = (float)cos(rotate.y);
    s.y = (float)sin(rotate.y);
    c.z = (float)cos(rotate.z);
    s.z = (float)sin(rotate.z);

    aspect = 1920.0 / 1080.0;

    rotateXYZ =
    glm::mat4(  glm::vec4(1,          0,           0, 0),
                glm::vec4(0,        c.x, -s.x/aspect, 0),
                glm::vec4(0, s.x*aspect,         c.x, 0),
                glm::vec4(0,          0,           0, 1) ) *
    glm::mat4(  glm::vec4( c.y, 0, s.y, 0),
                glm::vec4(   0, 1,   0, 0),
                glm::vec4(-s.y, 0, c.y, 0),
                glm::vec4(   0, 0,   0, 1)               ) *
    glm::mat4(  glm::vec4(       c.z, -s.z*aspect, 0, 0),
                glm::vec4(s.z/aspect,         c.z, 0, 0),
                glm::vec4(         0,           0, 1, 0),
                glm::vec4(         0,           0, 0, 1  ) );



    float array_rotx[9] =    {  1,          0,  0,          0,c.x,-s.x/aspect,    0,s.x*aspect,c.x};
    float array_roty[9] =    {c.y,          0,s.y,          0,  1,          0, -s.y,         0,c.y};
    float array_rotz[9] =    {c.z,-s.z*aspect,  0, s.z/aspect,c.z,          0,    0,         0,  1};
    array_rotx_glob=array_rotx;
    array_roty_glob=array_roty;
    array_rotz_glob=array_rotz;
    float array_between[16];
    mul_mat2(3,3,array_rotz,3,3,array_roty,array_between);
    mul_mat2(3,3,array_between,3,3,array_rotx,array_rotate);

    Projection = glm::perspective(plot_all_fovyInDegrees, 1.0f, plot_all_znear, plot_all_zfar);
//    Projection = glm::perspective(glm::radians(plot_all_fovyInDegrees), 1.0f, plot_all_znear, plot_all_zfar);
//    Projection *= glm::ortho(0.0f, 1.0f, 1.0f, 0.0f, (GLfloat)plot_all_znear, (GLfloat)plot_all_zfar);
    static float array_perspective[16];

    glhPerspectivef2(array_perspective, plot_all_fovyInDegrees, 1.0, plot_all_znear, plot_all_zfar);
    pers=array_perspective;

    translateXYZ=glm::translate(glm::mat4(),glm::vec3(-plot_all_translate_x/100.0, -plot_all_translate_y/100.0, plot_all_translate_z/100.0-1.0f));

    sf::Glsl::Mat4 matrix(array_perspective);
    matrix_glob=&matrix;

    Model_pers[0] = glm::vec4(array_perspective[0], array_perspective[1], array_perspective[2], array_perspective[3]);
    Model_pers[1] = glm::vec4(array_perspective[4], array_perspective[5], array_perspective[6], array_perspective[7]);
    Model_pers[2] = glm::vec4(array_perspective[8], array_perspective[9], array_perspective[10],array_perspective[11]);
    Model_pers[3] = glm::vec4(array_perspective[12],array_perspective[13],array_perspective[14],array_perspective[15]);

    sf::Vector2f resolution;
    resolution.x=1920.0;
    resolution.y=1080.0;

    sf::Vector2f half_size;
    half_size.x = 2.0*size.x/(resolution.x*draw_scale.x);
    half_size.y = 2.0*size.y/(resolution.y*draw_scale.y);

    sf::Vector3f Position1;
    sf::Vector3f Position2;
    sf::Vector3f Position3;
    sf::Vector3f Position4;

    sf::Vector2f pos;

    sf::Vector2f coord;
    coord.x=(1.0+(m_pointCloud_map[0].position.x)) * resolution.x/2.0;
    coord.y=(1.0-(m_pointCloud_map[0].position.y)) * resolution.y/2.0;

    sf::Vector2f adapt;
    adapt.x= ((1.0+2.0*(draw_translate.x/resolution.x)) / draw_scale.x - 1.0);
    adapt.y=-((1.0+2.0*(draw_translate.y/resolution.y)) / draw_scale.y - 1.0);

    sf::VertexArray mycalc(sf::LineStrip, 5);
    int cloud_pos=0;

/*

    if (blending>=1 || shade_main!=0 || blendit==1)
    {
//        texture_final.pushGLStates();
        texture_final.setActive(true);
        texture_final.setActive(false);
    }
    else
    {
//        SFMLView1.pushGLStates();
        SFMLView1.setActive(true);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        SFMLView1.setActive(false);
    }
*/
//        glDisable(GL_DEPTH_TEST);
//        glDepthMask(GL_FALSE);


/*
    for (int y1=0;y1<yn;y1++) {
        for (int x1=0;x1<xn;x1++) {
//            float x1=xnn;
//            float y1=ynn;

            ok=0;
            pos.x = 2.0*(((float)x1*size.x/1920.0-0.5) / draw_scale.x) + adapt.x;
            pos.y = 2.0*(((float)y1*size.y/1080.0-0.5) / draw_scale.y) + adapt.y;

//            pos.x = 2.0*((m_pointCloud_map[cloud_pos].position.x/1920.0-0.5) / draw_scale.x) + adapt.x;
//            pos.y = 2.0*((m_pointCloud_map[cloud_pos].position.y/1080.0-0.5) / draw_scale.y) + adapt.y;

            Position1 = make_vertex(sf::Vector2f(pos.x + half_size.x*0.99, pos.y));
            Position2 = make_vertex(pos);
            Position3 = make_vertex(sf::Vector2f(pos.x + half_size.x*0.99f, pos.y + half_size.y*0.99f));
            Position4 = make_vertex(sf::Vector2f(pos.x , pos.y + half_size.y*0.99));

            mycalc[0].position.x=(1.0+Position2.x)*(960.0);
            mycalc[0].position.y=(1.0-Position2.y)*(540.0);
            mycalc[0].color=sf::Color(255,0,0,255);

            mycalc[1].position.x=(1.0+Position1.x)*(960.0);
            mycalc[1].position.y=(1.0-Position1.y)*(540.0);
            mycalc[1].color=sf::Color(255,255,0,255);

            mycalc[2].position.x=(1.0+Position3.x)*(960.0);
            mycalc[2].position.y=(1.0-Position3.y)*(540.0);
            mycalc[2].color=sf::Color(255,255,255,255);

            mycalc[3].position.x=(1.0+Position4.x)*(960.0);
            mycalc[3].position.y=(1.0-Position4.y)*(540.0);
            mycalc[3].color=sf::Color(255,0,255,255);

            mycalc[4].position.x=(1.0+Position2.x)*(960.0);
            mycalc[4].position.y=(1.0-Position2.y)*(540.0);
            mycalc[4].color=sf::Color(255,0,0,255);

            sf::BlendMode old_mode=picture_states.blendMode;
            picture_states.blendMode=sf::BlendAlpha;

            if (blending>=1 || shade_main!=0 || blendit==1)
                texture_final.draw(mycalc,picture_states);
            else
                SFMLView1.draw(mycalc,picture_states);
            picture_states.blendMode=old_mode;

            cloud_pos++;
        }
    }
*/

//        glEnable(GL_DEPTH_TEST);
//        glDepthMask(GL_TRUE);

/*
    if (blending>=1 || shade_main!=0 || blendit==1)
    {
        texture_final.setActive(true);
//        texture_final.popGLStates();
        texture_final.setActive(false);
    }
    else
    {
        SFMLView1.setActive(true);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
//        SFMLView1.popGLStates();
        SFMLView1.setActive(false);
    }

*/

    pos.x = 2.0*((xnn*size.x/1920.0-0.5) / draw_scale.x) + adapt.x;
    pos.y = 2.0*((ynn*size.y/1080.0-0.5) / draw_scale.y) + adapt.y;
    Position1 = make_vertex(pos);
/*
    extern sf::Sprite spritedot;
    extern sf::Sprite spritedot2;
    spritedot.setScale(1.0/Position1.z,1.0/Position1.z);
    spritedot2.setScale(1.0/Position1.z,1.0/Position1.z);
    RenderBlit2(  (1.0+Position1.x)*(960.0)-23/Position1.z,
                  (1.0-Position1.y)*(540.0)-26/Position1.z,
                  9,
                  72+10,
                  64-18,
                  72-20);
    spritedot.setScale(1.0,1.0);
    spritedot2.setScale(1.0,1.0);
*/
//    m_transform = sf::Transform::Identity;
//    m_transform.scale( .99999/(x),-0.99999/(y)).translate(0.9999*(offsetx+1920.0*x/2.0-1920.0/2.0),0.9999*(-offsety-1080.0*y/2.0+1080.0/2.0)); // Better... looks more normal.
    return Position1;
}


sf::Vector3f make_vertex(sf::Vector2f pos) {
    float aspect = 1920.0 / 1080.0;

    sf::Vector3f vertex;
    glm::vec4 myVector;
    glm::vec4 myVector2;
    myVector=glm::vec4(pos.x,pos.y,0.0f,1.0f);

    switch(draw_model){
        case 0 : {
            break;
        }
        case 1 : {
            myVector.z = cos(myVector.x*draw_scale.x*PI/8.0)/draw_scale.x*2.5;
            myVector.x = sin(myVector.x*draw_scale.x*PI/8.0)/draw_scale.x*2.5;
            break;
        }
        case 2 : {
            myVector.z = cos(myVector.x*draw_scale.x*PI/8.0)/draw_scale.x*2.5;
            myVector.x = sin(myVector.x*draw_scale.x*PI/8.0)/draw_scale.x*2.5;

            myVector.x = myVector.x-2.0/draw_scale.x*2.5;
            myVector2  = myVector;

            myVector.y = myVector2.x*sin(myVector2.y*draw_scale.y*PI/8.0)*aspect;
            myVector.x = myVector2.x*cos(myVector2.y*draw_scale.y*PI/8.0);
            myVector.z = myVector2.z;

            break;
        }
        case 3 : {
            myVector.z += (   sin(    .5*(myVector.x    +render_pos.x/(960.0*draw_scale.x))*draw_scale.x*PI/.5+iTime*2.0   )
                           +  cos(   -.5*(myVector.y    +render_pos.y/(540.0*draw_scale.y))*draw_scale.y*PI/.5+iTime*2.4   )   )/draw_scale.x/10.0;
            myVector.z += (   sin(   .33*(myVector.x/2.0+render_pos.x/(960.0*draw_scale.x))*draw_scale.x*PI/.5+iTime*.97   )
                           +  cos(  -.29*(myVector.y/2.0+render_pos.y/(540.0*draw_scale.y))*draw_scale.y*PI/.5+iTime*1.022 )   )/draw_scale.x/5.0;
            break;
        }
        case 4 : {
            myVector.z = cos(-myVector.y*draw_scale.y*PI/8.0)/draw_scale.x*2.5;
            myVector.y = sin( myVector.y*draw_scale.y*PI/8.0)/draw_scale.y*2.5;
            myVector.y = myVector.y-2.0/draw_scale.y*2.5;
            myVector2  = myVector;

            myVector.x = myVector2.y*sin(myVector2.x*draw_scale.x*PI/8.0)*aspect;
            myVector.y = myVector2.y*cos(myVector2.x*draw_scale.x*PI/8.0);
            myVector.z = myVector2.z;

            break;
        }
        case 5 : {
//            myVector.z = cos(myVector.x*draw_scale.x*PI/8.0)/draw_scale.x*2.5;
//            myVector.x = sin(myVector.x*draw_scale.x*PI/8.0)/draw_scale.x*2.5;



            myVector.z =  -cos(myVector.x*draw_scale.x*PI/32.0)/draw_scale.x*2.5;
            myVector.z += cos(myVector.y*draw_scale.y*PI/32.0)/draw_scale.y*2.5;
            myVector.x = sin(myVector.x*draw_scale.x*PI/64.0)/draw_scale.x*5.0;
            myVector.y = sin(myVector.y*draw_scale.y*PI/32.0)/draw_scale.y*2.5;

            break;
        }
//slots
        case 6 : {
            myVector.z = -cos(myVector.y*draw_scale.y*PI/20.0)/draw_scale.y*6.0/aspect;
            myVector.y = sin(myVector.y*draw_scale.y*PI/20.0)/draw_scale.y*6.0;
            break;
        }

    }

    myVector=rotateXYZ*myVector;

    myVector=myVector+glm::vec4(-plot_all_translate_x/100.0f, -plot_all_translate_y/100.0f, plot_all_translate_z/100.0f,0.0f );
    myVector.z-=1.0f;
    myVector.w=1.0;

    float z=myVector.z;

//    myVector=Model_pers*myVector;
    myVector=myVector*Model_pers;
    myVector.x=myVector.x/(myVector.w);
    myVector.y=myVector.y/(myVector.w);
//    myVector.z=myVector.z/(myVector.w);
//    myVector.z=myVector.w;

    vertex.x=(float)myVector.x*iZoom;
    vertex.y=(float)myVector.y*iZoom;
//    vertex.z=(float)myVector.z;
    vertex.z=z;

    if (vertex.z > -0.4 -0.5 && vertex.z < 5.0) ok=1;
    return vertex;
}

void mul_mat2( int row1, int col1, float *a,  int row2, int col2, float *b, float *d)
{
    assert(col1 == row2);

    int size = row1*col2;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            float sum = 0.0;
            for (int k = 0; k < col1; k++)
                sum = sum + a[i * col1 + k] * b[k * col2 + j];
            d[i * col2 + j] = sum;
        }
    }

/*
    for (int i = 0; i < size; i++) {
        if (i % col2 == 0) {
            printf("\n");
        }
        printf("%d ", d[i]);
    }
*/
}

int mul_mat(int row1, int col1, float *first, int row2, int col2, float *second, float *multiply)
{
  int r, c;
  int r1,c1,r2,c2,k;
  float sum = 0.0;
//  int first[10][10], second[10][10], multiply[10][10];
//  printf("Enter number of rows and columns of first matrix\n");
//  scanf("%d%d", &row1, &col1);
//  printf("Enter elements of first matrix\n");

//  for (r = 0; r < row1; r++)         //row
//    for (c = 0; c < col1; c++)       //column
//      scanf("%d", &first[r][c]);


//  printf("Enter number of rows and columns of second matrix\n");
//  scanf("%d%d", &row2, &col2);

  if (col1 != row2)
    printf("The matrices can't be multiplied with each other.\n");
  else
  {
//    printf("Enter elements of second matrix\n");

//    for (r = 0; r < row2; r++)
//      for (c = 0; c < col2; c++)
//        scanf("%d", &second[r][c]);

    for (r1 = 0; r1 < row1; r1++) {
      for (c2 = 0; c2 < col2; c2++) {
        for (r2 = 0; r2 < row2; r2++) {
          sum = sum + first[r1*col1+r2]*second[r2*col2+c2];
//          sum = sum + first[r1][r2]*second[r2][c2];
//          sum = sum + first[c][k]*second[k][d];
        }

        multiply[r1*col1+c2] = sum;
//        multiply[r1][c2] = sum;
//        multiply[c][d] = sum;
        sum = 0.0;
      }
    }
//    printf("Product of the matrices:\n");

//    for (c = 0; c < m; c++) {
//      for (d = 0; d < q; d++)
//        printf("%d\t", multiply[c][d]);

//      printf("\n");
//    }
  }

  return 0;
}


int shaders()
{
    static sf::Vector2u old_size=( sf::Vector2u(1920/3,1080/3) );
    static sf::Vector2i old_pos=( sf::Vector2i(100,100) );
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::ContextSettings contextSettings(0,0,2,3,0);
    contextSettings.antialiasingLevel = 0;
    shader_window.create(sf::VideoMode(1920,1080), "Shaders", sf::Style::Resize,contextSettings);
    shader_window.setSize(old_size);
    shader_window.setPosition(old_pos);
    shader_window.setVerticalSyncEnabled(true);
//    shader_window.setVerticalSyncEnabled(false);

    sf::Font font;
    if (!font.loadFromFile("shaders/sansation.ttf"))
        return EXIT_FAILURE;
    Effect::setFont(font);
    effects.push_back(new Pixelate);
    effects.push_back(new WaveBlur);
    effects.push_back(new StormBlink);
    effects.push_back(new Edge);
    effects.push_back(new Geometry);
    effects.push_back(new Geometry2);
    effects.push_back(new MAPPER);
    for (std::size_t i = 0; i < effects.size(); ++i) effects[i]->load();

    current = 4;

    sf::Clock clock;
    cool=1;
    static int bar_on=1;
    while (shader_window.isOpen())
    {
        if (shader_window.hasFocus() ) {
            if (bar_on==1) ShowTaskBar(false);
            bar_on=0;
        } else {
            if (bar_on==0) ShowTaskBar(true);
            bar_on=1;
        }
        // Process events
        sf::Event event;
        while (shader_window.pollEvent(event) || cool==0)
        {
            // Close window: exit
            if (event.type == sf::Event::Closed || cool==0) {
//                    mutje.lock();
                    cool=0;
                    old_size=shader_window.getSize();
                    old_pos=shader_window.getPosition();
                    shader_window.close();
//                    mutje.unlock();
                    break;
            }

//            if (event.type == sf::Event::Resized)
//                shader_window.

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    // Escape key: exit
                    case sf::Keyboard::Escape:
//                        mutje.lock();
                        cool=0;
                        old_size=shader_window.getSize();
                        old_pos=shader_window.getPosition();
                        shader_window.close();
//                        mutje.unlock();
                        break;

                    // Left arrow key: previous shader
                    case sf::Keyboard::Left:
                        if (current == 0)
                            current = effects.size() - 1;
                        else
                            current--;
//                        description.setString("Current effect: " + effects[current]->getName());
                        break;

                    // Right arrow key: next shader
                    case sf::Keyboard::Right:
                        if (current == effects.size() - 1)
                            current = 0;
                        else
                            current++;
//                        description.setString("Current effect: " + effects[current]->getName());
                        break;

                    default:
                        break;
                }
            }
        }
//        if (cool==0) break;
        // Update the current example
        float x = static_cast<float>(sf::Mouse::getPosition(shader_window).x) / shader_window.getSize().x;
        float y = static_cast<float>(sf::Mouse::getPosition(shader_window).y) / shader_window.getSize().y;

        if (shader_window.hasFocus()) {
            shader_window.clear(sf::Color(128, 128, 0));
            if (current!=4 && current!=5) {
                mutje.lock();
                effects[current]->update(clock.getElapsedTime().asSeconds(), x, y);
                shader_window.draw(*effects[current]);
                mutje.unlock();
                shader_window.display();
            }
            else {
                mutje.lock();
                radar=1;
                effects[5]->update(clock.getElapsedTime().asSeconds(), (float)BITMAPSX, (float)BITMAPSY);
                shader_window.draw(*effects[5]);
                radar=0;
                shader_window.display();
                mutje.unlock();
            }
        }
//        else sf::sleep(sf::milliseconds(100));
    }
    mutje.lock();
    cool=0;
    mutje.unlock();
    // delete the effects
    for (std::size_t i = 0; i < effects.size(); ++i)
        delete effects[i];
    effects.clear();

//    overlay.create(1,1);
    if (bar_on==0) ShowTaskBar(true);
    bar_on=1;
    printf("leaving radar thread\n");
    return EXIT_SUCCESS;
}
