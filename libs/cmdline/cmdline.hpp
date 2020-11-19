#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <memory>
#include <fstream>

#include "exceptions.hpp"

#ifndef __CMDLINE_H__
#define __CMDLINE_H__

class cmdline {
private:
    const unsigned int _buff_size = 256;
    std::string word_buffer;
    const std::string shell_name;
    std::vector<std::string> input_content;

public:
    explicit cmdline(std::string_view name, unsigned int buff_size);

    std::string_view getName();

    bool input(std::istream &inp_stream);

    std::vector<std::string> &get_v();

    char **get_cv();

    unsigned long size();

    std::string &operator[](unsigned int index);

    void pop_front();
};

#endif // __CMDLINE_H__