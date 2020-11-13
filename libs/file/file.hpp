#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <vector>
#include <utility>

#include "exeptions.hpp"

namespace fs = std::filesystem;

namespace file {
    class File {
    private:
        const std::string &file_name;

    public:
        void Copy(const std::string &path);

        unsigned int Size();

        void Delete();

        void Move(const std::string &destination);

        std::string GetContent();

        explicit File(const std::string &filename);
    };

}; // namespace file
