#include "argsParser.hpp"
#include <iostream>
#include "array"
#include "algorithm"
#include "exceptions.hpp"
#include "filesystem"
#include "file.hpp"

namespace argexec
{
    enum init_flag{
        server,
        local
    };

    init_flag ArgExec(int argc, char **argv);
} // namespace args_execute