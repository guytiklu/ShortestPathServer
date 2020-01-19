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

void MySerialServer::open(int port,ClientHandler* c) {
    socketPreparations2(port,&socketfd2,&address2);
    while(true) {
        thread tr(openThread, port, c);
        tr.detach();
        int timeout = 60;
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

/*    Astar srcr{};
    SearcherSolver solver(&srcr);
    string solution = solver.solve("9,1,9,10,8,4,1,8,-1,3,7\n"
                                   "0,8,4,3,10,3,8,2,0,8,10\n"
                                   "6,2,3,4,8,5,4,9,10,10,7\n"
                                   "4,2,10,5,-1,3,10,3,8,-1,10\n"
                                   "2,0,10,10,3,7,7,0,1,0,3\n"
                                   "9,10,7,2,2,10,0,2,3,3,10\n"
                                   "10,5,0,1,6,4,0,2,0,1,7\n"
                                   "8,7,3,6,6,4,1,1,3,3,9\n"
                                   "8,4,-1,7,2,5,10,1,10,3,4\n"
                                   "10,1,9,8,1,5,7,0,2,2,3\n"
                                   "-1,10,2,9,7,3,9,10,9,2,5\n"
                                   "0,0\n10,10\n");
    cout<<solution<<endl;*/
}
void MySerialServer::closed(int socket) {
    close(socket);
 }