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
void waitFinishWord() {
    std::string inputWord;
    while(std::cin >> inputWord) {
        if(inputWord == "finish") return;
    }
}
void writeReceivedTextToFile(const char* outputText, std::ofstream outputStream) {
    while(*outputText != '\0') {
        outputStream << *outputText;
        outputText++;
    }
}

void readEditedTextFromFile(std::string& result, std::ifstream inputStream) {
    std::string currentString;
    while(inputStream >> currentString) {
        result+=currentString+'\n';
    }
    result+='\0';
}
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
                 "Request string templates:\n"
                 "K Name int 5 - for keeping this object on server \n"
                 "G Name - for getting this object(with Name name) from server\n"
                 "Enter \"finish\" keyword to finish\n";

    std::string ProtocolRequest;/*= "GET Who";*/
    while(true) {
        //std::cin.ignore();
        getline(std::cin, ProtocolRequest);

        send(sock, ProtocolRequest.c_str(), ProtocolRequest.length() + 1, 0);

        char buffer[1024];
        if(ProtocolRequest[0] == 'G') {
            read(sock, buffer, 1024);
            std::cout << "\nReceived from server: \n" << buffer << '\n';
        }
        if(ProtocolRequest == "finish") break;
    }
    return 0;

}