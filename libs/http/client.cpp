
#include "client.hpp"

using namespace http;

client::client(std::string ip_addr, int port) {
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        throw Except("Could not create socket");
    }
    _server.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    _server.sin_family = AF_INET;
    _server.sin_port = htons(port);

    if (connect(socket_desc, (struct sockaddr *) &_server, sizeof(_server)) < 0) {
        throw Except("connect error");
    }
}

client::~client(){
    close(socket_desc);
}

void client::sendData(const char *message) {
    if (send(socket_desc, message, strlen(message), 0) < 0) {
        throw Except("Send data failed");
    }
}

char *client::recvData() {
    char *server_reply = new char[2048];
    if (recv(socket_desc, server_reply, 2000, 0) < 0) {
        throw Except("recv failed");
    }
    return server_reply;
}