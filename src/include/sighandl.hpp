#pragma once

#include <csignal>
#include <iostream>

using namespace std;

class sighandl
{
private:
    static sighandl *instance;

    static void interrupt(int signum)
    {
        cout << "The great interrupt signal (" << signum << ") has received.\n";
        exit(signum);
    }

    sighandl(/* args */)
    {
        signal(SIGINT, interrupt);
    }

public:
    static sighandl *getInstance()
    {
        if (!instance)
            instance = new sighandl;
        return instance;
    }
};

sighandl *sighandl::instance = 0;
