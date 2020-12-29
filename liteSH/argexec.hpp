#pragma once

#include "argsParser.hpp"
#include <iostream>
#include "array"
#include "algorithm"
#include "exceptions.hpp"
#include "filesystem"
#include "file.hpp"

namespace argexec
{
    inline constexpr std::string_view man_path("/opt/litesh/man.txt");
    typedef std::pair<std::string_view, std::string_view> word_flag;
    inline constexpr std::array<word_flag, 2> proxy = {{
                                                               {"help", "h"},
                                                               {"server", "s"},
                                                       }};

    enum init_flag{
        server,
        dlload,
        local,
    };

    init_flag ArgExec(int argc, char **argv);
} // namespace args_execute