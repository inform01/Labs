//
// Created by oleksandr on 23/09/2021.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H
#include<iostream>

void waitFinishWord();

void writeReceivedTextToFile(const char* outputText, std::ofstream outputStream);

void readEditedTextFromFile(std::string& result, std::ifstream inputStream);

int mainClientFunc(int argc, char* argv[], int port);


#endif //CLIENT_CLIENT_H
