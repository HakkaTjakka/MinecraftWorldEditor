#include "everything.hpp"

sf::Font print_font;
sf::Text print_text;
extern sf::Clock kp;

void set_print_text() {
    char fn[200]="";
//    set_mono(1);
//    sprintf(fn,"%s/files/Megapack/4. Pixel Font Pack/mono0756.ttf",FONTDIR);
//    sprintf(fn,"%s/files/AndaleMono.ttf",FONTDIR);


//    sprintf(fn,"resources/BungeeLayers-Regular.otf",FONTDIR);
//    print_font.loadFromFile(fn);
    print_font.loadFromFile("resources/consolab.ttf");
    print_text.setFont(print_font);
//    set_mono(0);
    return;
}

int end_screen=0;

void print_to_screen(int var_font, char * text_to_print, int font_size, sf::Color paint_in, sf::Color paint_out, sf::Color paint_back, float outline, sf::Uint32 text_type ) {
    static int x_position=1920/2.0+32;
    static int y_position=0;
    int screen_x;
    int screen_y;
    static int max_x=0;

//    x_position=1920/2;
//    y_position=1080;

//    screen_x=x_position;
    screen_x=x_position-1920/2;
    screen_y=(maxpixelsy+y_position-1080/2)%maxpixelsy;

    text_to_ffmpeg_w2(var_font, text_to_print, font_size, paint_in, paint_out, paint_back, outline, text_type);

    ffmpeg_move=0;
    size_ffmpeg=0;
    rotate_ffmpeg=0;
    sprite_from_ffmpeg.setScale(sf::Vector2f(1.0,1.0));

    int start_posx_mem=start_posx;
    int start_posy_mem=start_posy;

    int render_picturex_mem=render_picturex;
    int render_picturey_mem=render_picturey;
    int render_posx_mem=render_posx;
    int render_posy_mem=render_posy;

    int picturex_mem=picturex;
    int picturey_mem=picturey;
    int posx_mem=posx;
    int posy_mem=posy;
    float fposx_mem=fposx;
    float fposy_mem=fposy;

    picturex=screen_x/1920;         render_picturex=picturex;
    posx=screen_x-1920*picturex;
    picturey=screen_y/1080;         render_picturey=picturey;
    posy=screen_y-1080*picturey;
    posx=-posx;                     render_posx=posx;
    posy=-posy;                     render_posy=posy;
    fposx=posx;
    fposy=posy;

    ffmpeg_posx=x_position;
    ffmpeg_posy=y_position;


    start_posx=ffmpeg_posx-1920/2+(int)(texture_from_ffmpeg.getSize().x/2);
    start_posy=ffmpeg_posy-1080/2+(int)(texture_from_ffmpeg.getSize().y/2);
//    start_posx=ffmpeg_posx-1920/2+(int)(texture_from_ffmpeg.getSize().x/2);
//    start_posy=ffmpeg_posy-1080/2+(int)(texture_from_ffmpeg.getSize().y/2);
//                    start_posx=ffmpeg_posx-1920/2;
//                    start_posy=ffmpeg_posy-1080/2;

    if ((start_posx)>=maxpixelsx) start_posx=start_posx-maxpixelsx;
    else if ((start_posx)<0) start_posx=start_posx+maxpixelsx;
    if ((start_posy)>=maxpixelsy) start_posy=start_posy-maxpixelsy;
    else if ((start_posy)<0) start_posy=start_posy+maxpixelsy;

    home_map();

    render_picturex=picturex;
    render_posx=posx;
    render_picturey=picturey;
    render_posy=posy;

    perform_quit=1;
    setffmpegfile();
    plot_ffmpegfile=1;
    double osx=smooth_x;
    double osy=smooth_y;
    smooth_x=(float)((int)smooth_x);
    smooth_y=(float)((int)smooth_y);
    plot_some();
    smooth_x=osx;
    smooth_y=osy;
    perform_quit=0;

    start_posx=start_posx_mem;
    start_posy=start_posy_mem;

    render_picturex=render_picturex_mem;
    render_picturey=render_picturey_mem;
    render_posx=render_posx_mem;
    render_posy=render_posy_mem;

    picturex=picturex_mem;
    picturey=picturey_mem;
    posx=posx_mem;
    posy=posy_mem;
    fposx=fposx_mem;
    fposy=fposy_mem;

    y_position=y_position+texture_from_ffmpeg.getSize().y;
    if (texture_from_ffmpeg.getSize().x>max_x) max_x=texture_from_ffmpeg.getSize().x;

//    y_position=y_position+font_size+4+(int)outline;

    if (y_position>=maxpixelsy-texture_from_ffmpeg.getSize().y) {
//        y_position=(y_position)%maxpixelsy;
        y_position=0;
        x_position=x_position+(2400);
        if (x_position+max_x>=maxpixelsx) {
            end_screen=1;
            strcpy(error_msg4,"END OF SCREEN REACHED, ABORTING..");
            printf("%s\n",error_msg4);
            error_flag4=1;
        }
        max_x=0;
//        break;
    }

    if (kp.getElapsedTime().asSeconds() > 5.0) {
        picturex=((screen_x+1920/2-32)%maxpixelsx)/1920;      //   render_picturex=picturex;
        posx=(screen_x+1920/2)%maxpixelsx-1920*picturex;
        picturey=((screen_y-400+maxpixelsy)%maxpixelsy)/1080;         //render_picturey=picturey;
        posy=(screen_y-400+maxpixelsy)%maxpixelsy-1080*picturey;
        posx=-posx;                     //render_posx=posx;
        posy=-posy;                     //render_posy=posy;
        fposx=posx;
        fposy=posy;
    }



//    ffmpegfile=1;
    ffmpeg_move=0;
    size_ffmpeg=0;
//    forced_jump=1;
//    follow_ghost_pos();
//    blitter("",1);
//    pen=1;
//    pen_mode=2;
//    ReadBitmaps2();
//    ReadBitmaps4();
}

void text_to_ffmpeg_w2(int var_font, char * in,int font_size, sf::Color inner, sf::Color outer, sf::Color background, float outline, sf::Uint32 text_type) {
    sf::Text *mytext_var;
    static sf::RenderTexture print_font_texture;

//    set_mono(1);

    mytext_var=&print_text;
//    if (var_font==1)  mytext_var=&mytext;
//    else mytext_var=&mytext2;

    mytext_var->setScale(1,1);
    mytext_var->setStyle(text_type);
    mytext_var->setOutlineColor(outer);
    mytext_var->setFillColor(inner);
    mytext_var->setOutlineThickness((int)outline);
    mytext_var->setPosition(0.0,0.0);
    mytext_var->setString(in);

    int s=font_size;
    mytext_var->setCharacterSize(s);
    int xsize=9999999;
    int ysize=9999999;
    while ((xsize>1920*8 ) && s>10) {
        xsize=mytext_var->getGlobalBounds().width+2;
        if ((xsize>1920*8 ) && s>10) {
            s=s-1;
            mytext_var->setCharacterSize(s);
        }
    }
    if ((xsize%2)==1) xsize++;
    static char previous[200]="";
    static int prev_ysize=0;
    static int prev_originx=0;
    static int prev_originy=0;
    char now[200];
    sprintf(now,"%d%d%d%d%d%d",s,ysize,var_font,font_size,(int)outline,text_type);
    if (strcmp(now,previous)!=0) {
        mytext_var->setString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZàáâãäæçèéêëíîïğñòóôõöùúûüışÿ`~!@#$%^&*()_+1234567890{}[];:'\"\|,<.>/?");
        ysize=mytext_var->getGlobalBounds().height;
//        ysize=mytext_var->getGlobalBounds().height+mytext_var->getOutlineThickness()*2+2;
        if ((ysize%2)==1) ysize++;
        prev_originx=mytext_var->getLocalBounds().left-1;
//        prev_originx=mytext_var->getLocalBounds().left-mytext_var->getOutlineThickness()*2;
//        prev_originy=mytext_var->getLocalBounds().top-2;
//        prev_originy=mytext_var->getLocalBounds().top+1;
        prev_originy=mytext_var->getLocalBounds().top;
        mytext_var->setOrigin(prev_originx,prev_originy);
        prev_ysize=ysize;
        sprintf(previous,"%d%d%d%d%d%d",s,ysize,var_font,font_size,(int)outline,text_type);
        mytext_var->setString(in);
    } else {
        ysize=prev_ysize;
        mytext_var->setOrigin(prev_originx,prev_originy);
    }

//    sf::Texture& texture = const_cast<sf::Texture&>(print_font.getTexture(s));
    if (smooth==1)  {
//        texture.setSmooth(true);
        const_cast<sf::Texture&>(print_font.getTexture(mytext_var->getCharacterSize())).setSmooth(true);
    } else {
        const_cast<sf::Texture&>(print_font.getTexture(mytext_var->getCharacterSize())).setSmooth(false);
//        texture.setSmooth(false);
    }

    texture_from_ffmpeg.create(xsize,ysize);
    print_font_texture.create(xsize,ysize);
    print_font_texture.clear(background);

    if (smooth==1)  {
        font_texture.setSmooth(true);
        print_font_texture.setSmooth(true);
        texture_from_ffmpeg.setSmooth(true);
    } else {
        font_texture.setSmooth(false);
        print_font_texture.setSmooth(false);
        texture_from_ffmpeg.setSmooth(false);
    }

    print_font_texture.draw(*mytext_var);
    print_font_texture.display();

    texture_from_ffmpeg.update(print_font_texture.getTexture());
    ffmpegfile=1;
    sprite_from_ffmpeg.setTexture(texture_from_ffmpeg,true);
//    set_mono(0);
}

