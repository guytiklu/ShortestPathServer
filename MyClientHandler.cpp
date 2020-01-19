#include <unistd.h>
#include <sys/socket.h>
#include "MyClientHandler.h"
#include <mutex>
#pragma once

 //solver
 //cm

void MyClientHandler::handleClient(int socket) {
    mutex m;
    string problem = "";
    bool stop=false;
    while (true) {
        char buffer[4096] = {0};
        m.lock();
        int length = read(socket, buffer, 4096);
        m.unlock();
        if(strcmp(buffer,"end\n")==0 || strcmp(buffer,"end")==0){
            break;
        } else {
            problem += buffer;
            if(buffer[length-1]!='\n') {
                problem += "\n";
            }
        }
    }

    string answer;
    if(cm->exists(problem)){
        answer = cm->getSolution(problem);
    }
    else{
        answer = solver->solve(problem);
        cm->saveSolution(problem,answer);
    }

    send(socket, answer.c_str(), answer.length(), 0);
}