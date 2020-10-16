#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "exeptions.hpp"

namespace fs = std::filesystem;

namespace lab2
{
    class File
    {
    private:
        const std::string fname;

    public:
        void Copy(std::string path) { fs::copy(fname, path); }
        unsigned int Size() { return fs::file_size(fname); }
        void Delete() { fs::remove_all(fname.c_str()); }

        void Move(std::string fpath)
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

        std::string GetContent()
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

        File(std::string filename) : fname(filename)
        {
            const std::string msg = "lab2::File error: File is not exist: [" + fname + "]";
            if (!fs::exists(fname))
                throw Except(msg);
        }
    };

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

    void CatProc()
    {
        const std::string procdir = "/proc/";
        if (!fs::exists(procdir))
            throw Except("Couldn't open the PROC_DIRECTORY");

        std::cout << "pid:process\n";
        for (auto &p : fs::directory_iterator(procdir))
        {
            std::string name = p.path().filename();
            if (IsNum(name.c_str())) // only pid-proc directories needed
            {
                std::string buf, fpath = p.path() / "cmdline";
                std::ifstream file(fpath);
                getline(file, buf);
                if (buf.size() > 0)
                    std::cout << name + ": " + buf + "\n";
            }
        }
    }
}; // namespace lab2
