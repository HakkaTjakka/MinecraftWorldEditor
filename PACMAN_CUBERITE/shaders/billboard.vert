uniform float wave_phase;
uniform int draw_mode;
uniform int num_pacman;
uniform vec2 draw_scale;
vec2 wave_amplitude=vec2(5.0, 5.0);

// if RADAR view: draw_mode=1
// x,y is draw_scale = BITMAPSX,BITMAPSY ( like 8 x 8 total virtual screen)
// real used scale = 1.0/(x*x),1.0/(y*y) ( very small... ???)
// position translation = 1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0
// m_transform.scale( 1.0/(x*x),1.0/(y*y)).translate(1920.0*x/2.0-1920.0/2.0,1080.0*y/2.0-1080.0/2.0); // ???????????? scale???? funny. Plz explain.... :P

// if SCREEN view (like on real screen): draw_mode=0
// x,y is draw_scale =  1.0,1.0 ( also on like 8 x 8 screen but now 1.0, scaling is same as on viewport from code )
// real used scale = 1.0,1.0 ( like on screen )
// position translation = 0.0,0.0 ( like on screen )
// m_transform.translate(0.0,0.0).scale( x,y );

// gl_Vertex is vertex of WHOLE pointcloud. Every vertex is the position of 1 object. Like its center point.
// Like 1 vertex per ghost. So you don't have all 4 corners of the textured object/square.
// So you only can change them position here, and how they are rotated and translated as object like a point.
// The objects themselves don't rotate around their axes. That needs to be done in the geometry shader. There you have all 4 points of one point object.
void main()
{

//    if (gl_Color.ba==vec2(0.0,0.0)) return;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
}
