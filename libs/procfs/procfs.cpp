#include "procfs.hpp"

namespace fs = std::filesystem;

namespace
{
    bool IsNum(const char *ch)
    {
        for (; *ch; ch++)
            if (!isdigit(*ch))
                return false;
        return true;
    }
} // namespace

std::vector<std::pair<int, std::string>> &procfs::getProcesses()
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