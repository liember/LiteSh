#pragma once

#include <csignal>
#include <iostream>

using namespace std;

class sighandl
{
private:
    static sighandl *instance;
    static void interrupt(int signum);

    sighandl(/* args */);

public:
    static sighandl *getInstance();
};
