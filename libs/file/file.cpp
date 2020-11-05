#include "file.hpp"

using namespace fctrl;

void File::Copy(std::string path) { fs::copy(fname, path); }
unsigned int File::Size() { return fs::file_size(fname); }
void File::Delete() { fs::remove_all(fname.c_str()); }

void File::Move(std::string fpath)
{
    fs::path filedir;
    filedir = fpath;
    filedir.remove_filename();
    fs::path dir = fs::current_path();
    fs::create_directories(dir / filedir);
    std::cout << dir / filedir;
    Copy(fpath);
    Delete();
}

std::string File::GetContent()
{
    std::string result;
    auto info = fs::status(fname);
    if (fs::is_directory(info)) // if directory eq (ls -l)
    {
        for (auto &p : fs::directory_iterator(fname))
            result = result + p.path().filename().string() + '\n';
    }
    else // else eq (cat fname)
    {
        std::string line;
        std::ifstream in(fname); // already checked in File::File()
        while (getline(in, line))
            result = result + line + "\n";
        in.close();
    }
    return result;
}

File::File(std::string filename) : fname(filename)
{
    const std::string msg = "lab2::File error: File is not exist: [" + fname + "]";
    if (!fs::exists(fname))
        throw Except(msg);
}

std::vector<std::pair<int, std::string>> GetProcs()
{
    std::vector<std::pair<int, std::string>> result;
    const std::string procdir = "/proc/";

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
                result.push_back(a);
            }
        }
    }
    return std::move(result);
}
