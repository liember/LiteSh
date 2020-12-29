//
// Created by liember on 11/21/20.
//

#include <iostream>
#include "argexec.hpp"
#include "sighandl.hpp"
#include "shell.hpp"
#include "server.hpp"
#include "thread"

int main(int argc, char **argv) {
    static auto sig = sighandl::getInstance();
    auto init_rule = argexec::ArgExec(argc, argv);
    std::thread *t = nullptr;

    if (init_rule == argexec::server) {
        t = new std::thread([]() {
            server s(8888);
            s.start();
        });
        std::cout << "server has been started\n";
    } else {
        shell sh("LiteSh");
        do {
            auto child_out = sh.getExecResult();
            if (!child_out.empty()) {
                std::cout << child_out << std::endl;
            }
            std::cout << "|>>|" << sh.getShellName() << ": ";
        } while (sh.inputData(std::cin));
    }
    if (t)
        t->join();
    return 0;
}