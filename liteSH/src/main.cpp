#include <iostream>

#include "src/argexec.hpp"
#include "cmdline.hpp"
#include "sighandl.hpp"
#include "http/client.hpp"

int main(int argc, char **argv) {
    argexec::ArgExec(argc, argv);

    auto sig = sighandl::getInstance();
    auto procs = subproc();
    auto shell = cmdline("liteSH", 2048);

    constexpr std::string_view fctrl_path = "./fctrl/fctrl";

    while (true) {
        if (shell.input(std::cin)) {
            try {

                if (shell[0] == "fctrl") {
                    shell[0] = fctrl_path.data();
                    auto cmd = shell[0];
                    auto args = shell.get_cv();
                    procs.Spawn(shell[0], args, false);
                } else if (shell[0] == "q") {
                    break;
                } else if (shell[0] == "spawn") {
                    shell.pop_front();
                    auto cmd = shell[0];
                    auto args = shell.get_cv();
                    procs.Spawn(cmd, args, false);
                } else if (shell[0] == "spawnf") {
                    shell.pop_front();
                    auto cmd = shell[0];
                    auto args = shell.get_cv();
                    procs.Spawn(shell[0], shell.get_cv(), true);
                } else if (shell[0] == "websend") {
                    auto c = new http::client("127.0.0.1", 8888);
                    c->sendData(shell[1].c_str());
                    std::cout << c->recvData();
                    delete c;
                } else {
                    cout << "Incorrect input" << shell[0] << endl;
                    cout << "Enter the required action: " << endl;
                    cout << "'spawn' - spawn new process" << endl;
                    cout << "'spawnf' - Spawn a process in fone" << endl;
                    cout << "'fctrl' - spawn lab2" << endl;
                }
            }
            catch (const std::exception &e) {
                std::cerr << e.what() << '\n';
            }
        }
    }
    return 0;
}
