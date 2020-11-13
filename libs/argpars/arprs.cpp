#include "argsParser.hpp"

std::vector<std::string> &argsParser::GetParams() ///< returns params from argv
{
    return params;
}

std::vector<std::string> &argsParser::GetArgs() ///< returns args (tagged "-" or "--") from argv
{
    return args;
}

argsParser::argsParser(int argc, char **argv) {
    for (auto i = 0; i < argc; i++) {
        std::string cur_word = argv[i];
        auto length = cur_word.size();

        if (cur_word[0] == '-' && length > 1) {
            if (cur_word[1] == '-') {
                cur_word = cur_word.substr(2, length);
                args.push_back(cur_word);
            } else {
                cur_word = cur_word.substr(1, length);
                for (auto &&ch : cur_word) {
                    std::string flag(1, ch);
                    args.push_back(flag);
                }
            }
        } else
            params.push_back(cur_word);
    }
}
