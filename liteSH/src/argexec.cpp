#include "argexec.hpp"

namespace {
    class args_proxy : public argsParser {
    private:
        static constexpr std::array<std::pair<std::string_view, std::string_view>, 7> proxy = {{
                                                                                                      {"help", "h"},
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

    void GetHelp(fs::path p) {
        p.remove_filename();
        p /= "man.txt";
        file::File help(p.string());
        auto res = help.GetContent();
        std::cout << res;
    }
} // namespace

void argexec::ArgExec(int argc, char **argv) {
    args_proxy arg(argc, argv);
    auto arg_tokens = arg.GetArgs();
    auto paths = arg.GetParams();

    paths.erase(paths.begin()); // firs element it self binary path

    if (arg_tokens.empty()) {
        return;
    }

    if (arg_tokens.size() > 1) {
        std::cout << "Arguments error (0_0)" << std::endl;
        GetHelp(fs::path(argv[0]));
        return;
    }
    if (!paths.empty())
        if (paths[0] != "h") {
            std::cout << "Arguments paths error (0_0)" << std::endl;
            GetHelp(fs::path(argv[0]));
            return;
        }

    auto token = arg_tokens[0].c_str()[0];

    try {
        file::File *f;

        if (token == 'h')
            GetHelp(fs::path(argv[0]));
        else
            throw Except("Undef argument");

    }
    catch (const std::exception &e) {
        std::cout << e.what() << '\n';
        std::cout << "try liteSh -h for help" << std::endl;
    }

}