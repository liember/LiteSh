#ifndef __PROC_H__
#define __PROC_H__

#include <string>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <sys/wait.h>

#include "exeptions.hpp"
#include "procfs.hpp"
#include "file.hpp"

class subproc {
private:
    static constexpr std::string_view cmd_kill = "kill ";
    std::vector<std::pair<int, std::string>> childs;

    void kill() {
        for (auto &[supp_pid, supp_path] : childs) {
            auto proc_list = procfs::getProcesses();
            auto target = supp_path;
            auto target_pid = supp_pid;

            auto it = std::find_if(proc_list.begin(), proc_list.end(),
                                   [target, target_pid](const std::pair<int, std::string> &element) {
                                       return (element.second == target && element.first == target_pid);
                                   });
            if (it != childs.end()) {
                system((cmd_kill.data() + std::to_string(supp_pid)).c_str());
            }
        }
    }

public:
    subproc() = default;

    ~subproc() {
        kill();
    }

    void Spawn(std::string Path, char **args, bool background) {
        if (!std::filesystem::exists(Path)) {
            auto proxy_path = "/usr/bin/" + Path;
            if (std::filesystem::exists(proxy_path)) {
                Path = proxy_path;
            } else {
                auto err_msg = "File " + Path + " is not exists";
                throw Except(err_msg);
            }
        }

        auto pid = fork();
        if (pid == 0) {
            auto cmd = Path.c_str();
            auto iExecRetVal = execv(cmd, args);
            if (iExecRetVal == -1) {
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS); // if files are opened they are dont closed
        } else if (pid > 0) {
            int status = 0, spawn_res = 0;
            if (!background)
                spawn_res = waitpid(pid, &status, 0);
            else
                spawn_res = waitpid(pid, &status, WNOHANG);

            if (spawn_res != 0 && spawn_res != pid) {
                auto err_msg = "Failed to start process with pid " + std::to_string(pid) +
                               " status " + std::to_string(status) + " result " + std::to_string(spawn_res);
                throw Except(err_msg);
            }
            childs.emplace_back(pid,Path);
        } else {
            throw Except("Failed to create process");
        }
    }
};

#endif // __PROC_H__