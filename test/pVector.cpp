//
// Created by liember on 11/18/20.
//

#include "gtest/gtest.h"
#include "pVector.hpp"

TEST(pVector, memory) {
    auto vec = new pVector<char>;
    char *w1;
    for (int i = 0; i < 10000000; ++i) {
        w1 = new char[100];
        strcpy(w1, "word");
        vec->push_back(w1);
    }
    ASSERT_NO_THROW(delete vec);
}

TEST(pVector, release) {
    std::string a[] = {"word1", "word2", "word3", "word4", "word5"};
    auto vec = new pVector<char>;
    char *w1;
    for (int i = 0; i < 5; ++i) {
        w1 = new char[100];
        strcpy(w1, a[i].c_str());
        vec->push_back(w1);
    }
    auto rel = vec->release();
    for (int i = 0; i < vec->size(); ++i) {
        ASSERT_STREQ(rel[i],a[i].c_str());
    }
    ASSERT_NO_THROW(delete vec);
}

