#include "server.hpp"

using boost::asio::ip::tcp;

void server::session(tcp::socket sock) {
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

server::server(unsigned short port) : a(io_service, tcp::endpoint(tcp::v4(), port)) {
    run = true;
}

void server::start(){
    while (run) {
        tcp::socket sock(io_service);
        a.accept(sock);
        std::thread(session, std::move(sock)
        ).detach();
    }
}

const boost::asio::io_service &server::getIoService() const {
    return io_service;
}
