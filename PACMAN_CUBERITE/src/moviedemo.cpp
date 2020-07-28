#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <sfeMovie/Movie.hpp>
#include <iostream>
#include <algorithm>
#include "UserInterface.hpp"
#include "StreamSelector.hpp"
#include "MediaInfo.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <io.h>
#include <cstdlib>
#include <assert.h>
#include <Windows.h>
extern int force_game;
extern int smooth;
void stopmovie();
void stopmovie2();
extern sf::Time time_movie2;
extern char movie_name[];
extern char MOVIEDIR[];
extern select_movie(char *filename, char * path);
extern int movie2;
extern void setmoviefile2();
extern int timer_movie2;

//sf::RenderTexture *texture_from_movie;
sfe::Movie *live_movie=NULL;
StreamSelector *live_selector=NULL;

//sf::RenderTexture *texture_from_movie2;
sfe::Movie *live_movie2=NULL;
StreamSelector *live_selector2=NULL;

sf::Texture texture_from_movie_new;
sf::Texture texture_from_movie2_new;

extern sf::Sprite sprite_from_movie;
extern sf::Sprite sprite_from_movie2;

extern char* line;
extern void savedata(char *naam, int data);
extern int live_movie_is_mp3;
extern int live_movie2_is_mp3;
extern sf::Time time_movie;
extern char movie_name[];
extern char MOVIEDIR[];
extern select_movie(char *filename, char * path);
extern int movie;
extern void setmoviefile();
extern int timer_movie;
extern int rotate_movie2;
extern float rot_speed_movie2;
extern float rotation_movie2;
extern int size_movie2;


int startmovie(char* naam)
{
    sprintf(line,"MOVIE: %s",naam);
    savedata(line,0);
    live_movie = new sfe::Movie();
    live_selector = new StreamSelector(*live_movie);
    if (!live_movie->openFromFile(naam))
        return 1;
    live_movie->play();
    live_movie->update();
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float width = std::min(static_cast<float>(desktopMode.width), live_movie->getSize().x);
    float height = std::min(static_cast<float>(desktopMode.height), live_movie->getSize().y);
    force_game=0;
    if (width * height < 1.f)
    {
        live_movie_is_mp3=1;
        force_game=1;
        width = std::max(width, 250.f);
        height = std::max(height, 40.f);
    }
    else
    {
        live_movie_is_mp3=0;
        live_movie->fit(0, 0, width, height,true);
    }
    live_movie->setVolume(100.0);
    texture_from_movie_new.create(width,height);
    texture_from_movie_new.setRepeated(true);
    return 0;
}


int startmovie2(char* naam)
{
    sprintf(line,"MOVIE2: %s",naam);
    savedata(line,0);
    live_movie2 = new sfe::Movie();
    live_selector2 = new StreamSelector(*live_movie2);
    if (!live_movie2->openFromFile(naam))
        return 1;
    live_movie2->play();
    live_movie2->update();
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
//    float width = std::min(static_cast<float>(desktopMode.width), live_movie2->getSize().x);
//    float height = std::min(static_cast<float>(desktopMode.height), live_movie2->getSize().y);
    float width = live_movie2->getSize().x;
    float height =live_movie2->getSize().y;

    force_game=0;
    if (width * height < 1.f)
    {
        live_movie2_is_mp3=1;
//        force_game=1;
        width = std::max(width, 250.f);
        height = std::max(height, 40.f);
    }
    else
    {
        live_movie2_is_mp3=0;
    }

    live_movie2->fit(0, 0, width, height);

    live_movie2->setVolume(100.0);
    texture_from_movie2_new.create(width,height);
    texture_from_movie2_new.setRepeated(true);


    if (live_movie2_is_mp3==0)
    {
        rotate_movie2=1;
        rot_speed_movie2=0;
        rotation_movie2=0;
        size_movie2=1;

        sf::Vector2f wanted_size = {1920,1080};
        sf::Vector2f new_size;

        sf::Vector2f movie_size = live_movie2->getSize();

        sf::Vector2f target_size = movie_size;

        float source_ratio = movie_size.x / movie_size.y;
        float target_ratio = wanted_size.x / wanted_size.y;

        if (source_ratio > target_ratio)
        {
            target_size.x = movie_size.x * wanted_size.x / movie_size.x;
            target_size.y = movie_size.y * wanted_size.x / movie_size.x;
        }
        else
        {
            target_size.x = movie_size.x * wanted_size.y / movie_size.y;
            target_size.y = movie_size.y * wanted_size.y / movie_size.y;
        }
        new_size = target_size;
        sprite_from_movie2.setScale((float)new_size.x / movie_size.x, (float)new_size.y / movie_size.y);
    }
    return 0;
}


void stopmovie()
{
    if (movie==0)
        if (live_movie->getStatus()!=sfe::Stopped)
            live_movie->stop();
    delete live_movie;
    delete live_selector;
    live_movie=NULL;
    live_selector=NULL;
    return;
}
void stopmovie2()
{
    if (movie2==0)
        if (live_movie2->getStatus()!=sfe::Stopped)
            live_movie2->stop();
    delete live_movie2;
    delete live_selector2;
    live_movie2=NULL;
    live_selector2=NULL;
    return;
}

void updatemovie()
{
    if (live_movie->getStatus()!=sfe::Stopped
            && live_movie->getStatus()!=sfe::End
            && time_movie<live_movie->getDuration())
    {
        live_movie->update();
        texture_from_movie_new=live_movie->getCurrentImage();
//wow
        if (smooth==1)
            texture_from_movie_new.setSmooth(true);
        else
            texture_from_movie_new.setSmooth(false);
        sprite_from_movie.setTexture(texture_from_movie_new,false);
        if (live_movie_is_mp3=0)
            if (texture_from_movie_new.getSize().x==0)
                live_movie_is_mp3=1;
        texture_from_movie_new.setRepeated(true);

    }
    else
    {

        stopmovie();

        char filename[400];
        time_movie=sf::seconds(0.0);
        strcpy(movie_name,"");
        if (select_movie(filename,MOVIEDIR)>0)
            movie=startmovie(filename);
        if (movie==0)
        {
            texture_from_movie_new.setRepeated(true);
            strcpy(movie_name,filename);
            sprite_from_movie.setTexture(texture_from_movie_new,false);
            setmoviefile();

            sprite_from_movie.setTextureRect( { 0,0,(int)texture_from_movie_new.getSize().x, (int)texture_from_movie_new.getSize().y } );
            timer_movie=10;
            if (smooth==1)
                texture_from_movie_new.setSmooth(true);
            else
                texture_from_movie_new.setSmooth(true);
        }
    }
}

void updatemovie2()
{
    if (live_movie2->getStatus()!=sfe::Stopped
            && live_movie2->getStatus()!=sfe::End
            && time_movie2<live_movie2->getDuration())
    {
        live_movie2->update();
        texture_from_movie2_new=live_movie2->getCurrentImage();
        if (smooth==1)
            texture_from_movie2_new.setSmooth(true);
        else
            texture_from_movie2_new.setSmooth(false);
        sprite_from_movie2.setTexture(texture_from_movie2_new,false);
        if (live_movie2_is_mp3=0)
            if (texture_from_movie2_new.getSize().x==0)
                live_movie2_is_mp3=1;
        texture_from_movie2_new.setRepeated(true);
    }
    else
    {
        stopmovie2();

        char filename[400];
        time_movie2=sf::seconds(0.0);
        strcpy(movie_name,"");
        if (select_movie(filename,MOVIEDIR)>0)
            movie2=startmovie2(filename);
        printf(filename);
        if (movie2==0)
        {
            texture_from_movie2_new.setRepeated(true);
            strcpy(movie_name,filename);
            sprite_from_movie2.setTexture(texture_from_movie2_new,false);
            setmoviefile2();

            sprite_from_movie2.setTextureRect( { 0,0,(int)texture_from_movie2_new.getSize().x, (int)texture_from_movie2_new.getSize().y } );
            timer_movie2=10;
            if (smooth==1)
                texture_from_movie2_new.setSmooth(true);
            else
                texture_from_movie2_new.setSmooth(true);
        }
    }
}



void my_pause()
{
#ifdef SFML_SYSTEM_WINDOWS
    system("PAUSE");
#endif
}

void displayShortcuts()
{
    std::cout << "Shortcuts:\n"
              << "\tSpace - Play / pause\n"
              << "\tS - Stop\n"
              << "\tH - Hide / show user controls and mouse cursor\n"
              << "\tF - Toggle fullscreen\n"
              << "\tI - Log media info and current state\n"
              << "\tAlt + V - Select next video stream\n"
              << "\tAlt + A - Select next audio stream\n"
              << "\tAlt + S - Select next subtitle stream"
              << std::endl;
}

int playmovie(char * naam)
{

    sfe::Movie movie;
    if (!movie.openFromFile(naam))
    {
        my_pause();
        return 1;
    }

    bool fullscreen = false;
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    float width = std::min(static_cast<float>(desktopMode.width), movie.getSize().x);
    float height = std::min(static_cast<float>(desktopMode.height), movie.getSize().y);

    // For audio files, there is no frame size, set a minimum:
    if (width * height < 1.f)
    {
        width = std::max(width, 250.f);
        height = std::max(height, 40.f);
    }

    // Create window
    sf::RenderWindow window(sf::VideoMode(width, height), "sfeMovie Player",
                            sf::Style::Close | sf::Style::Resize);

    // Scale movie to the window drawing area and enable VSync
//    window.setFramerateLimit(60);
//    window.setVerticalSyncEnabled(true);
    movie.fit(0, 0, width, height);
    movie.setVolume(100.0);

    UserInterface ui(window, movie);
    StreamSelector selector(movie);
    displayShortcuts();

    movie.play();

    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            // Window closure
            if (ev.type == sf::Event::Closed ||
                    (ev.type == sf::Event::KeyPressed &&
                     ev.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (ev.type == sf::Event::KeyPressed)
            {
                switch (ev.key.code)
                {
                case sf::Keyboard::Space:
                    if (movie.getStatus() == sfe::Playing)
                        movie.pause();
                    else
                        movie.play();
                    break;

                case sf::Keyboard::A:
                    if (ev.key.alt)
                        selector.selectNextStream(sfe::Audio);
                    break;

                case sf::Keyboard::F:
                    fullscreen = !fullscreen;

                    if (fullscreen)
                        window.create(desktopMode, "sfeMovie Player", sf::Style::Fullscreen);
                    else
                        window.create(sf::VideoMode(width, height), "sfeMovie Player",
                                      sf::Style::Close | sf::Style::Resize);

                    window.setFramerateLimit(60);
                    window.setVerticalSyncEnabled(true);
                    movie.fit(0, 0, (float)window.getSize().x, (float)window.getSize().y);
                    ui.applyProperties();
                    break;

                case sf::Keyboard::H:
                    ui.toggleVisible();
                    break;

                case sf::Keyboard::I:
                    displayMediaInfo(movie);;
                    break;

                case sf::Keyboard::S:
                    if (ev.key.alt)
                        selector.selectNextStream(sfe::Subtitle);
                    else
                        movie.stop();
                    break;

                case sf::Keyboard::V:
                    if (ev.key.alt)
                        selector.selectNextStream(sfe::Video);
                default:
                    break;
                }
            }
            else if (ev.type == sf::Event::MouseWheelMoved)
            {
                float volume = movie.getVolume() + 10 * ev.mouseWheel.delta;
                volume = std::max(volume, 100.f);
                volume = std::min(volume, 0.f);
                movie.setVolume(volume);
                std::cout << "Volume changed to " << int(volume) << "%" << std::endl;
            }
            else if (ev.type == sf::Event::Resized)
            {
                movie.fit(0, 0, window.getSize().x, window.getSize().y);
                window.setView(sf::View(sf::FloatRect(0, 0, (float)window.getSize().x, (float)window.getSize().y)));
            }
            else if (ev.type == sf::Event::MouseButtonPressed ||
                     (ev.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
            {
                int xPos = 0;

                if (ev.type == sf::Event::MouseButtonPressed)
                    xPos = ev.mouseButton.x;
                else if (ev.type == sf::Event::MouseMoved)
                    xPos = ev.mouseMove.x;

                float ratio = static_cast<float>(xPos) / window.getSize().x;
                sf::Time targetTime = ratio * movie.getDuration();
                movie.setPlayingOffset(targetTime);
            }
        }

        movie.update();

        // Render movie
//        window.clear();
        window.draw(movie);
        ui.draw();
        window.display();
    }

    return 0;
}
