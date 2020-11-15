#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string>

#include "exeptions.hpp"

namespace http {
    class client {
    private:
        int socket_desc;
        struct sockaddr_in _server;
    public:
        client(std::string ip_addr);
        ~client();

        void sendData(char *message);

        char *recvData();
    };
}