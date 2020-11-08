#ifndef __SIGHANDL_H__
#define __SIGHANDL_H__

#include <csignal>
#include <iostream>

using namespace std;

class sighandl
{
private:
    static sighandl *instance;
    static void interrupt(int signum)
    {
        cout << "\nThe great interrupt signal (" << signum << ") has received.\n";
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
#endif // __SIGHANDL_H__