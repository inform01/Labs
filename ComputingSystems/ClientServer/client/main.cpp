#include"client.h"
#include<iostream>
int main(int argc, char* argv[]) {
    int port = 0;
    std::cout << "Please,enter the port number: ";
    std::cin >> port;
    return mainClientFunc(argc,argv, port);

}
