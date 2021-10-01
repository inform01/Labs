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

    std::cout << "Connection accepted! Client connected to server!\n";

    std::ifstream serverTextFile("/home/oleksandr/Labs/ComputingSystems/ClientServer/server/textStorage.txt");
    std::cout << "\nRead from text file:\n";
    std::string stringsStorage;

    //get all strings from textStorage.txt file and pass them to vector
    readStringsFromTextFile(stringsStorage, std::move(serverTextFile));

    //send source text to client(for editing)
    send(clientSocket, stringsStorage.c_str(), stringsStorage.length() + 1, 0);

    //read edited text from client
    read(clientSocket, buffer, 4096);

    //write edited text to file
    std::ofstream writeTextRedactor("/home/oleksandr/Labs/ComputingSystems/ClientServer/server/textStorage.txt");
    writeReceivedTextToFile(buffer, std::move(writeTextRedactor));


    std::cout << "Received changed text from client:\n" << buffer << '\n';

    close(serverSocket);
    return 0;

}