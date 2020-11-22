//
// Created by liember on 11/21/20.
//

#include "argexec.hpp"
#include "sighandl.hpp"
#include "shell.hpp"
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

constexpr int max_length = 1024;
constexpr char *success = (char *) "Command executed\n";
constexpr char *fail = (char *) "Command unexpected\n";

static bool run = true;

void session(tcp::socket sock) {
    try {
        shell sh("WebSH");
        for (;;) {
            char data[max_length];
            boost::system::error_code error;
            size_t length = sock.read_some(boost::asio::buffer(data), error);
            data[length] = '\0';

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            if (length > 0) {
                std::stringstream ss(data);
                std::cout << data << std::endl;
                auto input_res = sh.input(ss);
                auto child_out = sh.getExecResult();

                if (!child_out.empty()) {
                    std::cout << child_out << std::endl;
                    boost::asio::write(sock, boost::asio::buffer(child_out.c_str(), child_out.size()));
                } else if (input_res)
                    boost::asio::write(sock, boost::asio::buffer(success, 20));
                else
                    boost::asio::write(sock, boost::asio::buffer(fail, 20));
            }
        }
    }
    catch (std::exception &e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(boost::asio::io_service &io_service, unsigned short port) {
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    while (run) {
        tcp::socket sock(io_service);
        a.accept(sock);
        std::thread(session, std::move(sock)).detach();
    }
}

int main(int argc, char **argv) {
    static auto sig = sighandl::getInstance();
    auto init_rule = argexec::ArgExec(argc, argv);

    if (init_rule == argexec::server) {
        boost::asio::io_service io_service;
        server(io_service, 8888);
    } else {
        shell sh("LiteSh");
        do {
            auto child_out = sh.getExecResult();
            if (!child_out.empty()) {
                std::cout << child_out << std::endl;
            }
            std::cout << "|>>|" << sh.getShellName() << ": ";
        } while (sh.input(std::cin));
    }

    return 0;
}