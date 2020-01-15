#include "Interfaces.h"
#include "Solvers.cpp"
#include "FileCacheManager.cpp"
#pragma once

class myTestClientHandler : public ClientHandler{
public:
    Solver<string,string>* solver;
    CacheManager<string,string> *cm;
    myTestClientHandler(){
        solver = new StringReverser();
        cm = new FileCacheManager<string,string>();
    }
    void handleClient(int socket);
};