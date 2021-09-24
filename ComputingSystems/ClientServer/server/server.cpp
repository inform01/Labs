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

void getStringsFromTextFile(std::vector<std::string>& storage, std::ifstream&& textStream) {
    std::string currentStringFromFile;
    while(getline(textStream, currentStringFromFile)){
        storage.push_back(currentStringFromFile);
    }
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

    std::vector<std::string> stringsStorage;
    getStringsFromTextFile(stringsStorage, std::move(serverTextFile));

    std::string resString;
    for(const auto& it: stringsStorage) {
        std::cout << it << '\n';
        resString+=it+'\n';
    }
    resString+='\0';
    send(clientSocket, resString.c_str(), resString.length() + 1, 0);


    read(clientSocket, buffer, 4096);

    std::ofstream writeTextRedactor("/home/oleksandr/Labs/ComputingSystems/ClientServer/server/textStorage.txt");
    writeReceivedTextToFile(buffer, std::move(writeTextRedactor));


    std::cout << "Received changed text from client:\n" << buffer << '\n';

    close(serverSocket);
    return 0;

}