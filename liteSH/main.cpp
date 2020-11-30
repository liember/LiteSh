//
// Created by liember on 11/21/20.
//

#include <iostream>
#include "argexec.hpp"
#include "sighandl.hpp"
#include "shell.hpp"
#include "server.hpp"

int main(int argc, char **argv) {
    static auto sig = sighandl::getInstance();
    auto init_rule = argexec::ArgExec(argc, argv);

    if (init_rule == argexec::server) {
        server s(8888);
        s.start();
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