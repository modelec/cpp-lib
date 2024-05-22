#include <Modelec/CLParser.h>
#include <iostream>

struct B {
    std::string a;
};

int main(int argc, char* argv[]) {

    CLParser parser(argc, argv);

    int port = parser.getOption("port", 12);

    std::cout << "Port : " << port << std::endl;

    auto test = parser.getOption<long>("long");

    if (test.has_value()) {
        std::cout << test.value() << std::endl;
    }
    else {
        std::cout << "missing long argument" << std::endl;
    }

    return 0;
}