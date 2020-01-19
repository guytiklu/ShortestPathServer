#include <cstring>
#include "MyParallelServer.h"
#include <mutex>

#pragma once

int numOfConnections=0;
bool waitingForClient=false;
int socketfd1;
sockaddr_in address1;

void socketPreparations1(int port, int* sktfd, sockaddr_in* adrs){
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;

    }
    *sktfd = socketfd;

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.
    *adrs = address;

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }
    //making socket listen to the port
    if (listen(socketfd, 20) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;

    }
}

void MyParallelServer::openThread(int port, ClientHandler *c){

    cout << "Waiting for client to connect . . ." << endl;
    // accepting a client
    int client_socket = accept(socketfd1, (struct sockaddr *) &address1, (socklen_t *) &address1);
    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
    }
    cout << "connected" << endl;
    numOfConnections++;
    waitingForClient=false;

    c->handleClient(client_socket);
    numOfConnections--;
}

void MyParallelServer::open(int port, ClientHandler* c) {
    int i=0;
    // socket preparations:
    socketPreparations1(port,&socketfd1,&address1);

    while(true) {
        if(!waitingForClient) {
            thread tr(openThread, port, c);
            tr.detach();
            waitingForClient = true;
        }

        int timeOut = 20;
        int timer = timeOut*5;
        while (numOfConnections==0 && timer != 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            timer--;
        }
        if (timer == 0) {
            cout << "timeout, the server is closed" << endl;
            return;
        }
        i++ ;
    }
    closed(socketfd1);

}
void MyParallelServer::closed(int socket) {
    close(socket);
}
