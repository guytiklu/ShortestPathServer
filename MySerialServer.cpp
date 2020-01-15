#include <cstring>
#include "MySerialServer.h"
#include <mutex>

#pragma once

bool connected = false;

void MySerialServer::openThread(int port, ClientHandler *c){
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;

    }
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;

    }
    cout << "Waiting for client to connect . . ." << endl;
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
    }
    cout << "connected" << endl;
    connected = true;

    c->handleClient(client_socket);
    close(client_socket);
    close(socketfd);
    connected = false;
}

void MySerialServer::open(int port, ClientHandler* c) {
    while(true) {
        thread tr(openThread, port, c);
        tr.detach();
        int timer = 20*2;
        while (!connected && timer != 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            timer--;
        }
        if (timer == 0) {
            cout << "timeout, the server is closed" << endl;
            return;
        }
        while (connected) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

/*    BestFS srcr{};
    SearcherSolver solver(&srcr);
    string solution = solver.solve("enter problem");
    cout<<solution<<endl;*/
}
void MySerialServer::closed(int socket) {
    close(socket);
}