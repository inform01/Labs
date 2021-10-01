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

    //read 5+ strings from server storage
    read(sock, textFromServer, 1024);

    std::cout << "You received text from server. Check textRedactor.txt file to change it, if you want\n"
                 "Type \"finish\" if you finish editing a file\nAll changes will send to server storage\n";

    //write all text to textRedactor.txt file(for convenient editing)
    std::ofstream writeTextRedactor("/home/oleksandr/Labs/ComputingSystems/ClientServer/client/textRedactor.txt");
    writeReceivedTextToFile(textFromServer, std::move(writeTextRedactor));

    //waiting when client finish file editing
    waitFinishWord();

    //read edited string to editedTextString variable
    std::ifstream readTextRedactor("/home/oleksandr/Labs/ComputingSystems/ClientServer/client/textRedactor.txt");
    std::string editedTextString;
    readEditedTextFromFile(editedTextString, std::move(readTextRedactor));

    //send edited buffer back to server storage
    send(sock , editedTextString.c_str(),  editedTextString.length() + 1, 0 );

    return 0;

}