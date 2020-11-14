//
// Created by liember on 11/13/20.
//

#include "gtest/gtest.h"
#include "argpars/argsParser.hpp"

char *a[]{
        "--someword",
        "--oneword",
        "--twoword",
        "-w",
        "wasd",
};

const std::vector<std::string> args_v{"someword",
                                      "oneword",
                                      "twoword",
                                      "w",};

TEST(argsParser, zero_args_params_init) {
    ASSERT_NO_THROW(argsParser p(0, nullptr));
}

TEST(argsParser, zero_args_params_get) {
    argsParser p(0, nullptr);
    auto size = p.GetArgs().size();
    ASSERT_EQ(size, 0);
    size = p.GetParams().size();
    ASSERT_EQ(size, 0);
}

TEST(argsParser, normal_args_init) {
    ASSERT_NO_THROW(argsParser p(4, a));
}

TEST(argsParser, normal_args_get) {
    argsParser p(4, a);
    auto size = p.GetArgs().size();
    ASSERT_EQ(size, 4);
    size = p.GetParams().size();
    ASSERT_EQ(size, 0);
    ASSERT_TRUE(args_v == p.GetArgs());
}

TEST(argsParser, normal_params_get) {
    argsParser p(5, a);
    auto size = p.GetArgs().size();
    ASSERT_EQ(size, 4);
    size = p.GetParams().size();
    ASSERT_EQ(size, 1);
    ASSERT_TRUE("wasd" == *p.GetParams().begin());
}