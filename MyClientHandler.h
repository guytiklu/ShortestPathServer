#include "Interfaces.h"
#include "Solvers.cpp"
#include "FileCacheManager.cpp"
#pragma once

class MyClientHandler : public ClientHandler{
public:
    Solver<string,string>* solver;
    CacheManager<string,string> *cm;
    MyClientHandler(){
        solver = new SearcherSolver(new Astar());
        cm = new FileCacheManager<string,string>();
    }
    void handleClient(int socket);
} ;