#pragma once

#include <thread>
#include <string>
#include <unistd.h>
#include <vector>
#include <filesystem>

#include "exeptions.hpp"

class subprocs
{
private:
    std::vector<pid_t> childs;
    bool check(pid_t);

public:
    void Spawn(const std::string &path);
    void Kill();

    ~subprocs();
};
