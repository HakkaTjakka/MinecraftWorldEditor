#define SFML_STATIC

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network.hpp>
#include <iostream>
#include <Windows.h>
#include <string>

extern HWND TextBox, SendButton, TextField;
extern char connectedip[100];
extern void savedata(char *naam, int data);
extern int playerleft;


////////////////////////////////////////////////////////////
/// Launch a server, wait for a message, send an answer.
///
////////////////////////////////////////////////////////////

sf::UdpSocket internet_socket_udp1;
sf::UdpSocket internet_socket_udp2;
sf::IpAddress sender;
sf::IpAddress server_address;
unsigned short senderPort1;
unsigned short senderPort2;

int runUdpServer(unsigned short port) {
	char port_text[10];
    char in[128];
    std::size_t received;
	std::string address;
	unsigned short remoteport;
    const char out[] = "Hi, I'm the server";


    sprintf(port_text,"%d",port);
//    itoa(port,port_text,10);

    if (internet_socket_udp1.bind(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED BINDING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER IS LISTENING ON PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING TO RECEIVE MESSAGE FROM CLIENT\r\n");

    if (internet_socket_udp1.receive(in, sizeof(in), received, sender, senderPort1) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}

	address=sender.toString();
	strcpy(connectedip,&address[0]);
//	savedata(&address[0],0);

	remoteport=senderPort1;
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT CONNECTED: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&address[0]);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE RECEIVED FROM THE CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING ANSWER TO CLIENT\r\n");

    if (internet_socket_udp1.send(out, strlen(out), sender, senderPort1) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING ANSWER TO CLIENT\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO THE CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	port++;

    sprintf(port_text,"%d",port);

//	itoa(port,port_text,10);
    if (internet_socket_udp2.bind(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED BINDING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER IS LISTENING TO PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING TO RECEIVE MESSAGE FROM CLIENT\r\n");

    if (internet_socket_udp2.receive(in, sizeof(in), received, sender, senderPort2) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}

	address=sender.toString();
	strcpy(connectedip,&address[0]);

	remoteport=senderPort2;
    sprintf(port_text,"%d",remoteport);
//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CLIENT CONNECTED: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)&address[0]);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE RECEIVED FROM THE CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING ANSWER TO CLIENT\r\n");

    if (internet_socket_udp2.send(out, strlen(out), sender, senderPort2) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING ANSWER TO CLIENT\r\n");
        return 0;
	}
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO THE CLIENT: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	return 1;
}


////////////////////////////////////////////////////////////
/// Send a message to the server, wait for the answer
///
////////////////////////////////////////////////////////////
int runUdpClient(char * ipaddress, unsigned short port)
{
	unsigned short remoteport;
	std::string address;
    const char out[] = "Hi, I'm a client";
	char port_text[10];
    char in[128];
    std::size_t received;

    sprintf(port_text,"%d",port);
//	itoa(port,port_text,10);
	server_address=ipaddress;

    if (server_address == sf::IpAddress::None) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"INVALLID IP ADDRESS, TRY AGAIN\r\n");
		return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING FOR SERVER\r\n");

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING MESSAGE TO SERVER TO PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    if (internet_socket_udp1.send(out, strlen(out), server_address, port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING FOR AWNSER\r\n");

	internet_socket_udp1.setBlocking(false);
	Sleep(100);
	int i=0;
//    if (internet_socket_udp1.receive(in, sizeof(in), received, sender, senderPort1) != sf::Socket::Done) {
    if (internet_socket_udp1.receive(in, sizeof(in), received, sender, senderPort1) != sf::Socket::Done) {

		for (i=0; i<15; i++) {
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"NO AWNSER, TRYING AGAIN ");
            sprintf(port_text,"%d",15-i);
//			itoa(15-i,port_text,10);
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" TIMES\r\n");

			internet_socket_udp1.setBlocking(true);
		    if (internet_socket_udp1.send(out, strlen(out), server_address, port) != sf::Socket::Done) {
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
		        return 0;
			}
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO SERVER ");
			internet_socket_udp1.setBlocking(false);
			Sleep(1000);
		    if (internet_socket_udp1.receive(in, sizeof(in), received, sender, senderPort1) == sf::Socket::Done) i=15;
		}
		if (received==0) {
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER NOT RESPONDING\r\n");
			return 0;
		}
	}
	internet_socket_udp1.setBlocking(true);

	address=sender.toString();
	strcpy(connectedip,&address[0]);

	remoteport=senderPort1;
    sprintf(port_text,"%d",remoteport);

//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"AWNSER RECEIVED FROM SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

	port++;

    sprintf(port_text,"%d",port);

//	itoa(port,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SENDING MESSAGE TO SERVER ON PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    if (internet_socket_udp2.send(out, strlen(out), server_address, port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
        return 0;
	}

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)out);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"WAITING FOR AWNSER\r\n");

	internet_socket_udp2.setBlocking(false);
	Sleep(100);
//    if (internet_socket_udp1.receive(in, sizeof(in), received, sender, senderPort1) != sf::Socket::Done) {
    if (internet_socket_udp2.receive(in, strlen(in), received, sender, senderPort2) != sf::Socket::Done) {

		for (i=0; i<15; i++) {
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"NO AWNSER, TRYING AGAIN ");
            sprintf(port_text,"%d",15-i);

//			itoa(15-i,port_text,10);
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)" TIMES\r\n");

			internet_socket_udp2.setBlocking(true);
		    if (internet_socket_udp2.send(out, strlen(out), server_address, port) != sf::Socket::Done) {
				SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING MESSAGE\r\n");
		        return 0;
			}
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"MESSAGE SEND TO SERVER ");
			internet_socket_udp2.setBlocking(false);
			Sleep(1500);
		    if (internet_socket_udp2.receive(in, sizeof(in), received, sender, senderPort2) == sf::Socket::Done) i=15;
		}
		if (received==0) {
			SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"SERVER NOT RESPONDING\r\n");
			return 0;
		}
	}
	internet_socket_udp2.setBlocking(true);

	address=sender.toString();
	strcpy(connectedip,&address[0]);

	remoteport=senderPort2;
    sprintf(port_text,"%d",remoteport);

//	itoa(remoteport,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"AWNSER RECEIVED FROM SERVER: ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)in);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"REMOTE PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    return 1;
}

int reconnectUdpServer(unsigned short port) {
	char port_text[10];
    char in[128];
    std::size_t received;
	std::string address;
	unsigned short remoteport;

    sprintf(port_text,"%d",port);

//	itoa(port,port_text,10);

	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"BINDING TO PORT ");
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
	SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");

    if (internet_socket_udp1.bind(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED BINDING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

    if (internet_socket_udp1.receive(in, sizeof(in), received, sender, senderPort1) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}
	in[received]='\0';

	address=sender.toString();
	strcpy(connectedip,&address[0]);
//	savedata(&address[0],0);

	remoteport=senderPort1;
    sprintf(port_text,"%d",remoteport);

//	itoa(remoteport,port_text,10);

	port++;


    sprintf(port_text,"%d",port);

//	itoa(port,port_text,10);
    if (internet_socket_udp2.bind(port) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED BINDING TO PORT ");
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)port_text);
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"\r\n");
        return 0;
	}

/*
    if (internet_socket_udp2.receive(in, sizeof(in), received, sender, senderPort2) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"CONNECTION FAILED\r\n");
        return 0;
	}

	address=sender.toString();
	strcpy(connectedip,&address[0]);

	remoteport=senderPort2;
	itoa(remoteport,port_text,10);


*/

/*
    if (internet_socket_udp1.send("T=RECONNECT,", strlen("T=RECONNECT,"), sender, senderPort1) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING ANSWER TO CLIENT\r\n");
        return 0;
	}
*/

	senderPort2=atoi(in);

    if (internet_socket_udp2.send("T=RECONNECT,", strlen("T=RECONNECT,"), sender, senderPort2) != sf::Socket::Done) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"FAILED SENDING ANSWER TO CLIENT\r\n");
        return 0;
	}

	return 1;
}


////////////////////////////////////////////////////////////
/// Send a message to the server, wait for the answer
///
////////////////////////////////////////////////////////////
int reconnectUdpClient(char * ipaddress, unsigned short port)
{
	server_address=ipaddress;

    if (server_address == sf::IpAddress::None) {
		SendMessage(TextField, EM_REPLACESEL, 0, (LPARAM)"INVALLID IP ADDRESS, TRY AGAIN\r\n");
		return 0;
	}
	internet_socket_udp1.setBlocking(false);
	internet_socket_udp2.setBlocking(false);
    internet_socket_udp1.send("T=RECONNECT,", strlen("T=RECONNECT,"), server_address, port);
    port++;
    internet_socket_udp2.send("T=RECONNECT,", strlen("T=RECONNECT,"), server_address, port);

    return 1;
}













