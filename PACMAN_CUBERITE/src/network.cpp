// add -U__STRICT_ANSI__ to compiler settings -> other compiler options!!!! (popen() function for ffmpeg recording).
// add SFML_STATIC to compiler settings -> #defines
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

extern int runTcpServer(unsigned short port);
extern int runTcpClient(char * ipaddress, unsigned short port);
extern int runUdpServer(unsigned short port);
extern int runUdpClient(char * ipaddress, unsigned short port);
extern int reconnectTcpServer(unsigned short port);
extern int reconnectTcpClient(char * ipaddress, unsigned short port);
extern int reconnectUdpServer(unsigned short port);
extern int reconnectUdpClient(char * ipaddress, unsigned short port);

void SEND(char *towrite);
void acceptorfunc();
void connectorfunc();

extern int udp;
extern int tcp;
extern HWND TextBox, SendButton, TextField;
extern HINSTANCE hInstance2;
extern HWND hWndMain2;
extern int server;
extern int client;
extern unsigned short portnumber;
extern int connected;
extern int SFML;
extern sf::RenderWindow SFMLView1;
extern int connecting;
extern char writer[];
extern sf::TcpSocket internet_socket_tcp1;
extern sf::TcpSocket internet_socket_tcp2;
extern sf::UdpSocket internet_socket_udp1;
extern sf::UdpSocket internet_socket_udp2;
extern std::size_t received;
extern std::size_t sent;
extern sf::IpAddress dummy_address;
extern unsigned short dummyPort;
extern sf::TcpListener listener1;
extern sf::TcpListener listener2;
extern sf::IpAddress sender;
extern sf::IpAddress server_address;
extern unsigned short senderPort1;
extern unsigned short senderPort2;
extern int accepted_ready;
extern char in[];
extern int old_mazemovex;
extern int old_mazemovey;
extern int thread_mazemovex;
extern int thread_mazemovey;
extern int playerleft;
extern int pen;
extern int sending_pos;
extern char out[];
extern char lastmove;
extern void SEND(char *towrite);
extern int connected_ready;

sf::Thread acceptor(&acceptorfunc);
sf::Thread connector(&connectorfunc);

extern int REMOTE_ALIVE;
extern int follow_ghost;
extern int inpointer;
extern char connectedip[];

void terminate_thread() {
    connector.terminate();
}
extern int MULTIPLAYER;
void INIT_NETWORK()
{
    int msgboxID=IDYES;
    int protocol;
    int reconnect;

    if (MULTIPLAYER==-1) {
        msgboxID = MessageBox(
                   NULL,
                   "MULTIPLAYER GAME?",
                   "PLEASE SELECT",
                   MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2
                    );
        if (msgboxID == IDNO)
            return;
    }

    if (msgboxID == IDYES)
    {
        msgboxID = MessageBox(
                       NULL,
                       "DO YOU WANT TO BE THE SERVER?\n"
                       "YES FOR SERVER OR NO FOR CLIENT",
                       "PLEASE SELECT",
                       MB_ICONEXCLAMATION | MB_YESNOCANCEL
                   );

        if (msgboxID == IDCANCEL)
            return;

        protocol = MessageBox(
                       NULL,
                       "TCP OR UDP PROTOCOL?\n"
                       "YES FOR TCP OR NO FOR UDP",
                       "PLEASE SELECT",
                       MB_ICONEXCLAMATION | MB_YESNOCANCEL
                   );

        if (protocol == IDCANCEL)
            return;
        if (protocol == IDYES)
        {
            tcp=1;
            udp=0;
        }
        else if (protocol == IDNO)
        {
            tcp=0;
            udp=1;
        }

        TextField = CreateWindow("EDIT",
                                 "",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_MULTILINE | ES_AUTOVSCROLL,
                                 10, 90, 565, 400,
//		                         WindowHandle, (HMENU) 3, NULL, NULL);
                                 hWndMain2, (HMENU) 3, NULL, NULL);

        if (msgboxID == IDNO)
            TextBox = CreateWindow("EDIT",
                                   "",
                                   WS_BORDER | WS_CHILD | WS_VISIBLE,
                                   10, 500, 390, 20,
                                   hWndMain2, (HMENU) 1, NULL, NULL);
//			                       WindowHandle, (HMENU) 1, NULL, NULL);

        if (msgboxID == IDNO)
            SendButton = CreateWindow("BUTTON",
                                      "SEND IP ADDRESS",
                                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      410, 500, 165, 20,
                                      hWndMain2, (HMENU) 2, NULL, NULL);
//			                          WindowHandle, (HMENU) 2, NULL, NULL);


        if (msgboxID == IDYES)
        {
            SendMessage(TextField, EM_SETSEL, -1, -1);
            SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"STARTING SERVER\r\n");
            UpdateWindow(hWndMain2);

            reconnect = MessageBox(
                            NULL,
                            "RECONNECT FROM PREVIOUS?\n"
                            "YES FOR RECONNECT NO FOR NEW CONNECTION",
                            "PLEASE SELECT",
                            MB_ICONEXCLAMATION | MB_YESNO | MB_DEFBUTTON2
                        );

            if (reconnect == IDYES)
            {
                if (udp==1)
                    server=reconnectUdpServer(portnumber);
                else if (tcp==1)
                    server=reconnectTcpServer(portnumber);
            }
            else
            {
                if (tcp==1)
                    server=runTcpServer(portnumber);
                else if (udp==1)
                    server=runUdpServer(portnumber);
            }

            if (server==0)
            {
                MessageBox(
                    NULL,
                    "CONNECTION FAILED",
                    "ERROR",
                    MB_ICONEXCLAMATION | MB_YESNO
                );
            }
            else
            {
                connected=1;
                if (SFML==1)
                {
                    SFMLView1.requestFocus();
                    SFMLView1.setActive(true);
                }
            }
        }
        else
        {
            UpdateWindow(hWndMain2);
            connecting=1;
        }

        if (connecting==0)
        {
            DestroyWindow(TextField);
            if (msgboxID == IDNO)
                DestroyWindow(TextBox);
            if (msgboxID == IDNO)
                DestroyWindow(SendButton);
        }
    }
}


void NETWORK_HANDLER2()
{
    static char debug[1200];
    static char gelezen[256*256];
    static int local_thread_mazemovex;
    static int local_thread_mazemovey;
    static int local_old_mazemovex;
    static int local_old_mazemovey;
    static char movement;

    local_thread_mazemovex=thread_mazemovex;
    local_thread_mazemovey=thread_mazemovey;
    local_old_mazemovex=old_mazemovex;
    local_old_mazemovey=old_mazemovey;
    old_mazemovex=thread_mazemovex;
    old_mazemovey=thread_mazemovey;

    if (client==1)
    {
        if ( ( (local_old_mazemovex!=local_thread_mazemovex) || (local_old_mazemovey!=local_thread_mazemovey) ) && playerleft==0 && pen==0 && sending_pos==1)
        {
            sprintf(out,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
            SEND(out);
        }
        sending_pos=1;
        if (playerleft==1)
        {
            if (tcp==1)
            {
                if (connected_ready==2)
                {
                    connected_ready=0;
                    connector.launch();
                }
                if (connected_ready==1)
                {
                    connector.terminate();
                    connected_ready=2;
                    playerleft=0;
                    REMOTE_ALIVE=10000;
                    sprintf(out,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
                    SEND(out);
                }
            }
            else if (udp==1)
            {
                static int counter=50;
                counter--;
                if (counter==0)
                {
                    sprintf(writer,"%d\0",internet_socket_udp2.getLocalPort());
                    SEND(writer);
                    counter=50;
                }
            }
        }
        if (playerleft==0)
        {
            if (tcp==1)
            {
                internet_socket_tcp2.receive(gelezen, sizeof(gelezen), received);
            }
        }
        if (udp==1)
        {
            internet_socket_udp2.receive(gelezen, sizeof(gelezen), received, dummy_address, dummyPort);
            if (received>0)
            {
                if (playerleft==1)
                {
                    REMOTE_ALIVE=10000;
                    playerleft=0;
                    sprintf(out,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
                    SEND(out);
                }
            }
        }
    }
    else if (server==1)
    {
        if ( ( (local_old_mazemovex!=local_thread_mazemovex) || (local_old_mazemovey!=local_thread_mazemovey) ) && playerleft==0 && pen==0 && sending_pos==1)
        {
            sprintf(out,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
            SEND(out);
        }
        sending_pos=1;
        static int accepted_ready=2;
        if (playerleft==1)
        {
            if (tcp==1)
            {
                static int accepted1=0;
                static int accepted2=0;

                if (accepted1==0)
                    if (listener1.accept(internet_socket_tcp1) == sf::Socket::Done)
                    {
                        accepted1=1;
                    }
                if (accepted2==0)
                    if (listener2.accept(internet_socket_tcp2) == sf::Socket::Done)
                    {
                        accepted2=1;
                    }

                if (accepted1==1 && accepted2==1)
                {
                    accepted1=0;
                    accepted2=0;
                    accepted_ready=2;
                    playerleft=0;
                    REMOTE_ALIVE=10000;
                    sprintf(out,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
                    SEND(out);
                }
                else
                    accepted_ready=0;
            }
            else if (udp==1)
                internet_socket_udp2.receive(gelezen, sizeof(gelezen), received, dummy_address, dummyPort);
            if (gelezen>0)
            {
                if (udp==1)
                {
                    sender=dummy_address;
                    senderPort2=dummyPort;
                }
                else if (tcp==1) {}
                received=0;
                sprintf(out,"T=POS,X=%d,Y=%d,M=%c,\0", thread_mazemovex,thread_mazemovey,lastmove);
                if(accepted_ready==2)
                    if (tcp==1)
                        SEND(out);
                if (udp==1)
                    SEND(out);

            }
        }
        if (accepted_ready==2)
        {
            if (tcp==1)
                internet_socket_tcp1.receive(gelezen, sizeof(gelezen), received);
            else if (udp==1)
                internet_socket_udp1.receive(gelezen, sizeof(gelezen), received, dummy_address, dummyPort);
        }
        if (received>0)
        {
            REMOTE_ALIVE=10000;
            playerleft=0;
        }
    }
    gelezen[received]= '\0';
    if (received>0)
    {
        strcat(in,gelezen);
        inpointer+=received;
        gelezen[0]='\0';
        received=0;
    }
}

void acceptorfunc()
{
    int accepted1=0;
    int accepted2=0;

    while (accepted1==0 || accepted2==0)
    {
        if (accepted1==0)
            if (listener1.accept(internet_socket_tcp1) == sf::Socket::Done)
            {
                accepted1=1;
            }
        if (accepted2==0)
            if (listener2.accept(internet_socket_tcp2) == sf::Socket::Done)
            {
                accepted2=1;
            }
    }

    if (accepted1==1 && accepted2==1)
    {
        accepted1=0;
        accepted2=0;
        accepted_ready=1;
    }

    accepted_ready=1;
}


void connectorfunc()
{
    int connected1=0;
    int connected2=0;
    sf::Time Timeout =sf:: milliseconds(300);

    sf::IpAddress a0000(0,0,0,0);

    internet_socket_tcp1.setBlocking(true);
    internet_socket_tcp2.setBlocking(true);
    Sleep(5000);

    while (connected1==0 || connected2==0)
    {
        if (connected1==0)
            if (internet_socket_tcp1.connect(connectedip,portnumber) != sf::Socket::NotReady)
                connected1=1;
        if (connected2==0)
            if (internet_socket_tcp2.connect(connectedip,portnumber+1) != sf::Socket::NotReady)
                connected2=1;

        if (internet_socket_tcp1.getRemotePort()==0)
            connected1=0;
        if (internet_socket_tcp2.getRemotePort()==0)
            connected2=0;
    }

    connected_ready=1;

    internet_socket_tcp1.setBlocking(false);
    internet_socket_tcp2.setBlocking(false);

}

void SEND(char *towrite)
{
    if (follow_ghost==0)
    {
        if (client==1)
        {
            if (udp==1)
                internet_socket_udp1.send(towrite, strlen(towrite), server_address, portnumber);
            else if (tcp==1)
                internet_socket_tcp1.send(towrite, strlen(towrite));
        }
        if (server==1)
        {
            if (tcp==1)
                internet_socket_tcp2.send(towrite, strlen(towrite));
            else if (udp==1)
                internet_socket_udp2.send(towrite, strlen(towrite), sender, senderPort2);
        }
    }
    return;
}
