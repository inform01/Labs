//
// Created by oleksandr on 23/09/2021.
//

#include "server.h"
#include <regex>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
int mainServerFunc(int argc, char* argv[],int port) {
    std::string prefix = "SERVER>";  //just for convenience
    //........................................................................
    int serverSocket;
    struct sockaddr_in serv_addr;
    struct sockaddr client_address;

    serverSocket = socket(AF_INET, SOCK_STREAM,0);

    if(serverSocket < 0) {
        std::cerr << "Socket opening error:(\n";
        return -1;
    }

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;

    if(bind(serverSocket, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << prefix + "Socket binding error:(\n";
        return -1;
    }

    listen(serverSocket, 5);


    //............................................................................................
    //^prepared to connections on our port^
    std::cout << prefix + "Server listening connections from clients! Current connection port:" << port << '\n';

    socklen_t clilen = sizeof(client_address);

    bool needStop = false;
    int clientsCount=0;

    //   while(!needStop) {
    char buffer[1024] = {0};

    int clientSocket = accept(serverSocket, (struct sockaddr*)&serv_addr, &clilen);
    if(clientSocket < 0) {
        std::cout << prefix + "acceptance error:(\n";
        return -2;
    }
    clientsCount++;

    std::cout << prefix + "Connection accepted! Client connected to server!\n";
    int valread = read(clientSocket, buffer, 4096);

    std::cout << prefix + "Received from client: " << buffer << '\n';

    std::string answerFromServer = "5!\n";

    send(clientSocket, answerFromServer.c_str(), answerFromServer.length() + 1, 0);

    std::cout << prefix + "Message to client sent\n\n";
    //   }
    close(serverSocket);
    return 0;

}