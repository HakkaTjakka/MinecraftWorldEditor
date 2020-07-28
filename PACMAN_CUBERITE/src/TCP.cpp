#define SFML_STATIC

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

extern HWND TextBox, SendButton, TextField;
extern char connectedip[100];

////////////////////////////////////////////////////////////
/// Launch a server, wait for an incoming connection,
/// send a message and wait for the answer.
///
////////////////////////////////////////////////////////////

sf::TcpListener listener1;
sf::TcpListener listener2;
sf::TcpSocket internet_socket_tcp1;
sf::TcpSocket internet_socket_tcp2;


int runTcpServer(unsigned short port)
{
	char port_text[10];
    char in[128];
    const char out[] = "Hi, I'm the server";
	std::string address;
	unsigned short remoteport;
    std::size_t received;

//	itoa(port,port_text,10);
    sprintf(port_text,"%d",port);

    if (listener1.listen(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED LISTENING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER IS LISTENING TO PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING TO RECEIVE MESSAGE FROM CLIENT\r\n");

    if (listener1.accept(internet_socket_tcp1) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}

//    sf::IpAddress * addr = new sf::IpAddress;
//    addr=internet_socket_tcp1.getRemoteAddress();
//    address=addr->toString();



	address=internet_socket_tcp1.getRemoteAddress().toString();
	strcpy(connectedip,&address[0]);




	remoteport=internet_socket_tcp1.getRemotePort();
//	itoa(remoteport,port_text,10);
    sprintf(port_text,"%d",remoteport);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT CONNECTED: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&address[0]);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING MESSAGE TO CLIENT\r\n");
    if (internet_socket_tcp1.send(out, sizeof(out)) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE TO CLIENT\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING TO RECEIVE MESSAGE FROM CLIENT\r\n");

	if (internet_socket_tcp1.receive(in, sizeof(in), received) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED RECEIVING MESSAGE FROM CLIENT\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"ANSWER RECEIVED FROM THE CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	port++;

    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);

    if (listener2.listen(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED LISTENING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER IS LISTENING TO PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    if (listener2.accept(internet_socket_tcp2) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}

//	address=internet_socket_tcp2.getRemoteAddress().toString();
//	strcpy(connectedip,&address[0]);

	remoteport=internet_socket_tcp2.getRemotePort();
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT CONNECTED: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&address[0]);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING MESSAGE TO CLIENT\r\n");
    if (internet_socket_tcp2.send(out, sizeof(out)) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE TO CLIENT\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING TO RECEIVE MESSAGE FROM CLIENT\r\n");

	if (internet_socket_tcp2.receive(in, sizeof(in), received) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED RECEIVING MESSAGE FROM CLIENT\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"ANSWER RECEIVED FROM THE CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	return 1;
}


////////////////////////////////////////////////////////////
/// Create a client, connect it to a server, display the
/// welcome message and send an answer.
///
////////////////////////////////////////////////////////////
int runTcpClient(char * ipaddress, unsigned short port)
{
    sf::IpAddress server;
	char port_text[10];
    const char out[] = "Hi, I'm a client";
    char in[128];
    std::size_t received;
	unsigned short remoteport;

    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);

	server=ipaddress;

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING FOR SERVER\r\n");

    if (server == sf::IpAddress::None) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"INVALLID IP ADDRESS, TRY AGAIN\r\n");
		return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTING ON PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	int i=0;
    if (internet_socket_tcp1.connect(server, port) != sf::Socket::Done) {
		internet_socket_tcp1.setBlocking(false);
		sf::Time Timeout =sf::milliseconds(1500);

		for (i=0; i<15; i++) {
		    if (internet_socket_tcp1.connect(server, port, Timeout) != sf::Socket::Done) {
	//	    if (internet_socket_tcp1.connect(server, port, Timeout ) == sf::Socket::NotReady) {
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED CONNECTING TO SERVER\r\n");
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"TRYING AGAIN ");
                sprintf(port_text,"%d",15-i);
//				itoa(15-i,port_text,10);
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" TIMES\r\n");
				Sleep(1500);
			}
		}
		internet_socket_tcp1.setBlocking(true);
	}


    if (i==15) if (internet_socket_tcp1.connect(server, port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED CONNECTING TO SERVER\r\n");
	    return 0;
	}

	remoteport=internet_socket_tcp1.getRemotePort();
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTED TO SERVER ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)ipaddress);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING MESSAGE TO SERVER\r\n");

    if (internet_socket_tcp1.send(out, sizeof(out)) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING FOR MESSAGE\r\n");

    if (internet_socket_tcp1.receive(in, sizeof(in), received) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED RECEIVING MESSAGE\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE RECEIVED FROM SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	port++;

//	Sleep(1000);
    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);

  	if (server == sf::IpAddress::None) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"INVALLID IP ADDRESS, TRY AGAIN\r\n");
		return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTING ON PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    if (internet_socket_tcp2.connect(server, port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED CONNECTING TO SERVER\r\n");
	    return 0;
	}

	remoteport=internet_socket_tcp2.getRemotePort();
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTED TO SERVER ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)ipaddress);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING MESSAGE TO SERVER\r\n");

    if (internet_socket_tcp2.send(out, sizeof(out)) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING FOR MESSAGE\r\n");
    if (internet_socket_tcp2.receive(in, sizeof(in), received) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED RECEIVING MESSAGE\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE RECEIVED FROM SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	return 1;
}



int reconnectTcpServer(unsigned short port)
{
	char port_text[10];
	std::string address;
	unsigned short remoteport;

    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"LISTENING PORT\r\n");
    if (listener1.listen(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED LISTENING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

    if (listener1.accept(internet_socket_tcp1) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}

//    sf::IpAddress * addr = new sf::IpAddress;
//    addr=internet_socket_tcp1.getRemoteAddress();
//   	address=addr->toString();

	address=internet_socket_tcp1.getRemoteAddress().toString();
	strcpy(connectedip,&address[0]);

	remoteport=internet_socket_tcp1.getRemotePort();
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT CONNECTED: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&address[0]);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");


    if (internet_socket_tcp1.send("T=RECONNECT,", strlen("T=RECONNECT,")) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}

	port++;

    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);

    if (listener2.listen(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED LISTENING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER IS LISTENING TO PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    if (listener2.accept(internet_socket_tcp2) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}

	remoteport=internet_socket_tcp2.getRemotePort();
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT CONNECTED: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&address[0]);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");


    if (internet_socket_tcp2.send("T=RECONNECT,", strlen("T=RECONNECT,")) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}

	return 1;
}


////////////////////////////////////////////////////////////
/// Create a client, connect it to a server, display the
/// welcome message and send an answer.
///
////////////////////////////////////////////////////////////
int reconnectTcpClient(char * ipaddress, unsigned short port)
{
	char port_text[10];
	std::string address;
	unsigned short remoteport;
    sf::IpAddress server;

	server=ipaddress;

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING FOR SERVER\r\n");

    if (server == sf::IpAddress::None) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"INVALLID IP ADDRESS, TRY AGAIN\r\n");
		return 0;
	}

    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTING ON PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	int i=0;
    if (internet_socket_tcp1.connect(server, port) != sf::Socket::Done) {
		internet_socket_tcp1.setBlocking(false);
		sf::Time Timeout =sf::milliseconds(1500);

		for (i=0; i<15; i++) {
		    if (internet_socket_tcp1.connect(server, port, Timeout) != sf::Socket::Done) {
	//	    if (internet_socket_tcp1.connect(server, port, Timeout ) == sf::Socket::NotReady) {
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED CONNECTING TO SERVER\r\n");
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"TRYING AGAIN ");
                sprintf(port_text,"%d",15-i);
//				itoa(15-i,port_text,10);
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" TIMES\r\n");
				Sleep(1500);
			}
		}
		internet_socket_tcp1.setBlocking(true);
	}

    if (i==15) if (internet_socket_tcp1.connect(server, port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED CONNECTING TO SERVER\r\n");
	    return 0;
	}

	remoteport=internet_socket_tcp1.getRemotePort();
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTED TO SERVER ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)ipaddress);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");



    if (internet_socket_tcp1.send("T=RECONNECT,", strlen("T=RECONNECT,")) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}

	port++;

//	Sleep(1000);
    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);

  	if (server == sf::IpAddress::None) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"INVALLID IP ADDRESS, TRY AGAIN\r\n");
		return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTING ON PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    if (internet_socket_tcp2.connect(server, port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED CONNECTING TO SERVER\r\n");
	    return 0;
	}

	remoteport=internet_socket_tcp2.getRemotePort();
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTED TO SERVER ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)ipaddress);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

/*
    if (internet_socket_tcp2.send("T=RECONNECT,", strlen("T=RECONNECT,")) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}
*/

	return 1;
}
