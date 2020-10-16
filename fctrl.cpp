#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "exeptions.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace lab2
{
    class File
    {
    private:
        const string fname;

    public:
        void Copy(string path) { fs::copy(fname, path); }
        unsigned int Size() { return fs::file_size(fname); }
        void Delete() { fs::remove_all(fname.c_str()); }

        void Move(string fpath)
        {
            fs::path filedir;
            filedir = fpath;
            filedir.remove_filename();
            fs::path dir = fs::current_path();
            fs::create_directories(dir / filedir);
            cout << dir / filedir;
            Copy(fpath);
            Delete();
        }

        string GetContent()
        {
            string result;
            auto info = fs::status(fname);
            if (fs::is_directory(info)) // if directory eq (ls -l)
            {
                for (auto &p : fs::directory_iterator(fname))
                    result = result + p.path().filename().string() + '\n';
            }
            else // else eq (cat fname)
            {
                string line;
                std::ifstream in(fname); // already checked in File::File()
                while (getline(in, line))
                    result = result + line + "\n";
                in.close();
            }
            return result;
        }

        File(string filename) : fname(filename)
        {
            const string msg = "lab2::File error: File is not exist: [" + fname + "]";
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
        const string procdir = "/proc/";
        if (!fs::exists(procdir))
            throw Except("Couldn't open the PROC_DIRECTORY");

        cout << "pid:process\n";
        for (auto &p : fs::directory_iterator(procdir))
        {
            string name = p.path().filename();
            if (IsNum(name.c_str())) // only pid-proc directories needed
            {
                string buf, fpath = p.path() / "cmdline";
                ifstream file(fpath);
                getline(file, buf);
                if (buf.size() > 0)
                    cout << name + ": " + buf + "\n";
            }
        }
    }
}; // namespace lab2

int main(int argc, char *argv[])
{
    const string arg = "--";
    const string ar = "-";
    const string arg_move = "move";
    const string arg_copy = "copy";
    const string arg_delete = "delete";
    const string arg_list = "list";
    const string arg_size = "size";
    const string arg_proc = "show-proc";
    const string arg_help = "help";
    const string ar_move = "M";
    const string ar_copy = "C";
    const string ar_delete = "D";
    const string ar_list = "L";
    const string ar_size = "S";
    const string ar_proc = "P";
    const string ar_help = "H";

    const string nonargs = "fctrl: missing file operand\nTry 'fctrl --help' for more information.";
    string args = argv[1];
    try
    {
        auto res1 = args.find(arg + arg_move);
        auto res2 = args.find(ar + ar_move);
        if (res1 != std::string::npos || res2 != std::string::npos)
        {
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}