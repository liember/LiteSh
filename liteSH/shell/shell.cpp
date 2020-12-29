//
// Created by liember on 11/21/20.
//

#include "shell.hpp"

shell::shell(const std::string &shell_name) : cmdline(shell_name, buff_size), procs() {
}

std::string_view shell::getShellName() { return getName(); }

namespace {
    using boost::asio::ip::tcp;

    enum {
        max_length = 2048
    };

    std::string webSend(const std::string &ip, const std::string &port) {
        boost::asio::io_service io_service;
        tcp::socket s(io_service);
        tcp::resolver resolver(io_service);

        boost::asio::connect(s, resolver.resolve({ip, port}));

        std::cout << "|>>| WebSh: ";
        char request[max_length];
        std::cin.getline(request, max_length);
        boost::asio::write(s, boost::asio::buffer(request, strlen(request)));

        char reply[max_length];
        boost::system::error_code error;
        size_t reply_length = s.read_some(boost::asio::buffer(reply), error);
        std::string res(reply, reply_length);
        return std::move(res);
    }
}

bool shell::inputData(std::istream &inp_stream) {
    if (input(inp_stream)) {
        try {
            auto first = get_v()[0];
            if (first == "fctrl") {
                first = fctrl_path.data();
                procs.Spawn(first, get_cv().raw(), false);
                exec_result = procs.getOutBuffer();
            } else if (first == "q") {
                return false;
            } else if (first == "spawn") {
                pop_front();
                auto args = get_cv();
                procs.Spawn(first, args.raw(), false);
                exec_result = procs.getOutBuffer();
            } else if (first == "spawnf") {
                pop_front();
                auto args = get_cv();
                procs.Spawn(first, get_cv().raw(), true);
            } else if (first == "websend") {
                exec_result = webSend(get_v()[1], get_v()[2]);
            } else {
                std::cout << "Incorrect input" << first << std::endl;
                std::cout << "Enter the required action: " << std::endl;
                std::cout << "'spawn' - spawn new process" << std::endl;
                std::cout << "'spawnf' - Spawn a process in fone" << std::endl;
                std::cout << "'fctrl' - spawn lab2" << std::endl;
            }
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    }
    return true;
}

std::string shell::getExecResult() {
    return std::move(exec_result);
}
