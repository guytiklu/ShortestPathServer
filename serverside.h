#include <iostream>
#include <string>
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "MyParallelServer.h"

#pragma once

namespace boot {

    class Main {
    public:
        static int main(int argc,char* argv[]) {
            /*//serial server
            MySerialServer mss{};
            MyClientHandler mtch{};
            mss.open(stoi(argv[1]), &mtch);*/

            //parallel server
            MyParallelServer mps{};
            MyClientHandler mtch{};
            mps.open(stoi(argv[1]), &mtch);

            return 0;
        }
    } ;
}