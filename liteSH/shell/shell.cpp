//
// Created by liember on 11/21/20.
//

#include "shell.hpp"

shell::shell(std::string shell_name) : input_line(shell_name, buff_size), procs() {
}

void shell::input(std::istream &inp_stream) {
    while (true) {
        std::cout << input_line.getName() << ": ";
        if (input_line.input(inp_stream)) {
            try {
                if (input_line[0] == "fctrl") {
                    input_line[0] = fctrl_path.data();
                    auto cmd = input_line[0];
                    auto args = input_line.get_cv();
                    procs.Spawn(input_line[0], args.raw(), false);
                } else if (input_line[0] == "q") {
                    break;
                } else if (input_line[0] == "spawn") {
                    input_line.pop_front();
                    auto cmd = input_line[0];
                    auto args = input_line.get_cv();
                    procs.Spawn(cmd, args.raw(), false);
                } else if (input_line[0] == "spawnf") {
                    input_line.pop_front();
                    auto cmd = input_line[0];
                    auto args = input_line.get_cv();
                    procs.Spawn(input_line[0], input_line.get_cv().raw(), true);
                } else if (input_line[0] == "websend") {
                    auto c = new http::client("127.0.0.1", 8888);
                    c->sendData(input_line[1].c_str());
                    std::cout << c->recvData();
                    delete c;
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
    }
}