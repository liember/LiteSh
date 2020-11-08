#include <iostream>
#include <sstream>

#include "proc.hpp"
#include "sighandl.hpp"
#include "argpars.hpp"

using namespace std;
namespace
{
    class argprox : public argpars
    {
    private:
        static constexpr std::array<std::pair<std::string_view, std::string_view>, 7> prox = {{
            {"help", "h"},
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

    void GetHelp(fs::path p)
    {
        p.remove_filename();
        p /= "man.txt";
        fctrl::File help(p.string());
        auto res = help.GetContent();
        std::cout << res;
    }

    void argexec(int argc, char **argv)
    {
        argprox arg(argc, argv);
        auto arg_tokens = arg.GetArgs();
        auto paths = arg.GetParams();

        paths.erase(paths.begin()); // firs element it self binary path

        if (arg_tokens.size() == 0)
        {
            return;
        }

        if (arg_tokens.size() > 1)
        {
            std::cout << "Arguments error (0_0)" << std::endl;
            GetHelp(fs::path(argv[0]));
            return;
        }
        if (paths.size() > 0)
            if (paths[0] != "h")
            {
                std::cout << "Arguments paths error (0_0)" << std::endl;
                GetHelp(fs::path(argv[0]));
                return;
            }

        auto token = arg_tokens[0].c_str()[0];

        try
        {
            fctrl::File *f;

            switch (token)
            {
            case 'h':
                GetHelp(fs::path(argv[0]));
                break;
            default:
                throw Except("Undef argument");
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << '\n';
            std::cout << "try fctrl -h for help" << std::endl;
        }
    }

} // namespace

void PrintInnerHelp()
{
    cout << "===========================" << endl;
    cout << "Enter the required action: " << endl;
    cout << "'-l2' - Command line from lab 2" << endl;
    cout << "'-p' - Spawn a process by name" << endl;
    cout << "'-pb' - Put the process in the background" << endl;
    cout << "'-signal' - Processing of signals" << endl;
    cout << "===========================" << endl;
}

int main(int argc, char **argv)
{
    constexpr std::string_view fctrl_path = "./fctrl/fctrl";

    auto sig = sighandl::getInstance();
    auto procs = subproc();

    argexec(argc, argv);
    char str[256];

    while (1)
    {
        cout << "liteSH:  ";
        cin.getline(str, 256);

        string buf(str), input, arg;
        std::stringstream ss(buf);
        string s;
        ss >> input;
        ss >> arg;

        if (input == "fctrl")
            procs.Spawn(fctrl_path.data(), false);
        else if (input == "spawn")
            procs.Spawn(arg, false);
        else if (input == "spawnf")
            procs.Spawn(arg, false);
        else
            cout << "Incorrect input" << endl;
    }
    return 0;
}