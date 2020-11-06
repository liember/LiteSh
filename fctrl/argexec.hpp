#ifndef __ARGEXEC_H__
#define __ARGEXEC_H__

#include <array>
#include <utility>
#include <algorithm>

#include "argpars.hpp"
#include "exeptions.hpp"

class argprox : public argpars
{
private:
    static constexpr std::array<std::pair<std::string_view, std::string_view>, 7> prox = {{
        {"help", "h"},
        {"move", "m"},
        {"copy", "c"},
        {"delete", "d"},
        {"size", "s"},
        {"list", "l"},
        {"procs", "p"},
    }};

public:
    argprox(int argc, char **argv) : argpars(argc, argv)
    {
        // prox commands (--command) to equal flag
        for (auto &i : GetArgs())
        {
            if (i.size() > 1)
            {
                auto target = [i](const std::pair<std::string_view, std::string_view> &element) {
                    return element.first == i;
                };
                auto [word, flag] = *std::find_if(prox.begin(), prox.end(), target);

                if (i == word)
                {
                    i = flag;
                }
                else
                {
                    auto err_msg = "Undefined argument: " + i;
                    throw Except(err_msg);
                }
            }
        }
    }
};

#endif // __ARGEXEC_H__