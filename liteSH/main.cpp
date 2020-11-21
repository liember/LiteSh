//
// Created by liember on 11/21/20.
//

#include "shell.hpp"
#include "argexec.hpp"
#include "sighandl.hpp"

int main(int argc, char **argv) {
    static auto sig = sighandl::getInstance();
    argexec::ArgExec(argc,argv);
    shell sh("LiteSh");
    sh.input(std::cin);
    return 0;
}