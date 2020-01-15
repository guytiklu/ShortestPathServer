#include "myTestClientHandler.h"
#pragma once

void myTestClientHandler::handleClient(int socket) {
     // get input if solution exits return it, else, generate solution save it and return
    // wait a few seconds for next command
    // if no command is given or the input "end" detected finish





    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    int count = 0;
    int max_time = 3;
    while (count < max_time * 10) {/// as long as we dont have input
        std::this_thread::sleep_for(std::chrono::milliseconds(100));/// make the program wait 0.1 sec
        count++;
    }
    if (count >= max_time * 10) { /// we have waited too much for information, we finish
        cout << "we have been waiting too much for you, my lord" << endl;
        return;
    }
}