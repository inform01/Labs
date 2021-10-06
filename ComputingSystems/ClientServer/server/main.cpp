#include"server.h"
#include<iostream>

int main(int argc, char* argv[]) {

    int port;
    std::cout << "Enter port number for server:\n";
    std::cin >> port;
    return mainServerFunc(argc,argv, port);

}