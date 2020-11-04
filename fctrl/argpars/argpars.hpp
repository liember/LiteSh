#pragma once

#include <vector>
#include <string>

class argpars
{
private:
    std::vector<std::string> args;
    std::vector<std::string> params;

public:
    auto GetParams(); ///< returns params from argv
    auto GetArgs();   ///< returns args (taged "-" or "--") from argv

    argpars(int argc, char **argv);
};
