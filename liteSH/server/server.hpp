//
// Created by liember on 12/1/20.
//

#ifndef AWS_SERVER_H
#define AWS_SERVER_H

#include <thread>
#include <utility>
#include <boost/asio.hpp>
#include "shell.hpp"

class server {
private:
    static constexpr int max_length = 1024;
    static constexpr char *success = (char *) "Command executed\n";
    static constexpr char *fail = (char *) "Command unexpected\n";

    bool run;

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor a;

    static void session(boost::asio::ip::tcp::socket sock);

public:

    [[nodiscard]] const boost::asio::io_service &getIoService() const;

    explicit server(unsigned short port);

    void start();

    ~server() = default;
};


#endif //AWS_SERVER_H
