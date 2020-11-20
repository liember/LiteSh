//
// Created by liember on 11/18/20.
//

#include "gtest/gtest.h"
#include "pVector.hpp"

const static std::string a[] = {"word1", "word2", "word3", "word4", "word5"};

TEST(pVector, memory) {
    auto vec = new pVector<char>;
    char *w1;
    for (int i = 0; i < 1000; ++i) {
        w1 = new char[100];
        strcpy(w1, "word");
        vec->push_back(w1);
    }
    ASSERT_NO_THROW(delete vec);
}

TEST(pVector, release) {
    auto vec = new pVector<char>;
    char *w1;
    for (auto &i : a) {
        w1 = new char[100];
        strcpy(w1, i.c_str());
        vec->push_back(w1);
    }
    vec->release();
    for (int i = 0; i < vec->size(); ++i) {
        ASSERT_STREQ(vec->get()[i], a[i].c_str());
    }
    ASSERT_NO_THROW(delete vec);
}

TEST(pVector, copy_released) {
    auto vec1 = new pVector<char>;
    char *w1;
    for (const auto &i : a) {
        w1 = new char[100];
        strcpy(w1, i.c_str());
        vec1->push_back(w1);
    }
    vec1->release();

    for (int i = 0; i < 5; ++i) {
        ASSERT_STREQ(a[i].c_str(), vec1->get()[i]);
    }

    pVector<char> vec2(*vec1);
    delete vec1;

    auto chk = vec2.get();
    for (int i = 0; i < 5; ++i) {
        ASSERT_STREQ(a[i].c_str(), chk[i]);
    }
}

TEST(pVector, copy_unreleased) {
    auto vec1 = new pVector<char>;
    char *w1;
    for (const auto &i : a) {
        w1 = new char[100];
        strcpy(w1, i.c_str());
        vec1->push_back(w1);
    }

    pVector<char> vec2(*vec1);
    delete vec1;
    vec2.release();
    auto chk = vec2.get();
    for (int i = 0; i < 5; ++i) {
        ASSERT_STREQ(a[i].c_str(), chk[i]);
    }
}

pVector<char> foo() {
    pVector<char> res;
    char *w1;
    for (const auto &i : a) {
        w1 = new char[100];
        strcpy(w1, i.c_str());
        res.push_back(w1);
    }
    res.release();
    return res;
}

TEST(pVector, return_from_function) {
    auto vec = foo();
    auto res = vec.get();
    for (int i = 0; i < vec.size(); ++i) {
        ASSERT_STREQ(res[i], a[i].c_str());
    }
}