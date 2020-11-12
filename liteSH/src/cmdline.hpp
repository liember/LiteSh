#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>

#include "exeptions.hpp"

#ifndef __CMDLINE_H__
#define __CMDLINE_H__

class cmdline {
private:
    int buff_size = 256;
    std::string word_buffer;
    const std::string shell_name;
    std::vector<std::string> input_content;

public:
    explicit cmdline(std::string_view name) : shell_name(name) {}

    auto input() {
        char input_buffer[buff_size];
        input_content.clear();
        std::cout << shell_name << ": ";
        std::cin.getline(input_buffer, buff_size);
        std::stringstream stream(input_buffer);
        while (stream >> word_buffer) {
            input_content.push_back(word_buffer);
        }
        if (!input_content.empty()) {
            return true;
        }
        return false;
    }

    auto get_v() { return &input_content; }

    auto get_cv() {
        auto count = input_content.size();
        if (count == 0) {
            throw Except("cmdline size is 0 cant return char vector");
        }

        auto size = sizeof(char *);
        auto result = (char **) malloc(size * (count + 1));

        for (size_t i = 0; i < count; i++) {
            auto word_size = input_content[i].size();
            result[i] = (char *) malloc(sizeof(char) * (word_size + 1));
            strcpy(result[i], input_content[i].c_str());
        }
        result[count + 1] = (char *) nullptr;
        return result;
    }

    auto size() { return input_content.size(); }

    auto &operator[](const int index) {
        auto size = input_content.size();
        if (index > size || size == 0) {
            throw Except("cmdline index not exist");
        }
        return input_content[index];
    }

    auto pop_front() {
        if (input_content.empty()) {
            throw Except("cmdline size is 0 cant remove first");
        }
        input_content.erase(input_content.begin());
    }
};

#endif // __CMDLINE_H__