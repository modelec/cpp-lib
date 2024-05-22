#include <Modelec/TCPClient.h>
#include <Modelec/Utils.h>
#include <Modelec/CLParser.h>
#include <unistd.h>
#include <iostream>
#include <csignal>
#include <atomic>

std::atomic<bool> shouldStop = false;

void signalHandler( int signum ) {
    shouldStop = true;
}

void messageHandler(TCPClient& client) {
    std::string message;

    while (!shouldStop && !client.shouldStop()) {
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

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);

    CLParser clParser(argc, argv);

    int port = clParser.getOption<int>("port", 8080);

    auto host = clParser.getOption("host", "127.0.0.1");

    bool loggerMode = clParser.hasOption("logger");

    TCPClient client(host, port); // Replace "127.0.0.1" with the IP address of your server and 8080 with the port number

    client.start();

    if (!loggerMode) {
        std::thread messageThread(messageHandler, std::ref(client));
        messageThread.detach();
    }

    while (!client.shouldStop() && !shouldStop) {
        usleep(500'000);
    }

    return 0;
}