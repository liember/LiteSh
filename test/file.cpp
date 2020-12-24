#include "file.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <filesystem>

inline const std::string file_name = "file_test.txt";
inline const std::string file_content = "IT IS CONTENT OF TEST FILE\n";
inline const std::string folder_dest = "dest/";

TEST(file, init_exists) {
    std::ofstream fout(file_name);
    fout.close();
    ASSERT_NO_THROW(file::File f(file_name););
    std::filesystem::remove_all(file_name);
}

TEST(file, init_unexists) {
    ASSERT_THROW(file::File f(file_name), std::exception);
}

TEST(file, move) {
    std::ofstream fout(file_name);
    fout.close();
    file::File f(file_name);

    ASSERT_NO_THROW(f.Move(folder_dest + file_name));
    bool dest_exist = std::filesystem::exists(folder_dest + file_name);
    bool src_deleted = !std::filesystem::exists(file_name);
    ASSERT_TRUE(src_deleted && dest_exist);
    std::filesystem::remove_all(folder_dest);
}

TEST(file, move_in_self) {
    std::ofstream fout(file_name);
    fout.close();
    file::File f(file_name);

    ASSERT_NO_THROW(f.Move(file_name));
    bool dest_exist = std::filesystem::exists(file_name);
    ASSERT_TRUE(dest_exist);
    std::filesystem::remove_all(folder_dest);
}

TEST(file, copy) {
    std::ofstream fout(file_name);
    fout.close();
    file::File f(file_name);

    ASSERT_NO_THROW(f.Copy(folder_dest + file_name));
    bool dest_exist = std::filesystem::exists(folder_dest + file_name);
    bool src_deleted = std::filesystem::exists(file_name);
    ASSERT_TRUE(src_deleted && dest_exist);
    std::filesystem::remove_all(folder_dest);
}

TEST(file, delete_file) {
    std::ofstream fout(file_name);
    fout.close();
    file::File f(file_name);
    ASSERT_NO_THROW(f.Delete());
    ASSERT_TRUE(!std::filesystem::exists(file_name));
}

TEST(file, delete_directory) {
    fs::create_directories(folder_dest);
    std::ofstream fout(folder_dest + file_name);
    fout.close();
    file::File f(folder_dest);
    ASSERT_NO_THROW(f.Delete());
    ASSERT_TRUE(!std::filesystem::exists(folder_dest + file_name));
}

TEST(file, get_content_file) {
    std::ofstream fout(file_name);
    fout << file_content;
    fout.close();
    file::File f(file_name);
    ASSERT_STREQ(f.GetContent().c_str() , file_content.c_str());
    f.Delete();
}

TEST(file, get_content_directory) {
    fs::create_directories(folder_dest);
    std::ofstream fout(folder_dest + file_name);
    fout.close();

    file::File f(folder_dest);
    auto name = file_name + "\n";
    ASSERT_STREQ(f.GetContent().c_str() , name.c_str());
    f.Delete();
}

TEST(file, get_size_file) {
    std::ofstream fout(file_name);
    fout << file_content;
    fout.close();
    file::File f(file_name);
    ASSERT_EQ(f.Size() , file_content.size());
    f.Delete();
}

TEST(file, get_size_directory) {
    fs::create_directories(folder_dest);
    std::ofstream fout(folder_dest + file_name);
    fout << file_content;
    fout.close();

    file::File f(folder_dest);
    auto name = file_name + "\n";
    ASSERT_EQ(f.Size() , file_content.size());
    f.Delete();
}