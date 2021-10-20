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
const char authorName[] = "Liza";
const char projectInfo[] = "Variant: 1\n Text redactor";

std::vector<std::string> cStringToSTDString(const char* protocolRequest, int size) {

   // std::cout << size << "\n";
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
    const std::string fileName = "/home/oyemets/University/Labs/ComputingSystems/LizaClientSever/server/ConnectionsLog.txt";
    fileOut.open(fileName, std::ios::app);
    fileOut << '\n' << line;
}


std::string searchInFile(char* context, const std::string& filePath) {
    std::string searchResult = "There is no such context in this file:(";

    std::string line;

    std::ifstream myStream(filePath);

    while(getline(myStream, line))
    {
        if (line.find(context) != std::string::npos) {
            return (std::string)context + " was found in the file";
        }
    }
    //std::cout << "END OF FUNCTION!\n";
    return "There is no such context in this file:(";
}
int mainServerFunc(int argc, char* argv[],int port) {
    const std::string filePath = "/home/oyemets/University/Labs/ComputingSystems/LizaClientSever/server/textStorage.txt";
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
        std::cerr <<  "Socket binding error:(\n";
        return -1;
    }

    listen(serverSocket, 5);


    //............................................................................................
    //^prepared to connections on our port^
    std::cout << "Server listening connections from clients! Current connection port:" << port << '\n';

    socklen_t clilen = sizeof(client_address);

    bool needStop = false;
    int clientsCount=0;


    int clientSocket = accept(serverSocket, (struct sockaddr *) &serv_addr, &clilen);
    if (clientSocket < 0) {
        std::cout <<  "acceptance error:(\n";
        return -2;
    }

    std::cout << "Connection accepted! Client connected to server!\n";


    while(!needStop) {

        char buffer[1024];


        //read protocol request
        char context[1024];
        read(clientSocket, context, 1024);
        //std::cout << context << std::endl;
        //header for keeping info
        addToLog(context);
        std::string result = searchInFile(context, filePath);

        send(clientSocket, result.c_str(), result.length()+1,0);

        std::cout << result << std::endl;
    }



    close(serverSocket);
    return 0;

}