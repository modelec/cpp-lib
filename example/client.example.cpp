#include <Modelec/TCPClient.h>
#include <Modelec/Utils.h>
#include <Modelec/CLParser.h>
#include <unistd.h>
#include <iostream>
#include <csignal>
#include <atomic>

std::atomic<bool> running(true);

void signalHandler(int signal) {
    running = false;
}

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);

    CLParser parser(argc, argv);

    int port = parser.getOption<int>("port", 8080);

    bool loggerMode = parser.hasOption("logger");

    TCPClient client("127.0.0.1", port); // Replace "127.0.0.1" with the IP address of your server and 8080 with the port number

    client.start();

    while (!client.shouldStop() && !running) {
        if (loggerMode) {
            usleep(500'000);
        } else {
            std::string message;
            std::getline(std::cin, message);

            if (message == "quit") {
                client.stop();
                break;
            }
            if (message == "ready") {
                client.sendMessage("lidar;strat;ready;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("aruco;strat;ready;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("arduino;strat;ready;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("tirette;strat;ready;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("servo_moteur;strat;ready;1");
            } else if (message == "pong") {
                client.sendMessage("lidar;ihm;pong;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("aruco;ihm;pong;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("arduino;ihm;pong;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("tirette;ihm;pong;1");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                client.sendMessage("servo_moteur;ihm;pong;1");
            } else {
                client.sendMessage(message);
            }
        }
    }

    return 0;
}