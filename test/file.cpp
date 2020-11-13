#include "file.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <filesystem>

const std::string file_name = "file_test.txt";
const std::string file_content = "IT IS CONTENT OF TEST FILE";


TEST(file, init_normal)
{
    std::ofstream fout(file_name);
    fout.close();
    ASSERT_NO_THROW(file::File f(file_name););
    std::filesystem::remove_all(file_name);
}

TEST(file, init_without_file)
{
    ASSERT_THROW(file::File f(file_name), std::exception);
}
