//
// Created by oleksandr on 23/09/2021.
//

#include "client.h"
#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int mainClientFunc(int argc, char* argv[],int port) {

    std::string prefix = "CLIENT>";
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[4096] = {0};


    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);


    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection failed:( \n");
        return -1;
    }
    std::string messageToServer;

    //messageToServer = "2 + 3\n";
    std::getline(std::cin, messageToServer);
    send(sock , messageToServer.c_str() , messageToServer.length(), 0 );
    //   std::cout << prefix + "Message to server sent!\n";

    valread = read( sock , buffer, 4096);

    std::cout << prefix + "Received from server: " << buffer << '\n';
    return 0;

}