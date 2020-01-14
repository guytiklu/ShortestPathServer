#include <cstring>
#include "MySerialServer.h"
#include <mutex>

#pragma once

bool connected = false;
mutex mutexlock;
/*void inThread(int client_socket, std::stringstream* in) {
    while (connected) { // make while in a thread
        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);
        if (strcmp(buffer, "\0") != 0) {
            mutexlock.lock();
            cout << "got input: " << buffer << endl;//########################################
            *in << buffer;
            mutexlock.unlock();
        }
    }
}
void outThread(int client_socket, std::stringstream* out) {
    string data;
    string s;
    while (connected) {
        if (out->rdbuf()->in_avail() > 0) {
            mutexlock.lock();
            data = "";
            s = "";
            while (out->rdbuf()->in_avail() > 0) {
                *out >> s;
                data += s;
                if (out->rdbuf()->in_avail() > 0) {
                    data += " ";
                }
            }
            out->clear();
            cout << "sent to server: " << data << endl;//########################################
            send(client_socket, data.c_str(), data.length(), 0);
            mutexlock.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}*/

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

    /*stringstream in;
    stringstream out;

    // input thread
    thread trIn(inThread, client_socket, &in);
    trIn.detach();

    // output thread
    thread trOut(outThread, client_socket, &out);
    trOut.detach();*/

    c->handleClient(client_socket);
    close(client_socket);
    close(socketfd);
    connected = false;
}

void MySerialServer::open(int port, ClientHandler* c) {
    /*while(true) {
        thread tr(openThread, port, c);
        tr.detach();
        int timer = 10*2;
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
    }*/

    MySearchable srcble{};
    BestFS srcr{};
    SearcherSolver solver(&srcble,&srcr);
    Solution<string> solution = solver.solve("");
}
void MySerialServer::closed(int socket) {
    close(socket);
}