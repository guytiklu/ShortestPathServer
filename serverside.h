#include <iostream>
#include <string>
#include "MySerialServer.h"
#include "MyClientHandler.h"

#pragma once

namespace boot {

    class Main {
    public:
        static int main(int argc,char* argv[]) {
            MySerialServer mss{};
            MyClientHandler mtch{};
            mss.open(stoi(argv[1]), &mtch);

            return 0;
        }
    } ;
}