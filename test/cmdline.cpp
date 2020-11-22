//
// Created by liember on 11/17/20.
//

#include "gtest/gtest.h"
#include "cmdline/cmdline.hpp"
#include <string>
#include "strstream"

auto buf_size = 2059;
std::string name = "shell";
auto test_string = "hello it arguments for cmdline test";

TEST(cmdline, init) {
    cmdline shell(name, buf_size);
    ASSERT_STREQ(shell.getName().data(), name.c_str());
}

TEST(cmdline, dyn_init) {
    char *tst_name = new char[20];
    strcpy(tst_name, name.c_str());
    cmdline shell(tst_name, buf_size);
    delete[] tst_name;
    ASSERT_STREQ(shell.getName().data(), name.c_str());
}

TEST(cmdline, string_stream) {
    std::string str = "hello world";
    cmdline sh(name.c_str(), buf_size);
    std::stringstream ss(str);
    sh.input(ss);
    auto v = sh.get_v();
    ASSERT_EQ(sh.size(),2);
    ASSERT_STREQ(v[0].c_str(),"hello");
    ASSERT_STREQ(v[1].c_str(),"world");

}

TEST(cmdline, get_cv) {
    cmdline shell(name, buf_size);
    std::stringstream ss1(test_string);
    std::stringstream ss2(test_string);
    shell.input(ss1);

    auto result = shell.get_cv();

    ASSERT_EQ(shell.size(), result.size());
    for (int i = 0; i < shell.size(); ++i) {
        ASSERT_STREQ(result.raw()[i], shell[i].c_str());
    }
}

