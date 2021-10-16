//
// Created by oleksandr on 23/09/2021.
//

#include "client.h"
#include <iostream>
#include<cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int mainClientFunc(int argc, char* argv[],int port) {

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char textFromServer[4096] = {0};
    std::string textFromServerString;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);


    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed:( \n");
        return -1;
    }

    std::cout << "Hi!\n";

    char passwordSize[32];
    read(sock, passwordSize, 1024);

    std::cout << "Password size is " << passwordSize << '\n';
    std::cout << "Please, try to guess server password:\n";
    while(true) {
        std::string password;
        std::cin >> password;
        send(sock, password.c_str(), password.length() + 1, 0);

        //read result strings from server storage
        read(sock, textFromServer, 1024);
        std::cout << textFromServer << '\n';
        if((std::string)textFromServer != "Try again:(") {
            break;
        }
    }


    return 0;
}