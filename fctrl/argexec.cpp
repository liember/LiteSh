#include "argexec.hpp"
namespace
{
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

    bool IsNum(const char *ch)
    {
        for (; *ch; ch++)
            if (!isdigit(*ch))
                return false;
        return true;
    }

    std::vector<std::pair<int, std::string>> &GetProcs()
    {
        auto result = new std::vector<std::pair<int, std::string>>();
        constexpr std::string_view procdir = "/proc/";

        if (!fs::exists(procdir))
            throw Except("Couldn't open the PROC_DIRECTORY");

        for (auto &p : fs::directory_iterator(procdir))
        {
            std::string name = p.path().filename();
            if (IsNum(name.c_str())) // only pid-proc directories needed
            {
                std::string buf, fpath = p.path() / "cmdline";
                std::ifstream file(fpath);
                getline(file, buf);

                if (buf.size() > 0)
                {
                    std::pair<int, std::string> a;
                    a.first = std::stoi(name);
                    a.second = buf;
                    result->push_back(a);
                }
            }
        }
        return *result;
    }

    void GetHelp(fs::path p)
    {
        p.remove_filename();
        p /= "man.txt";
        fctrl::File help(p.string());
        auto res = help.GetContent();
        std::cout << res;
    }

} // namespace

void argexec(int argc, char **argv)
{
    argprox arg(argc, argv);
    auto arg_tokens = arg.GetArgs();
    auto paths = arg.GetParams();

    paths.erase(paths.begin()); // firs element it self binary path

    if (arg_tokens.size() != 1)
    {
        std::cout << "Arguments error (0_0)" << std::endl;
        GetHelp(fs::path(argv[0]));
    }
    if (paths.size() > 2)
        if (paths[0] != "h")
        {
            std::cout << "Arguments paths error (0_0)" << std::endl;
            GetHelp(fs::path(argv[0]));
        }

    auto token = arg_tokens[0].c_str()[0];

    try
    {

        fctrl::File *f;

        switch (token)
        {
        case 'm':
            if (paths.size() != 2)
                throw Except("2 arguments needed");
            f = new fctrl::File(paths[0]);
            f->Move(paths[1]);
            break;
        case 'c':
            if (paths.size() != 2)
                throw Except("2 arguments needed");
            f = new fctrl::File(paths[0]);
            f->Copy(paths[1]);
            break;
        case 'd':
            if (paths.size() != 1)
                throw Except("1 arguments needed");
            f = new fctrl::File(paths[0]);
            f->Delete();
            break;
        case 's':
            if (paths.size() != 1)
                throw Except("1 arguments needed");
            f = new fctrl::File(paths[0]);
            std::cout << f->Size() << std::endl;
            break;
        case 'l':
            if (paths.size() != 1)
                throw Except("1 arguments needed");
            f = new fctrl::File(paths[0]);
            std::cout << f->GetContent() << std::endl;
            break;
        case 'p':
            if (paths.size() == 0)
                for (auto [pid, process] : GetProcs())
                    std::cout << "Pid: " << pid << " " << process << std::endl;
            break;
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