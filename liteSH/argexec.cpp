#include "argexec.hpp"

namespace {
    inline auto args_proxy(int argc, char **argv) {
        argsParser ap(argc, argv);
        for (auto &i : ap.GetArgs()) {
            if (i.size() > 1) {
                auto target = [i](const std::pair<std::string_view, std::string_view> &element) {
                    return element.first == i;
                };
                auto[word, flag] = *std::find_if(argexec::proxy.begin(), argexec::proxy.end(), target);

                if (i == word) {
                    i = flag;
                } else {
                    auto err_msg = "Undefined argument: " + i;
                    throw Except(err_msg);
                }
            }
        }
        return std::move(ap);
    }
} // namespace

argexec::init_flag argexec::ArgExec(int argc, char **argv) {
    auto arg = args_proxy(argc, argv);
    auto arg_tokens = arg.GetArgs();
    auto paths = arg.GetParams();

    paths.erase(paths.begin()); // firs element it self binary path
    if (arg_tokens.empty()) {
        return init_flag::local;
    } else {
        auto token = arg_tokens[0].c_str()[0];
        try {
            if (token == 'h') {
                file::File help(man_path.data());
                std::cout << help.GetContent();
                exit(0);
            } else if (token == 's') {
                return init_flag::server;
            } else {
                throw Except("Undef argument");
            }
        }
        catch (const std::exception &e) {
            std::cout << e.what() << '\n';
            std::cout << "try liteSh -h for help" << std::endl;
        }

    }
    return init_flag::local;
}