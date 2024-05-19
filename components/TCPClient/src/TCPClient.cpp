#include <Modelec/TCPClient.h>

#include <Modelec/Utils.h>

TCPClient::TCPClient(const char* serverIP, int port) : running(false), _stoped(false) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIP, &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Connection failed" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void TCPClient::sendMessage(const char* message) const {
    std::string temp = message;
    if (!Modelec::endsWith(temp, "\n")) {
        temp += "\n";
    }

    send(clientSocket, temp.c_str(), temp.size(), 0);
}

void TCPClient::sendMessage(const std::string& message) const {
    std::string temp = message;
    if (!Modelec::endsWith(temp, "\n")) {
		temp += "\n";
	}

    send(clientSocket, temp.c_str(), temp.size(), 0);
}

void TCPClient::receiveMessages() {
    char buffer[1024] = {0};
    while (running) {
        ssize_t valread = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (valread > 0) {
            std::vector<std::string> messages = Modelec::split(buffer, "\n");
            for (const std::string& message : messages) {
                handleMessage(message);
            }
            memset(buffer, 0, sizeof(buffer)); // Clear buffer
        } else if (valread == 0) {
            std::cerr << "Connection closed by server" << std::endl;
            break;
        } else {
            std::cerr << "Error in receiving message" << std::endl;
            break;
        }
    }
    running = false;
}

void TCPClient::handleMessage(const std::string& message) {
    std::cout << message << std::endl;
}

TCPClient::~TCPClient() {
    stop();
}

void TCPClient::start() {
	running = true;
    std::thread receiveThread(&TCPClient::receiveMessages, this);
    receiveThread.detach();
}

void TCPClient::stop() {
    if (!_stoped) {
        running = false;
        close(clientSocket);
        _stoped = true;
    }
}

bool TCPClient::shouldStop() const {
    return !running;
}