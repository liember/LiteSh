#include "proc.hpp"

void subprocs::Spawn(const std::string &path)
{
    int iExecRetVal, pid;
    pid = fork();

    if (pid == -1)
    {
    }
    else if (pid > 0)
    {
    }
    else
    {
        iExecRetVal = execl("./flute-static", "./flute-static", "-send", "-a192.168.190.1/6666", "JFlute.1.2.tar.gz", NULL);
        if (iExecRetVal == -1)
        {
            throw Except("Faild to start process");
        }
        _exit(0);
    }
}

void subprocs::Kill()
{
    for (auto &&i : childs)
    {
        std::string cmd = "kill";
        cmd = cmd + std::to_string(i);
        system(cmd.c_str());
    }
}

bool subprocs::check(pid_t pid)
{
    return true;
}

subprocs::~subprocs()
{
}