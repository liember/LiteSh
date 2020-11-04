#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <vector>
#include <utility>

#include "exeptions.hpp"

namespace fs = std::filesystem;

namespace fctrl
{
    class File
    {
    private:
        const std::string fname;

    public:
        void Copy(std::string path);
        unsigned int Size();
        void Delete();
        void Move(std::string fpath);
        std::string GetContent();
        File(std::string filename);
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

    std::vector<std::pair<int, std::string>> &GetProcs();
}; // namespace fctrl
