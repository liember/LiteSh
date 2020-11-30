//
// Created by liember on 11/27/20.
//
#pragma once

#include <iostream>
#include <dlfcn.h>
#include "filesystem"
#include "exceptions.hpp"

void loadLib(const std::string& file, const std::string& foo_name) {
    auto f_exists = std::filesystem::exists(file);
    if (!f_exists)
        throw Except("file does not exists");

    auto path = "./" + file;

    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle)
        throw Except(dlerror());

    typedef void (*func_t)();
    auto func = (func_t) dlsym(handle, foo_name.c_str());
    std::cout << "foo name: " << foo_name.c_str() << std::endl;

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        dlclose(handle);
        throw Except(dlsym_error);
    }

    func();
    std::cout << "fun end\n";
    dlclose(handle);
}

