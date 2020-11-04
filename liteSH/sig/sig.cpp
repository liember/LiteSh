#include "sighandl.hpp"

void sighandl::interrupt(int signum)
{
    cout << "The great interrupt signal (" << signum << ") has received.\n";
    exit(signum);
}

sighandl::sighandl(/* args */)
{
    signal(SIGINT, interrupt);
}

sighandl *sighandl::getInstance()
{
    if (!instance)
        instance = new sighandl;
    return instance;
}

sighandl *sighandl::instance = 0;