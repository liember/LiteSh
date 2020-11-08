#pragma once

#include <filesystem>
#include <vector>
#include <utility>
#include <filesystem>
#include <fstream>

#include "exeptions.hpp"

namespace procfs
{
    std::vector<std::pair<int, std::string>> &GetProcs();
} // namespace procfs