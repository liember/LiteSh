//
// Created by liember on 11/21/20.
//

#include "shell.hpp"

shell::shell(const std::string &shell_name) : input_line(shell_name, buff_size), procs() {
}

std::string_view shell::getShellName() { return input_line.getName(); }

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

bool shell::input(std::istream &inp_stream) {
    if (input_line.input(inp_stream)) {
        try {
            if (input_line[0] == "fctrl") {
                input_line[0] = fctrl_path.data();
                auto cmd = input_line[0];
                auto args = input_line.get_cv();
                procs.Spawn(input_line[0], args.raw(), false);
                exec_result = procs.getOutBuffer();
            } else if (input_line[0] == "q") {
                return false;
            } else if (input_line[0] == "spawn") {
                input_line.pop_front();
                auto cmd = input_line[0];
                auto args = input_line.get_cv();
                procs.Spawn(cmd, args.raw(), false);
                exec_result = procs.getOutBuffer();
            } else if (input_line[0] == "spawnf") {
                input_line.pop_front();
                auto cmd = input_line[0];
                auto args = input_line.get_cv();
                procs.Spawn(input_line[0], input_line.get_cv().raw(), true);
            } else if (input_line[0] == "websend") {
                exec_result = webSend(input_line[1], input_line[2]);
            } else {
                std::cout << "Incorrect input" << input_line[0] << std::endl;
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
