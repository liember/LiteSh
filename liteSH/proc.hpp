#pragma once

#include <string>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <sys/wait.h>

#include "exeptions.hpp"
#include "procfs.hpp"
#include "file.hpp"

auto CheckExists(std::string path) { return std::filesystem::exists(path); }

class subproc
{
private:
    static constexpr std::string_view cmd_kill = "kill";
    std::vector<std::pair<int, std::string>> fone_childs;

    void KillChilds()
    {
        for (auto &[supp_pid, supp_path] : fone_childs)
        {
            auto proc_list = procfs::GetProcs();
            auto target = supp_path;
            auto target_pid = supp_pid;

            auto it = std::find_if(proc_list.begin(), proc_list.end(),
                                   [target, target_pid](const std::pair<int, std::string> &element) {
                                       return (element.second == target && element.first == target_pid);
                                   });
            if (it != fone_childs.end())
            {
                system((cmd_kill.data() + std::to_string(supp_pid)).c_str());
            }
        }
    }

public:
    subproc() {}
    void Spawn(std::string Path, bool In_fone)
    {
        if (!CheckExists(Path))
        {
            auto prox_path = "/usr/bin/" + Path;
            if (CheckExists(prox_path))
            {
                Path = prox_path;
            }
            else
            {
                auto err_msg = "File " + Path + " is not exists";
                throw Except(err_msg);
            }
        }

        auto pid = fork();
        if (pid == 0)
        {
            auto execl_arg = Path.c_str();
            auto iExecRetVal = execl(execl_arg, execl_arg, (char *)NULL);
            if (iExecRetVal == -1)
            {
                _exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS); // if files are openned they are dont closed
        }
        else if (pid > 0)
        {
            int status = 0, spawn_res = 0;
            if (!In_fone)
                spawn_res = waitpid(pid, &status, 0);
            else
                spawn_res = waitpid(pid, &status, WNOHANG);

            if (spawn_res != 0 && spawn_res != pid)
            {
                auto err_msg = "Faild to start process with pid " + std::to_string(pid) + " status " + std::to_string(status) + " result " + std::to_string(spawn_res);
                throw Except(err_msg);
            }
        }
        else
        {
            throw Except("Faild to create process");
        }
    }
};
