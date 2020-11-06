#include <iostream>
#include "argexec.hpp"

using namespace std;

int main(int argc, char **argv)
{
    argprox line(argc, argv);
    auto params = line.GetParams();
    for (auto &&i : params)
    {
        std::cout << i << endl;
    }

    std::cout << std::endl;

    auto args = line.GetArgs();
    for (auto &&i : args)
    {
        std::cout << i << endl;
    }
    return 0;
}