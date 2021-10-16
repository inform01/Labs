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

    std::cout << "Hi! Please, enter the protocol request:\n"
                 "Request string example:\n"
                 "P Who\n"
                 "(P - header used for tell server you gonna Play, Who - command for see project info)\n";
    std::string ProtocolRequest;/*= "GET Who";*/

    std::cin.ignore();
    getline(std::cin, ProtocolRequest);
    std::cout << ProtocolRequest << '\n';
    //send start info to server(header GET(get text file) and command Who))
    send(sock, ProtocolRequest.c_str(), ProtocolRequest.length() + 1, 0);

    int count = 0;
    int MAX_COUNT = 13; // max amount of moves

    while(count++ != MAX_COUNT) {
        //read game field from server storage
        read(sock, textFromServer, 1024);


        int cellForMove;
        std::cout << "Your move! Enter cell you want move to!\n";
        std::cout << textFromServer << '\n';
        std::cin >> cellForMove;

        textFromServer[cellForMove] = 'X'; // make a move

        send(sock, textFromServer, strlen(textFromServer), 0);
    }
    return 0;

}