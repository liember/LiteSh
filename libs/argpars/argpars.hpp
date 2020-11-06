#pragma once

#include <vector>
#include <string>

class argpars
{
private:
    std::vector<std::string> args;
    std::vector<std::string> params;

public:
    std::vector<std::string> &GetParams(); ///< returns params from argv
    std::vector<std::string> &GetArgs();   ///< returns args (taged "-" or "--") from argv

    argpars(int argc, char **argv);
};
