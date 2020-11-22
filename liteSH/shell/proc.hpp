#ifndef __PROC_H__
#define __PROC_H__

#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sys/wait.h>

#include "cstdio"
#include "unistd.h"

#include "exceptions.hpp"
#include "procfs.hpp"
#include "file.hpp"
#include "cstdlib"

#define NUM_PIPES          2

#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1
/* always in a pipe[], pipe[0] is for read and
   pipe[1] is for write */
#define READ_FD  0
#define WRITE_FD 1

#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )

#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )

class subproc {
private:
    int pipes[NUM_PIPES][2];
    static constexpr std::string_view cmd_kill = "kill ";
    std::vector<std::pair<int, std::string>> childs;

    std::string out_buffer;
    char buffer[2000];

private:
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

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

    std::string getOutBuffer()  {
        return std::move(out_buffer);
    }

    void Spawn(std::string Path, char **args, bool background) {
        if (!std::filesystem::exists(Path)) {
            auto proxy_paths = split(getenv("PATH"), ':');
            for (auto &i : proxy_paths) {
                auto target_path = i + "/" + Path;
                if (std::filesystem::exists(target_path)) {
                    Path = target_path;
                }
            }
            if (!std::filesystem::exists(Path)) {
                auto err_msg = "File " + Path + " is not exists";
                throw Except(err_msg);
            }
        }

        // pipes for parent to write and read
        pipe(pipes[PARENT_READ_PIPE]);
        pipe(pipes[PARENT_WRITE_PIPE]);

        auto pid = fork();
        if (pid == 0) {
            auto cmd = Path.c_str();

            dup2(CHILD_READ_FD, STDIN_FILENO);
            dup2(CHILD_WRITE_FD, STDOUT_FILENO);
            close(CHILD_READ_FD);
            close(CHILD_WRITE_FD);
            close(PARENT_READ_FD);
            close(PARENT_WRITE_FD);

            auto iExecRetVal = execv(cmd, args);
            if (iExecRetVal == -1) {
                _exit(EXIT_FAILURE);
            }
            _exit(EXIT_SUCCESS); // if files are opened they are dont closed
        } else if (pid > 0) {
            int status = 0, spawn_res;
            if (!background) {
                close(CHILD_READ_FD);
                close(CHILD_WRITE_FD);
                auto count = read(PARENT_READ_FD, buffer, sizeof(buffer) - 1);
                if (count >= 0) {
                    buffer[count] = 0;
                    out_buffer = buffer;
                } else {
                    printf("IO Error\n");
                }
                spawn_res = waitpid(pid, &status, 0);
            }
            else {
                spawn_res = waitpid(pid, &status, WNOHANG);
                childs.emplace_back(pid, Path);
            }
            if (spawn_res != 0 && spawn_res != pid) {
                auto err_msg = "Failed to start process with pid " + std::to_string(pid) +
                               " status " + std::to_string(status) + " result " + std::to_string(spawn_res);
                throw Except(err_msg);
            }
        } else {
            throw Except("Failed to create process");
        }
    }
};

#endif // __PROC_H__