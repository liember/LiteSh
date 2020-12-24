#include "argexec.hpp"
#include "dlload.h"

namespace {
    class args_proxy : public argsParser {
    private:
        static constexpr std::array<std::pair<std::string_view, std::string_view>, 7> proxy = {{
                                                                                                       {"help", "h"},
                                                                                                       {"server", "s"},
                                                                                                       {"dlload", "l"},
                                                                                               }};

    public:
        args_proxy(int argc, char **argv) : argsParser(argc, argv) {
            // prox commands (--command) to equal flag
            for (auto &i : GetArgs()) {
                if (i.size() > 1) {
                    auto target = [i](const std::pair<std::string_view, std::string_view> &element) {
                        return element.first == i;
                    };
                    auto[word, flag] = *std::find_if(proxy.begin(), proxy.end(), target);

                    if (i == word) {
                        i = flag;
                    } else {
                        auto err_msg = "Undefined argument: " + i;
                        throw Except(err_msg);
                    }
                }
            }
        }
    };

    void GetHelp() {
        file::File help("/opt/litesh/man.txt");
        auto res = help.GetContent();
        std::cout << res;
    }
} // namespace

argexec::init_flag argexec::ArgExec(int argc, char **argv) {
    args_proxy arg(argc, argv);
    auto arg_tokens = arg.GetArgs();
    auto paths = arg.GetParams();

    paths.erase(paths.begin()); // firs element it self binary path

    if (arg_tokens.empty()) {
        return init_flag::local;
    }

    if (arg_tokens.size() > 1) {
        std::cout << "Arguments error (0_0)" << std::endl;
        GetHelp();
        return init_flag::local;
    }
    auto token = arg_tokens[0].c_str()[0];

    try {
        if (token == 'h')
            GetHelp();
        else if (token == 's') {
            return init_flag::server;
        } else if (token == 'l') {
            loadLib(paths[0], paths[1]);
            return init_flag::dlload;
        } else {
            throw Except("Undef argument");
        }
    }
    catch (const std::exception &e) {
        std::cout << e.what() << '\n';
        std::cout << "try liteSh -h for help" << std::endl;
    }
    return init_flag::local;
}