//
// Created by oleksandr on 23/09/2021.
//

#include "client.h"
#include <iostream>
#include<cstdio>
#include<cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
int mainClientFunc(int argc, char* argv[],int port) {

    std::string prefix = "CLIENT>";
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char textFromServer[4096] = {0};


    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);


    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection failed:( \n");
        return -1;
    }

    std::cout << "Hi! Please, enter the search context:\n"
                 "Enter \"finish\" keyword to finish\n";

    std::string searchContext;/*= "GET Who";*/
    while(true) {
        //std::cin.ignore();
        std::cin >> searchContext;

        send(sock, searchContext.c_str(), searchContext.length() + 1, 0);

        char buffer[1024];
        read(sock, buffer, 1024);
        std::cout << "Received from server: \n" << buffer << '\n';
        if(searchContext == "finish") break;
    }
    return 0;

}