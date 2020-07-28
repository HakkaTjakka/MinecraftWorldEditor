#define SFML_STATIC
#undef UNICODE
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

extern int reload_init();
extern int PIXELISBLACKTHRESHOLD;
extern int PIXELISWHITETHRESHOLD;
extern int PIXELISCOLORTHRESHOLD;
extern int PIXELISCOLOR_R;
extern int PIXELISCOLOR_G;
extern int PIXELISCOLOR_B;
extern int ffmpegfile;
extern int internetfile;

extern void savedata(char *naam, int data);
sf::RenderTexture *MyRenderTexture = new sf::RenderTexture();
extern sf::RenderWindow SFMLView1;

void make_black_transparant(sf::Texture * MyTexture) {
    int x,y;
    sf::Image MyImage;
    sf::Image MyImage2;
    sf::Color MyColor;
    int SizeX,SizeY;

    reload_init();

    SizeX=MyTexture->getSize().x;
    SizeY=MyTexture->getSize().y;

    MyImage=MyTexture->copyToImage();
    MyImage2.create(SizeX,SizeY);

    for (x=0; x<SizeX; x++) {
        for (y=0; y<SizeY; y++) {
            MyColor=MyImage.getPixel(x,y);
            if (MyColor.r<PIXELISBLACKTHRESHOLD && MyColor.g<PIXELISBLACKTHRESHOLD && MyColor.b<PIXELISBLACKTHRESHOLD) {
                MyColor.r=0;
                MyColor.g=0;
                MyColor.b=0;
                MyColor.a=0;
            }
            MyImage2.setPixel(x,y,MyColor);
        }
    }
    for (x=0; x<SizeX; x++) {
        for (y=0; y<SizeY; y++) {
            MyColor=MyImage.getPixel(x,y);
            if (MyColor.r<PIXELISBLACKTHRESHOLD && MyColor.g<PIXELISBLACKTHRESHOLD && MyColor.b<PIXELISBLACKTHRESHOLD) {
                if (x>0)        { MyColor=MyImage2.getPixel(x-1, y);      MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x-1,    y,      MyColor); }
                if (x<SizeX-1)  { MyColor=MyImage2.getPixel(x+1, y);      MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x+1,    y,      MyColor); }
                if (y>0)        { MyColor=MyImage2.getPixel(x,   y-1);    MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x,      y-1,    MyColor); }
                if (y<SizeY-1)  { MyColor=MyImage2.getPixel(x,   y+1);    MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x,      y+1,    MyColor); }

                if (x>1)        { MyColor=MyImage2.getPixel(x-2, y);      MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x-2,    y,      MyColor); }
                if (x<SizeX-2)  { MyColor=MyImage2.getPixel(x+2, y);      MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x+2,    y,      MyColor); }
                if (y>1)        { MyColor=MyImage2.getPixel(x,   y-2);    MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x,      y-2,    MyColor); }
                if (y<SizeY-2)  { MyColor=MyImage2.getPixel(x,   y+2);    MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x,      y+2,    MyColor); }

                if (x>0         && y>0)       { MyColor=MyImage2.getPixel(x-1, y-1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x-1,    y-1,    MyColor); }
                if (x<SizeX-1   && y>0)       { MyColor=MyImage2.getPixel(x+1, y-1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x+1,    y-1,    MyColor); }
                if (x>0         && y<SizeY-1) { MyColor=MyImage2.getPixel(x-1, y+1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x-1,    y+1,    MyColor); }
                if (x<SizeX-1   && y<SizeY-1) { MyColor=MyImage2.getPixel(x+1, y+1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x+1,    y+1,    MyColor); }
            }
        }
    }
    MyTexture->loadFromImage(MyImage2);
}

void make_dark_transparant(sf::Texture * MyTexture) {
    int x,y;
    sf::Image MyImage;
    sf::Color MyColor;
    int SizeX,SizeY;

    reload_init();

    SizeX=MyTexture->getSize().x;
    SizeY=MyTexture->getSize().y;

    MyImage=MyTexture->copyToImage();
    int max_illum;

    for (x=0; x<SizeX; x++) {
        for (y=0; y<SizeY; y++) {
            MyColor=MyImage.getPixel(x,y);
            max_illum=(MyColor.r+MyColor.g+MyColor.b)/3;
            max_illum=MyColor.r;
            if (MyColor.b>max_illum) max_illum=MyColor.b;
            if (MyColor.g>max_illum) max_illum=MyColor.g;
            MyColor.a=max_illum; // if (MyColor.a>255) MyColor.a=255;
//            MyColor.r=(MyColor.r*2); if (MyColor.r>255) MyColor.r=255;
//            MyColor.g=(MyColor.g*2); if (MyColor.g>255) MyColor.g=255;
//            MyColor.b=(MyColor.b*2); if (MyColor.b>255) MyColor.b=255;
            MyImage.setPixel(x,y,MyColor);
        }
    }
    MyTexture->loadFromImage(MyImage);
}

void make_white_transparant(sf::Texture * MyTexture) {
    int x,y;
    sf::Image MyImage;
    sf::Image MyImage2;
    sf::Color MyColor;
    int SizeX,SizeY;

    reload_init();

    SizeX=MyTexture->getSize().x;
    SizeY=MyTexture->getSize().y;

    MyImage=MyTexture->copyToImage();
    MyImage2.create(SizeX,SizeY);

    for (x=0; x<SizeX; x++) {
        for (y=0; y<SizeY; y++) {
            MyColor=MyImage.getPixel(x,y);
            if ((255-MyColor.r)<PIXELISWHITETHRESHOLD && (255-MyColor.g)<PIXELISWHITETHRESHOLD && (255-MyColor.b)<PIXELISWHITETHRESHOLD) {
                MyColor.a=0;
                MyColor.r=0;
                MyColor.g=0;
                MyColor.b=0;
            }
            MyImage2.setPixel(x,y,MyColor);
        }
    }
    for (x=0; x<SizeX; x++) {
        for (y=0; y<SizeY; y++) {
            MyColor=MyImage.getPixel(x,y);
            if ((255-MyColor.r)<PIXELISWHITETHRESHOLD && (255-MyColor.g)<PIXELISWHITETHRESHOLD && (255-MyColor.b)<PIXELISWHITETHRESHOLD) {
                if (x>0)        { MyColor=MyImage2.getPixel(x-1, y);      MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x-1,    y,      MyColor); }
                if (x<SizeX-1)  { MyColor=MyImage2.getPixel(x+1, y);      MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x+1,    y,      MyColor); }
                if (y>0)        { MyColor=MyImage2.getPixel(x,   y-1);    MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x,      y-1,    MyColor); }
                if (y<SizeY-1)  { MyColor=MyImage2.getPixel(x,   y+1);    MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x,      y+1,    MyColor); }

                if (x>1)        { MyColor=MyImage2.getPixel(x-2, y);      MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x-2,    y,      MyColor); }
                if (x<SizeX-2)  { MyColor=MyImage2.getPixel(x+2, y);      MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x+2,    y,      MyColor); }
                if (y>1)        { MyColor=MyImage2.getPixel(x,   y-2);    MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x,      y-2,    MyColor); }
                if (y<SizeY-2)  { MyColor=MyImage2.getPixel(x,   y+2);    MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x,      y+2,    MyColor); }

                if (x>0         && y>0)       { MyColor=MyImage2.getPixel(x-1, y-1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x-1,    y-1,    MyColor); }
                if (x<SizeX-1   && y>0)       { MyColor=MyImage2.getPixel(x+1, y-1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x+1,    y-1,    MyColor); }
                if (x>0         && y<SizeY-1) { MyColor=MyImage2.getPixel(x-1, y+1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x-1,    y+1,    MyColor); }
                if (x<SizeX-1   && y<SizeY-1) { MyColor=MyImage2.getPixel(x+1, y+1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x+1,    y+1,    MyColor); }
            }
        }
    }
    MyTexture->loadFromImage(MyImage2);
}

void make_color_transparant(sf::Texture * MyTexture) {
    int x,y;
    sf::Image MyImage;
    sf::Image MyImage2;
    sf::Color MyColor;
    int SizeX,SizeY;

    reload_init();

    SizeX=MyTexture->getSize().x;
    SizeY=MyTexture->getSize().y;

    MyImage=MyTexture->copyToImage();
    MyImage2.create(SizeX,SizeY);

    for (x=0; x<SizeX; x++) {
        for (y=0; y<SizeY; y++) {
            MyColor=MyImage.getPixel(x,y);
            if (abs(PIXELISCOLOR_R-MyColor.r)<PIXELISCOLORTHRESHOLD && abs(PIXELISCOLOR_G-MyColor.g)<PIXELISCOLORTHRESHOLD && abs(PIXELISCOLOR_B-MyColor.b)<PIXELISCOLORTHRESHOLD) {
                MyColor.a=0;
                MyColor.r=0;
                MyColor.g=0;
                MyColor.b=0;
            }
            MyImage2.setPixel(x,y,MyColor);
        }
    }
    for (x=0; x<SizeX; x++) {
        for (y=0; y<SizeY; y++) {
            MyColor=MyImage.getPixel(x,y);
            if (abs(PIXELISCOLOR_R-MyColor.r)<PIXELISCOLORTHRESHOLD && abs(PIXELISCOLOR_G-MyColor.g)<PIXELISCOLORTHRESHOLD && abs(PIXELISCOLOR_B-MyColor.b)<PIXELISCOLORTHRESHOLD) {
                if (x>0)        { MyColor=MyImage2.getPixel(x-1, y);      MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x-1,    y,      MyColor); }
                if (x<SizeX-1)  { MyColor=MyImage2.getPixel(x+1, y);      MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x+1,    y,      MyColor); }
                if (y>0)        { MyColor=MyImage2.getPixel(x,   y-1);    MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x,      y-1,    MyColor); }
                if (y<SizeY-1)  { MyColor=MyImage2.getPixel(x,   y+1);    MyColor.a=MyColor.a/4; MyColor.r=MyColor.r/4; MyColor.g=MyColor.g/4; MyColor.b=MyColor.b/4; MyImage2.setPixel(x,      y+1,    MyColor); }

                if (x>1)        { MyColor=MyImage2.getPixel(x-2, y);      MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x-2,    y,      MyColor); }
                if (x<SizeX-2)  { MyColor=MyImage2.getPixel(x+2, y);      MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x+2,    y,      MyColor); }
                if (y>1)        { MyColor=MyImage2.getPixel(x,   y-2);    MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x,      y-2,    MyColor); }
                if (y<SizeY-2)  { MyColor=MyImage2.getPixel(x,   y+2);    MyColor.a=MyColor.a/2; MyColor.r=MyColor.r/2; MyColor.g=MyColor.g/2; MyColor.b=MyColor.b/2; MyImage2.setPixel(x,      y+2,    MyColor); }

                if (x>0         && y>0)       { MyColor=MyImage2.getPixel(x-1, y-1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x-1,    y-1,    MyColor); }
                if (x<SizeX-1   && y>0)       { MyColor=MyImage2.getPixel(x+1, y-1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x+1,    y-1,    MyColor); }
                if (x>0         && y<SizeY-1) { MyColor=MyImage2.getPixel(x-1, y+1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x-1,    y+1,    MyColor); }
                if (x<SizeX-1   && y<SizeY-1) { MyColor=MyImage2.getPixel(x+1, y+1);    MyColor.a=MyColor.a/3; MyColor.r=MyColor.r/3; MyColor.g=MyColor.g/3; MyColor.b=MyColor.b/3; MyImage2.setPixel(x+1,    y+1,    MyColor); }
            }
        }
    }
    MyTexture->loadFromImage(MyImage2);
}

extern int error_flag;
extern char error_msg[];

void convert_to_scale(sf::Texture * MyTexture,sf::Sprite * MySprite) {
    sf::RenderTexture MyRenderTexture;
    sf::Image MyImage;
    sf::Sprite MySpriteNew;
    int SizeX,SizeY;
    int NewSizeX,NewSizeY;
    unsigned int MaxSize=8000;

    SizeX=MyTexture->getSize().x;
    SizeY=MyTexture->getSize().y;
    NewSizeX=SizeX*MySprite->getScale().x;
    NewSizeY=SizeY*MySprite->getScale().y;

//    if (NewSizeX>MaxSize || NewSizeY>MaxSize) {
//        sprintf(error_msg,"MAXIMUM TEXTURESIZE=%d",MaxSize);
//        error_flag=1;
//        return;
//    }

    if (!MyRenderTexture.create(NewSizeX,NewSizeY)) {
        sprintf(error_msg,"FAILED TO CREATE TEXTURE (CREATE)");
        error_flag=1;
        return;

    }
    if (NewSizeX!=MyRenderTexture.getSize().x || NewSizeY!=MyRenderTexture.getSize().y) {
        sprintf(error_msg,"FAILED TO CREATE TEXTURE (SIZE DIFFERENT)");
        error_flag=1;
        return;
    }
    MyRenderTexture.clear(sf::Color(0,0,0,0));

    MySpriteNew.setTexture(*MyTexture,true);
    MySpriteNew.setTextureRect({0,0,SizeX,SizeY});
    MySpriteNew.setOrigin( SizeX/2,SizeY/2);
    MySpriteNew.setPosition( NewSizeX/2,NewSizeY/2);
    MySpriteNew.setScale(MySprite->getScale().x,MySprite->getScale().y);

    MyRenderTexture.draw(MySpriteNew);
    MyRenderTexture.display();

    MyImage=MyRenderTexture.getTexture().copyToImage();
    MyTexture->loadFromImage(MyImage);

    MySprite->setTexture(*MyTexture,false);
    MySprite->setTextureRect({0,0,NewSizeX,NewSizeY});
    MySprite->setScale(1.0,1.0);
}

void movie_to_ffmpeg(sf::Texture * MyTexture_movie, sf::Texture * MyTexture_ffmpeg) {
    sf::Image MyImage;

    MyImage=MyTexture_movie->copyToImage();
    MyTexture_ffmpeg->loadFromImage(MyImage);
}


void add_border(sf::Texture * MyTexture) {
//    sf::Image MyImage;
    unsigned int MaxSize=6000;
    SFMLView1.setActive(false);
  //  if (MyTexture->getSize().x+20>MaxSize || MyTexture->getSize().y+20>MaxSize) {
//        savedata("MAXIMUM TEXTURESIZE\n",0);
//        sprintf(error_msg,"MAXIMUM TEXTURESIZE=%d (BORDER ADDS 20 PIXELS)",MaxSize);
//        error_flag=1;
//        return;
//    }

    if (!MyRenderTexture->create((int)MyTexture->getSize().x+20,(int)MyTexture->getSize().y+20)) {
        savedata("error creating MyRenderTexuture in add_border()\n",0);
        printf("error creating MyRenderTexuture in add_border(). X=%d,Y=%d\n",(int)MyTexture->getSize().x+20,(int)MyTexture->getSize().y+20);
        if (ffmpegfile==0) ffmpegfile=1;
        if (internetfile==0) internetfile=1;
        return;
    }
    MyRenderTexture->clear(sf::Color(255,255,255,255));

    sf::Sprite MySprite;
    MySprite.setTexture(*MyTexture,true);
    MySprite.setTextureRect({0,0,MyTexture->getSize().x,MyTexture->getSize().y});
    MySprite.setPosition( 10.0,10.0 );

    MyRenderTexture->draw(MySprite);
    MyRenderTexture->display();

    *MyTexture=MyRenderTexture->getTexture();
    SFMLView1.setActive(true);
    return;
}

int border_col_r=0;
int border_col_g=100;
int border_col_b=200;
extern int smooth;

void add_border_left_right(sf::Texture * MyTexture) {
    if (border_col_r==0 && border_col_g==0 && border_col_b==0) {
        border_col_r=0;
        border_col_g=100;
        border_col_b=200;
    }
//    sf::Image MyImage;
    unsigned int MaxSize=6000;
    SFMLView1.setActive(false);
  //  if (MyTexture->getSize().x+20>MaxSize || MyTexture->getSize().y+20>MaxSize) {
//        savedata("MAXIMUM TEXTURESIZE\n",0);
//        sprintf(error_msg,"MAXIMUM TEXTURESIZE=%d (BORDER ADDS 20 PIXELS)",MaxSize);
//        error_flag=1;
//        return;
//    }

    if (!MyRenderTexture->create((int)MyTexture->getSize().x+20,(int)MyTexture->getSize().y)) {
        savedata("error creating MyRenderTexuture in add_border()\n",0);
        printf("error creating MyRenderTexuture in add_border(). X=%d,Y=%d\n",(int)MyTexture->getSize().x+20,(int)MyTexture->getSize().y);
        if (ffmpegfile==0) ffmpegfile=1;
        if (internetfile==0) internetfile=1;
        return;
    }
//    MyRenderTexture->clear(sf::Color(0,0,255,255));
    MyRenderTexture->setSmooth(smooth);
    sf::RectangleShape square;
    square.setOrigin(0.0,0.0);
    square.setFillColor(sf::Color(border_col_r,border_col_g,border_col_b,255));
    square.setOutlineThickness(1.0);

    square.setOutlineColor(sf::Color(border_col_r,border_col_g,border_col_b,0));
    square.setPosition(1.0,0.0);
    square.setSize( {(int)MyRenderTexture->getSize().x-2,(int)MyRenderTexture->getSize().y});
    MyRenderTexture->draw(square);

    square.setOutlineColor(sf::Color(border_col_r,border_col_g,border_col_b,30));
    square.setPosition(2.0,0.0);
    square.setSize( {(int)MyRenderTexture->getSize().x-4,(int)MyRenderTexture->getSize().y});
    MyRenderTexture->draw(square);

    square.setOutlineColor(sf::Color(border_col_r,border_col_g,border_col_b,90));
    square.setPosition(3.0,0.0);
    square.setSize( {(int)MyRenderTexture->getSize().x-6,(int)MyRenderTexture->getSize().y});
    MyRenderTexture->draw(square);

    square.setOutlineColor(sf::Color(border_col_r,border_col_g,border_col_b,160));
    square.setPosition(4.0,0.0);
    square.setSize( {(int)MyRenderTexture->getSize().x-8,(int)MyRenderTexture->getSize().y});
    MyRenderTexture->draw(square);

    square.setOutlineColor(sf::Color(border_col_r,border_col_g,border_col_b,240));
    square.setPosition(5.0,0.0);
    square.setSize( {(int)MyRenderTexture->getSize().x-10,(int)MyRenderTexture->getSize().y});
    MyRenderTexture->draw(square);

    sf::Sprite MySprite;
    MySprite.setTexture(*MyTexture,true);
    MySprite.setTextureRect({0,0,MyTexture->getSize().x,MyTexture->getSize().y});
    MySprite.setPosition( 10.0,0.0 );

    MyRenderTexture->draw(MySprite);
    MyRenderTexture->display();

    *MyTexture=MyRenderTexture->getTexture();
    SFMLView1.setActive(true);
    return;
}

void soften_edge(sf::Texture * MyTexture) {
//    sf::Image MyImage;
    unsigned int MaxSize=6000;

    SFMLView1.setActive(false);
    if (!MyRenderTexture->create((int)MyTexture->getSize().x+2,(int)MyTexture->getSize().y+2)) {
        printf("error creating MyRenderTexuture in soften_edge(). X=%d,Y=%d\n",(int)MyTexture->getSize().x+20,(int)MyTexture->getSize().y+20);
        savedata("error creating MyRenderTexuture in soften_edge()\n",0);
        if (ffmpegfile==0) ffmpegfile=1;
        if (internetfile==0) internetfile=1;
        return;
    }
    MyRenderTexture->clear(sf::Color(255,255,255,0));

    sf::Sprite MySprite;
    MySprite.setTexture(*MyTexture,true);
    MySprite.setPosition(1.0,1.0);
    MyRenderTexture->draw(MySprite);
    MyRenderTexture->display();

    sf::BlendMode MyBlend=sf::BlendAdd;
    MyBlend.alphaSrcFactor    = sf::BlendMode::One;
    MyBlend.alphaDstFactor    = sf::BlendMode::One;
    MyBlend.alphaEquation     = sf::BlendMode::ReverseSubtract;

    sf::RectangleShape Hole;

    Hole.setOutlineThickness(1.0);

    Hole.setFillColor(sf::Color(255,255,255,0));
    Hole.setPosition(1.0,1.0);
    Hole.setSize( {(int)MyRenderTexture->getSize().x-2,(int)MyRenderTexture->getSize().y-2});
    MyRenderTexture->draw(Hole,MyBlend);

    Hole.setOutlineColor(sf::Color(255,255,255,255-15));
    Hole.setPosition(2.0,2.0);
    Hole.setSize( {(int)MyRenderTexture->getSize().x-4,(int)MyRenderTexture->getSize().y-4});
    MyRenderTexture->draw(Hole,MyBlend);

    Hole.setOutlineColor(sf::Color(255,255,255,150));
    Hole.setPosition(3.0,3.0);
    Hole.setSize( {(int)MyRenderTexture->getSize().x-6,(int)MyRenderTexture->getSize().y-6});
    MyRenderTexture->draw(Hole,MyBlend);

    Hole.setOutlineColor(sf::Color(255,255,255,63));
    Hole.setPosition(4.0,4.0);
    Hole.setSize( {(int)MyRenderTexture->getSize().x-8,(int)MyRenderTexture->getSize().y-8});
    MyRenderTexture->draw(Hole,MyBlend);

    MyRenderTexture->display();

    *MyTexture=MyRenderTexture->getTexture();
    SFMLView1.setActive(true);
    return;
}

void rot_texture_90(sf::Texture * MyTexture) {
    SFMLView1.setActive(false);

    if (!MyRenderTexture->create((int)MyTexture->getSize().y,(int)MyTexture->getSize().x)) {
        savedata("error creating MyRenderTexuture in add_border()\n",0);
        printf("error creating MyRenderTexuture in add_border(). X=%d,Y=%d\n",(int)MyTexture->getSize().y,(int)MyTexture->getSize().x);
        if (ffmpegfile==0) ffmpegfile=1;
        if (internetfile==0) internetfile=1;
        return;
    }
    sf::Sprite MySprite;
    MySprite.setTexture(*MyTexture,true);
    MySprite.setTextureRect({0,0,MyTexture->getSize().x,MyTexture->getSize().y});
    MySprite.setPosition( MyTexture->getSize().y,0.0 );
    MySprite.setRotation(90);

    MyRenderTexture->draw(MySprite);
    MyRenderTexture->display();

    *MyTexture=MyRenderTexture->getTexture();
    SFMLView1.setActive(true);
    return;
}

void rot_texture_as_is(sf::Texture * MyTexture, sf::Sprite * MySpriteIn) {
    SFMLView1.setActive(false);
    int x,y;
    int globx=MySpriteIn->getGlobalBounds().width;
    int globy=MySpriteIn->getGlobalBounds().height;

    if (!MyRenderTexture->create(globx,globy)) {
        savedata("error creating MyRenderTexuture in add_border()\n",0);
        printf("error creating MyRenderTexuture in add_border(). X=%d,Y=%d\n",globx,globy);
        if (ffmpegfile==0) ffmpegfile=1;
        if (internetfile==0) internetfile=1;
        return;
    }
    sf::Sprite MySprite;
    MySprite.setTexture(*MyTexture,true);
    MySprite.setTextureRect({0,0,MyTexture->getSize().x,MyTexture->getSize().y});
    MySprite.setOrigin(MyTexture->getSize().x/2.0,MyTexture->getSize().y/2.0);
    MySprite.setPosition( MyRenderTexture->getSize().x/2.0,MyRenderTexture->getSize().y/2.0 );
    MySprite.setRotation(MySpriteIn->getRotation());
    MySprite.setScale(MySpriteIn->getScale());

    MyRenderTexture->draw(MySprite);
    MyRenderTexture->display();

    *MyTexture=MyRenderTexture->getTexture();
    SFMLView1.setActive(true);
    return;
}
