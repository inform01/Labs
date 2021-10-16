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

//Info for "Who" command
const char authorName[] = "Oleksandr Yemets";
const char projectInfo[] = "Variant: 1\n Text redactor";

void readStringsFromTextFile(std::string& result, std::ifstream&& inputStream) {
    std::string currentString;
    while(inputStream >> currentString) {
        result+=currentString+'\n';
    }
    result+='\0';
}

void writeReceivedTextToFile(const char* outputText, std::ofstream outputStream) {
    while(*outputText != '\0') {
        outputStream << *outputText;
        outputText++;
    }
}
std::vector<std::string> parseProtocolRequest(const char* protocolRequest, int size) {

    std::cout << size << "\n";
    std::vector<std::string> result;
    std::string currentWord;
    for(int i = 0; i < size; ++i) {
        if(*(protocolRequest + i)  == ' ') {
            if(currentWord != "|") result.push_back(currentWord);
            currentWord = "";
        }
        else if(currentWord != "|") currentWord+=*(protocolRequest + i);
    }
    result.push_back(currentWord);
    return result;
}
void addToLog(char* line) {
    std::ofstream fileOut;
    const std::string fileName = "/home/oyemets/University/Labs/ComputingSystems/ClientServer/server/ConnectionsLog.txt";
    fileOut.open(fileName, std::ios::app);
    fileOut << '\n' << line;
}
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
    std::cout << "Server listening connections from clients! Current connection port:" << port << '\n';

    socklen_t clilen = sizeof(client_address);

    int clientsCount=0;
    int count = 0;
    const int MAX_COUNT = 12; // max amount of server moves
    char gameField[] = ".....\n.....\n.....\n.....\n.....";

    int clientSocket = accept(serverSocket, (struct sockaddr *) &serv_addr, &clilen);
    if (clientSocket < 0) {
        std::cout << prefix + "acceptance error:(\n";
        return -2;
    }

    std::cout << "Connection accepted! Client connected to server!\n";

    //read protocol request
    char bufferProtocol[1024] = {0};
    read(clientSocket, bufferProtocol, 4096);

    addToLog(bufferProtocol);

    if(bufferProtocol[0] != 'P') {
        std::cout << "Incorrect header!\n";
        return 0;
    }


    //start game field to client
    send(clientSocket, gameField, strlen(gameField), 0);

    while(count++ != MAX_COUNT) {
        //read edited text from client
        read(clientSocket, gameField, 4096);


        int cellForMove;
        std::cout << "Your move! Enter cell you want move to!\n";
        std::cout << gameField << '\n';
        std::cin >> cellForMove;

        gameField[cellForMove] = 'O';

        send(clientSocket, gameField, strlen(gameField), 0);
    }

    close(serverSocket);
    return 0;

}