#include "argexec.hpp"

namespace {
    class args_proxy : public argsParser {
    private:
        static constexpr std::array<std::pair<std::string_view, std::string_view>, 7> proxy = {{
                                                                                                       {"help", "h"},
                                                                                                       {"move", "m"},
                                                                                                       {"copy", "c"},
                                                                                                       {"delete", "d"},
                                                                                                       {"size", "s"},
                                                                                                       {"list", "l"},
                                                                                                       {"procs", "p"},
                                                                                               }};

    public:
        args_proxy(int argc, char **argv) : argsParser(argc, argv) {
            // proxy commands (--command) to equal flag
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
        file::File help("/opt/fctrl/man.txt");
        std::cout << help.GetContent();
    }

} // namespace

void args_execute(int argc, char **argv) {
    args_proxy arg(argc, argv);
    auto arg_tokens = arg.GetArgs();
    auto paths = arg.GetParams();

    paths.erase(paths.begin()); // firs element it self binary path

    if (arg_tokens.size() != 1) {
        std::cout << "Arguments error (0_0)" << std::endl;
        GetHelp();
        return;
    }
    if (paths.size() > 2)
        if (paths[0] != "h") {
            std::cout << "Arguments paths error (0_0)" << std::endl;
            GetHelp();
            return;
        }

    auto token = arg_tokens[0].c_str()[0];
    try {

        file::File *f;

        switch (token) {
            case 'm':
                if (paths.size() != 2)
                    throw Except("2 arguments needed");
                f = new file::File(paths[0]);
                f->Move(paths[1]);
                break;
            case 'c':
                if (paths.size() != 2)
                    throw Except("2 arguments needed");
                f = new file::File(paths[0]);
                f->Copy(paths[1]);
                break;
            case 'd':
                if (paths.size() != 1)
                    throw Except("1 arguments needed");
                f = new file::File(paths[0]);
                f->Delete();
                break;
            case 's':
                if (paths.size() != 1)
                    throw Except("1 arguments needed");
                f = new file::File(paths[0]);
                std::cout << f->Size() << std::endl;
                break;
            case 'l':
                if (paths.size() != 1)
                    throw Except("1 arguments needed");
                f = new file::File(paths[0]);
                std::cout << f->GetContent() << std::endl;
                break;
            case 'p':
                if (paths.empty())
                    for (auto[pid, process] : procfs::getProcesses())
                        std::cout << "Pid: " << pid << " " << process << std::endl;
                break;
            case 'h':
                GetHelp();
                break;
            default:
                throw Except("Undef argument");
                break;
        }
    }
    catch (const std::exception &e) {
        std::cout << e.what() << '\n';
        std::cout << "try fctrl -h for help" << std::endl;
    }
}
