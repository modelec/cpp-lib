#pragma once

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>

class TCPClient {
private:
    int clientSocket;
    sockaddr_in serverAddress{};
protected:
    bool running;

    bool _stoped;

public:
    explicit TCPClient(const char* serverIP = "127.0.0.1", int port = 8080);

    void sendMessage(const char* message) const;

    void sendMessage(const std::string& message) const;

    void receiveMessages();

    virtual void start();

    virtual void stop();

    virtual ~TCPClient();

    virtual void handleMessage(const std::string& message);

    bool shouldStop() const;
};