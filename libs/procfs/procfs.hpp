#pragma once

#include <filesystem>
#include <vector>
#include <utility>
#include <filesystem>
#include <fstream>

#include "exceptions.hpp"

namespace procfs
{
    std::vector<std::pair<int, std::string>> &getProcesses();
} // namespace procfs