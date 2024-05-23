#include <Modelec/CLParser.h>
#include <iostream>

struct B {
    std::string a;
};

int main(int argc, char* argv[]) {

    CLParser parser(argc, argv);

    int port = parser.getOption("port", 12);

    auto test = parser.getOption("host", "127.0.0.1");

    return 0;
}