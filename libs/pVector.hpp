#pragma once

#include "vector"

template<class T>
class pVector {
private:
    std::vector<T *> storage;
    T **res;
    bool released;
public:
    pVector() {
        released = false;
    }

    ~pVector() {
        if (released)
            delete res;
        for (auto &&i : storage) {
            delete i;
        }
    }

    auto push_back(T *element) {
        if (!released) {
            storage.push_back(element);
            return true;
        }
        return false;
    }

    auto size(){
        return storage.size();
    }

    T** release() {
        if (!released) {
            released = true;
            auto size = storage.size();
            res = new T *[size + 1];
            for (size_t i = 0; i < size; i++) {
                res[i] = storage[i];
            }
            res[size] = (T *) nullptr;
        }
        return res;
    }
};