#include <cstring>
#include "MySerialServer.h"
#include <mutex>

#pragma once

bool connected = false;
int socketfd2;
sockaddr_in address2;

void socketPreparations2(int port, int* sktfd, sockaddr_in* adrs){
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

void MySerialServer::openThread(int port, ClientHandler *c){

    cout << "Waiting for client to connect . . ." << endl;
    // accepting a client
    int client_socket = accept(socketfd2, (struct sockaddr *) &address2, (socklen_t *) &address2);
    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
    }
    cout << "connected" << endl;
    connected = true;

    c->handleClient(client_socket);
    connected = false;
}

void MySerialServer::open(int port, ClientHandler* c) {
    socketPreparations2(port,&socketfd2,&address2);
    while(true) {
        thread tr(openThread, port, c);
        tr.detach();
        int timeout = 20;
        int timer = timeout*5;
        while (!connected && timer != 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            timer--;
        }
        if (timer == 0) {
            cout << "timeout, the server is closed" << endl;
            return;
        }
        while (connected) {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    closed(socketfd2);

/*   BestFS srcr{};
    SearcherSolver solver(&srcr);
    string solution = solver.solve("enter problem");
    cout<<solution<<endl;*/
}
void MySerialServer::closed(int socket) {
    close(socket);
}