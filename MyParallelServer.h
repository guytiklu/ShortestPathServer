#include <unistd.h>
#include <sstream>
#include <iostream>
#include "Interfaces.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <mutex>
#include "MySearchable.cpp"
#include "Solvers.cpp"
#pragma once

class MyParallelServer : public server_side::Server{
private:
    static void openThread(int port, ClientHandler *c);
public:
    void open(int port, ClientHandler *c);

    void closed(int socket);
} ;