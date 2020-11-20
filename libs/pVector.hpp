#pragma once

#include "vector"
#include "memory"
#include "exceptions.hpp"

template<class T>
class pVector {
private:
    std::vector<T *> *storage;
    T **res;
    bool *released;
    unsigned *ref_counter;

public:
    pVector() {
        ref_counter = new unsigned;
        *ref_counter = 1;
        storage = new std::vector<T *>;
        released = new bool;
        *released = false;
    }

    pVector(const pVector &src) {
        ref_counter = src.ref_counter;
        *ref_counter += 1;
        storage = src.storage;
        released = src.released;
        res = src.res;
        release();
    }

    pVector &operator=(const pVector &a) { return *this; }

    ~pVector() {
        if (*ref_counter <= 1) {
            if (released)
                delete res;
            for (auto &&i : *storage) {
                delete i;
            }
            delete ref_counter;
            delete storage;
            delete released;
        } else {
            *ref_counter--;
        }
    }

    auto push_back(T *element) {
        if (!*released) {
            storage->push_back(element);
            return true;
        }
        return false;
    }

    void release() {
        if (!*released) {
            *released = true;
            auto size = storage->size();
            res = new T *[size + 1];
            std::vector<T *> &vecRef = *storage;
            for (size_t i = 0; i < size; i++) {
                res[i] = vecRef[i];
            }
            res[size] = (T *) nullptr;
        }
    }

    auto size() const {
        return storage->size();
    }

    auto get() const {
        if (*released)
            return res;
        throw Except("Unreleased pVector cant give pointer to vector");
    }
};