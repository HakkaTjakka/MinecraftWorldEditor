#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include "WinMain.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <Winuser.h>
#include <assert.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <dirent.h>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <sfeMovie/Movie.hpp>
#include "StreamSelector.hpp"
#include "MediaInfo.hpp"

int MyBlending=0;
int MyBlendMode_num=0;
int MyBlend_colorSrcFactor_num=1;
int MyBlend_colorDstFactor_num=1;
int MyBlend_colorEquation_num=0;
int MyBlend_alphaSrcFactor_num=0;
int MyBlend_alphaDstFactor_num=6;
int MyBlend_alphaEquation_num=0;

sf::BlendMode MyBlendingMode(sf::BlendMode::One,sf::BlendMode::One,sf::BlendMode::Add,
                             sf::BlendMode::One,sf::BlendMode::SrcAlpha,sf::BlendMode::Add);


sf::BlendMode MyBlendMode[]=
{
    sf::BlendAdd,
    sf::BlendNone,
    sf::BlendAlpha,
    sf::BlendMultiply,
    MyBlendingMode
};

char * MyBlendMode_text[]=
{
    "Add",
    "None",
    "Alpha",
    "Multiply",
    "Custom"
};

sf::BlendMode::Equation MyEquation[]=
{
    sf::BlendMode::Add,
    sf::BlendMode::Subtract,
    sf::BlendMode::ReverseSubtract,
};

char * MyEquation_text[]=
{
    "Add",
    "Subtract",
    "ReverseSubtract"
};

sf::BlendMode::Factor MyFactor[]=
{
    sf::BlendMode::Zero,
    sf::BlendMode::One,
    sf::BlendMode::SrcColor,
    sf::BlendMode::OneMinusSrcColor,
    sf::BlendMode::DstColor,
    sf::BlendMode::OneMinusDstColor,
    sf::BlendMode::SrcAlpha,
    sf::BlendMode::OneMinusSrcAlpha,
    sf::BlendMode::DstAlpha,
    sf::BlendMode::OneMinusDstAlpha
};

char * MyFactor_text[]=
{
    "Zero",
    "One",
    "SrcColor",
    "OneMinusSrcColor",
    "DstColor",
    "OneMinusDstColor",
    "SrcAlpha",
    "OneMinusSrcAlpha",
    "DstAlpha",
    "OneMinusDstAlpha"
};

extern char error_msg4[];
extern int error_flag4;
extern char error_msg5[];
extern int error_flag5;


void set_blending()
{
    MyBlendingMode=MyBlendMode[MyBlendMode_num];

    if (MyBlendMode_num==4)
    {
        MyBlendMode[MyBlendMode_num].colorSrcFactor    = MyFactor[MyBlend_colorSrcFactor_num];
        MyBlendMode[MyBlendMode_num].colorDstFactor    = MyFactor[MyBlend_colorDstFactor_num];
        MyBlendMode[MyBlendMode_num].colorEquation     = MyEquation[MyBlend_colorEquation_num];

        MyBlendMode[MyBlendMode_num].alphaSrcFactor    = MyFactor[MyBlend_alphaSrcFactor_num];
        MyBlendMode[MyBlendMode_num].alphaDstFactor    = MyFactor[MyBlend_alphaDstFactor_num];
        MyBlendMode[MyBlendMode_num].alphaEquation     = MyEquation[MyBlend_alphaEquation_num];
    }

    MyBlendingMode.colorSrcFactor    = MyBlendMode[MyBlendMode_num].colorSrcFactor;
    MyBlendingMode.colorDstFactor    = MyBlendMode[MyBlendMode_num].colorDstFactor;
    MyBlendingMode.colorEquation     = MyBlendMode[MyBlendMode_num].colorEquation;
    MyBlendingMode.alphaSrcFactor    = MyBlendMode[MyBlendMode_num].alphaSrcFactor;
    MyBlendingMode.alphaDstFactor    = MyBlendMode[MyBlendMode_num].alphaDstFactor;
    MyBlendingMode.alphaEquation     = MyBlendMode[MyBlendMode_num].alphaEquation;

    sprintf(error_msg4,"Mode: Mode (colorSrcFactor, colorDstFactor, colorEquation, alphaSrcFactor, alphaDstFactor, alphaEquation)");
    error_flag4=2;

    sprintf(error_msg5,"Mode: %s (%s, %s, %s, %s, %s, %s)",
            MyBlendMode_text[MyBlendMode_num],
            MyFactor_text[MyBlendingMode.colorSrcFactor],
            MyFactor_text[MyBlendingMode.colorDstFactor],
            MyEquation_text[MyBlendingMode.colorEquation],
            MyFactor_text[MyBlendingMode.alphaSrcFactor],
            MyFactor_text[MyBlendingMode.alphaDstFactor],
            MyEquation_text[MyBlendingMode.alphaEquation]
           );
    error_flag5=2;
}

