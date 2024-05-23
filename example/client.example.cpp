#include <Modelec/TCPClient.h>
#include <Modelec/Utils.h>
#include <Modelec/CLParser.h>
#include <unistd.h>
#include <iostream>
#include <csignal>
#include <atomic>
#include <memory>
#include <thread>
#include <fcntl.h>
#include <mutex>
#include <sys/select.h>
#include <poll.h>

std::atomic<bool> shouldStop = false;

void signalHandler(int signum) {
    shouldStop = true;
}

void userInputHandler(const std::shared_ptr<TCPClient>& client) {
    std::string input;

    while (!client->shouldStop() && !shouldStop) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000000; // 100 milliseconds

        int result = select(STDIN_FILENO + 1, &read_fds, nullptr, nullptr, &timeout);

        if (result > 0 && FD_ISSET(STDIN_FILENO, &read_fds)) {
            std::string line;
            std::getline(std::cin, line);
            if (!line.empty()) {
                client->sendMessage(line);
            }
        } else if (result < 0) {
            // Some other error occurred
            std::cerr << "Error reading input" << std::endl;
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    signal(SIGINT, signalHandler);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    CLParser clParser(argc, argv);

    int port = clParser.getOption<int>("port", 8080);
    auto host = clParser.getOption("host", "127.0.0.1");
    bool loggerMode = clParser.hasOption("logger");

    std::shared_ptr<TCPClient> client = std::make_shared<TCPClient>(host, port);

    client->start();

    // Start the user input handling thread
    std::thread inputThread;

    if (!loggerMode) {
        inputThread = std::thread(userInputHandler, client);
        inputThread.detach();
    }

    while (!client->shouldStop() && !shouldStop) {
        usleep(500'000);
    }

    if (inputThread.joinable()) {
        inputThread.join();
    }

    return 0;
}
