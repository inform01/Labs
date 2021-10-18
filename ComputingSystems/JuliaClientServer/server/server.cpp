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

struct Object {
    std::string name;
    std::string type;
    int value;
};
std::ostream& operator<<(std::ostream& out, const Object& obj) {
    std::cout << "Object name: " << obj.name << '\n';
    std::cout << "Object type: " << obj.type << '\n';
    std::cout << "Object value: " << obj.value << '\n';
    return out;
}

std::vector<std::string> cStringToSTDString(const char* protocolRequest, int size) {

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

    std::vector<Object> serverStorage;
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

    while(!needStop) {
        char buffer[1024] = {0};

        int clientSocket = accept(serverSocket, (struct sockaddr *) &serv_addr, &clilen);
        if (clientSocket < 0) {
            std::cout <<  "acceptance error:(\n";
            return -2;
        }

        std::cout << "Connection accepted! Client connected to server!\n";

        //read protocol request
        char bufferProtocol[1024] = {0};
        read(clientSocket, bufferProtocol, 4096);

        addToLog(bufferProtocol);

        //header for keeping info
        if(bufferProtocol[0] == 'K') {
            //receivedObjectaName = {K, Name, type, value}
            std::vector<std::string> receivedObject = cStringToSTDString(bufferProtocol, strlen(bufferProtocol));

            std::string objectName = receivedObject[1];
            std::string objectType = receivedObject[2];
            std::string objectValue = receivedObject[3];

            Object object = {objectName, objectType, std::atoi(objectValue.c_str())};
            serverStorage.push_back(std::move(object));
        }

        else if(bufferProtocol[0] == 'G') {
            //receivedObjectName = {G, Name}
            std::vector<std::string> receivedObjectName = cStringToSTDString(bufferProtocol, strlen(bufferProtocol));
            std::string objectName = receivedObjectName[1];

            auto findIterator = std::find_if(serverStorage.begin(), serverStorage.end(),
                                             [objectName](const Object& obj) {return obj.name == objectName;});

            if(findIterator != serverStorage.end()) {
                std::string objectInString = findIterator->name + findIterator->type + std::to_string(findIterator->value);
                send(clientSocket, objectInString.c_str(), objectInString.length() + 1, 0);
            }
        }

//        if(parsedProtocolRequest[0] != "GET") {
//            std::cout << "Header must be specified!(GET for this variant)\n";
//            return 0;
//        }
//        if(parsedProtocolRequest[1] == "Who") {
//            std::cout << "project information:\n";
//            std::cout << authorName << '\n' << projectInfo << '\n';
//        }


        //send source text to client(for editing)
       // send(clientSocket, stringsStorage.c_str(), stringsStorage.length() + 1, 0);

        //read edited text from client
        read(clientSocket, buffer, 4096);

        //write edited text to file

    }



    close(serverSocket);
    return 0;

}