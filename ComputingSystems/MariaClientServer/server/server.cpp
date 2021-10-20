//
// Created by oleksandr on 23/09/2021.
//

#include "server.h"
#include <regex>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <algorithm>

//Info for "Who" command
const char authorName[] = "Maria Kardash";
const char projectInfo[] = "Variant: 1\n Guess the passport";


std::string generateRandomPassword() {
    srand(std::time(nullptr));
    std::string resultPassword;
    size_t passwordSize = rand()%10 + 1;  //size: 1 to 10
    for(int i = 0; i < passwordSize; ++i) {
        resultPassword+=static_cast<char>(rand()%75 + 48);  //48 to 122 ASCII code is symbols from '0' to 'z'
    }
    return resultPassword;
}
void addToLog(char* line) {
    std::ofstream fileOut;
    const std::string fileName = "/home/oleksandr/Labs/ComputingSystems/ClientServer/server/ConnectionsLog.txt";
    fileOut.open(fileName, std::ios::app);
    fileOut << '\n' << line;
}
int startServer(int argc, char* argv[],int port) {

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
    std::cout << "Server listening connections from clients! Current connection port:" << port << '\n';

    socklen_t clilen = sizeof(client_address);

    bool needStop = false;
    int clientsCount=0;

    while(!needStop) {

        int clientSocket = accept(serverSocket, (struct sockaddr *) &serv_addr, &clilen);
        if (clientSocket < 0) {
            std::cout << prefix + "acceptance error:(\n";
            return -2;
        }
        clientsCount++;

        std::cout << "Connection accepted! Client connected to server!\n";
        std::string resultPassword;
        //  size_t passwordSize = rand()%10 + 1;  //size: 1 to 10
        resultPassword = "abiba";
        const std::string generatedPassword = "aba"; /*generateRandomPassword();*/

        std::string passwordSizeString = std::to_string(generatedPassword.size());
        send(clientSocket, passwordSizeString.c_str(), passwordSizeString.length() + 1, 0);
     //   std::string passwordFromCLient;


     //always read message from client till password isn't guessed
        while(true) {
            // read password
            char buffer[1024] = {0};
            read(clientSocket, buffer, 4096);
            std::cout << buffer << '\n';
            //add currenrt password to log file
            addToLog(buffer);

            std::string passwordFromCLient(buffer);

            std::string answerToClient;
            if (passwordFromCLient == generatedPassword) {
                answerToClient = "You right! Correct password is " + passwordFromCLient;
                send(clientSocket, answerToClient.c_str(), answerToClient.length() + 1, 0);
                break;
            }
            else {
                answerToClient = "Try again:(";
                send(clientSocket, answerToClient.c_str(), answerToClient.length() + 1, 0);
            }
        }
        close(serverSocket);
        return 0;
    }

}