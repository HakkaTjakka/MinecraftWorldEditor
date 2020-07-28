#define SFML_STATIC

using namespace std;
//#undef UNICODE
//#include <winsock2.h>
//#include <io.h>
//#include "WinMain.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//#include <error.h>
//#include <cstdlib>
#include <Windows.h>
//#include <Winuser.h>
//#include <assert.h>
//#include <SFML/Audio.hpp>
//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
//#include <SFML/System.hpp>
#include <SFML/Network.hpp>
//#include <SFML/System/Mutex.hpp>
//#include <SFML/Network/IpAddress.hpp>
#include <iostream>

extern sf::Texture texture_from_internet;
extern int select_from_list(char *filename, char * path, int next);
extern bool file_exists(const char * filename);

select_url(char *filename, char * path) {
    static int next=0;
    static int total=0;
    next++;
    if (next>total) next=1;
    total=select_from_list(filename, path, next);
    if (total==0) return 0;
    return next;
}

extern char URLDIR[];
extern void savedata(char *naam, int data);

int GetFileFromInternet(char * naam) {
	sf::Http http;
	sf::Http::Request request;
	sf::Http::Response::Status status;
    sf::Http::Response response;
    char filenaam[1000];

	request.setMethod(sf::Http::Request::Get);
    int filenum=0;
    char url[4000]="";
    filenum=select_url(url,URLDIR);
    sprintf(filenaam,"%s/pic%05d.png",URLDIR,filenum);
    if (file_exists( filenaam)) {
        texture_from_internet.loadFromFile(filenaam);
        texture_from_internet.generateMipmap();
        return 0;
    }


    if (filenum==0) {
        savedata((char*)"URLDIR NOT SET? URLDIR EMPTY? NO LIST.TXT IN DIR?",0);
        savedata(url,0);
        savedata(URLDIR,0);
        strcpy(naam,url);
        return 1;
    }

    strcpy(naam,url);

    char ip[200]="";
    char page[4000]="";
    char ip2[200]="";
    char page2[4000]="";

    if (toupper(url[4])=='S') sscanf(url, "https://%199[^/]/%3999[^\n]", ip, page);
    else sscanf(url, "http://%199[^/]/%3999[^\n]", ip, page);

    if (toupper(url[4])=='S') strcpy(ip2,"https://");
    else strcpy(ip2,"http://");

    strcat(ip2,ip);
    strcat(ip2,"/");
    strcpy(page2,"/");
    strcat(page2,page);

//    savedata(ip2,0);
//    savedata(page2,0);
//    sscanf(text, "http://%199[^:]:%d/%3999[^\n]", ip, &port, page);

	http.setHost(ip2);
	request.setUri(page2);

	response = http.sendRequest(request);
	status = response.getStatus();

    if (status == sf::Http::Response::Ok)
    {
		if (    !texture_from_internet.loadFromMemory(   response.getBody().data(), response.getBody().size()  )     ) {
//				MessageBox(NULL,"LOADING PICTURE FAILED!","ERROR",MB_ICONEXCLAMATION | MB_OK);
                char filenaam[1000];
                sprintf(filenaam,"%s/error.txt",URLDIR);
                FILE* file = fopen (filenaam, "a");
                if (file!=NULL)
                {
                    fprintf (file, "%s\n",naam);
                    fclose (file);
                }
				return 1;
		} else {
                sprintf(filenaam,"%s/ok.txt",URLDIR);
                FILE* file = fopen (filenaam, "a");
                if (file!=NULL)
                {
                    fprintf (file, "%s\n",naam);
                    fclose (file);
                }
//                int timenow= time(0);
                sprintf(filenaam,"%s/pic%05d.png",URLDIR,filenum);
                texture_from_internet.copyToImage().saveToFile(filenaam);
				return 0;
		}
    }
    else
    {
    	char fout[10]="";
    	sprintf(fout,"%d",status);
        char filenaam[1000];
        sprintf(filenaam,"%s/error.txt",URLDIR);
        FILE* file = fopen (filenaam, "a");
        if (file!=NULL)
        {
            fprintf (file, "%s\n",naam);
            fclose (file);
        }
//		MessageBox(NULL,fout,"ERROR",MB_ICONEXCLAMATION | MB_OK);
		return 1;
    }
}

double BYTES_DOWNLOADED=0;
extern char SAS_URL[];
int count_errors=0;

int GetGoogleMap(char * url, sf::Texture * result) {
	sf::Http http;
	sf::Http::Request request;
	sf::Http::Response::Status status;
    sf::Http::Response response;

	request.setMethod(sf::Http::Request::Get);

    char ip[200]="";
    char page[4000]="";
    char ip2[200]="";
    char page2[4000]="";

    if (toupper(url[4])=='S') sscanf(url, "https://%199[^/]/%3999[^\n]", ip, page);
    else sscanf(url, "http://%199[^/]/%3999[^\n]", ip, page);

    if (toupper(url[4])=='S') strcpy(ip2,"https://");
    else strcpy(ip2,"http://");

    if (toupper(url[4])=='S') {
        return 1;
    }

    strcat(ip2,ip);
    strcat(ip2,"/");
    strcpy(page2,"/");
    strcat(page2,page);

	http.setHost(ip2);
	request.setUri(page2);

	response = http.sendRequest(request);
	status = response.getStatus();

    if (status == sf::Http::Response::Ok)
    {
		if (    !result->loadFromMemory(   response.getBody().data(), response.getBody().size()  )     ) {
                count_errors++;
				return 1;
		} else {
                BYTES_DOWNLOADED+=response.getBody().size();
				return 0;
		}
    }
    else
    {
//        printf("Loading from internet: %s",url);
        count_errors++;
    	printf("\nGetGoogleMap() failed. Status: %d\n",status);
		return (int)status;
    }
}

