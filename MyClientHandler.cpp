#include <unistd.h>
#include <sys/socket.h>
#include "MyClientHandler.h"
#pragma once

 //solver
 //cm
void MyClientHandler::handleClient(int socket) {
    string problem = "";
    bool stop=false;
    while (true) {
        char buffer[4096] = {0};
        read(socket, buffer, 4096);
        if(strcmp(buffer,"end")==0){
            break;
        } else {
            problem += buffer;
            problem += "\n";
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