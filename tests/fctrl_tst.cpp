#include "fctrl.hpp"
#include "gtest/gtest.h"
#include <fstream>

TEST(fsctrl, test1)
{
    int res = 2 + 2;
    EXPECT_EQ(res, 4);
}

TEST(fsctrl, test2)
{
    std::ofstream("test.txt");
    fctrl::File("test.txt");
    EXPECT_EQ(res, 4);
}