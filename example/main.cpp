#include <Modelec/CLParser.h>

#include <iostream>

int main(int argc, char* argv[]) {

    CLParser parser(argc, argv);

    if (parser.hasOption("help")) {
        std::cout << "Usage: " << parser.getPositionalArgument(0) << " [options]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  --help: Display this help message" << std::endl;
        std::cout << "  --port <port>: Set the port to listen to" << std::endl;
        return 0;
    }

    std::optional<std::string> port = parser.getOption("port");

    if (port.has_value()) {
        std::cout << port.value() << std::endl;
    } else {
        std::cout << "No port specified" << std::endl;
    }

    return 0;
}