//
// Created by liember on 11/17/20.
//

#include "gtest/gtest.h"
#include "cmdline/cmdline.hpp"
#include <string>
#include <strstream>

auto buf_size = 2059;
std::string name = "shell";
auto test_string = "hello it arguments for cmdline test";

TEST(cmdline,init){
    cmdline shell(name, buf_size);
    ASSERT_STREQ(shell.getName().data(),name.c_str());
}

TEST(cmdline,dyn_init){
    char * tst_name = new char[20];
    strcpy(tst_name,name.c_str());
    cmdline shell(tst_name, buf_size);
    delete[] tst_name;
    ASSERT_STREQ(shell.getName().data(),name.c_str());
}

//TEST(cmdline,get_cv){
//    cmdline shell(name, buf_size);
//    std::stringstream ss1(test_string);
//    std::stringstream ss2(test_string);
//    shell.input(ss1);
//
//    auto result = shell.get_cv();
//
//    for (int i = 0; i < shell.size(); ++i) {
//        char word[20];
//        ss2 >> word;
//        ASSERT_STREQ(result[i], word);
//    }
//
//    for (int i = 0; i < shell.size(); ++i) {
//        std::cout << result[i] << std::endl;
//        free(result[i]);
//    }
//    free(result);
//}

