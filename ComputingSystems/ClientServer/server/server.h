//
// Created by oleksandr on 23/09/2021.
//

#ifndef CLIENT_SERVER_H
#define CLIENT_SERVER_H
#include<iostream>
#include<vector>

void readStringsFromTextFile(std::string& result, std::ifstream&& inputStream);

void writeReceivedTextToFile(const char* outputText, std::ofstream outputStream);

std::vector<std::string> parseProtocolRequest(const char* protocolRequest, int size);

int mainServerFunc(int argc, char* argv[], int port);

#endif //CLIENT_SERVER_H
