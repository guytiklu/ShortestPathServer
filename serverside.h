#include <iostream>
#include <string>
#include "MySerialServer.h"
#include "myTestClientHandler.h"

#pragma once

namespace boot {

    class Main {
    public:
        static int main(int argc,char* argv[]) {
            MySerialServer mss{};
            myTestClientHandler mtch{};
            mss.open(stoi(argv[1]), &mtch);

            return 0;
        }
    };
}