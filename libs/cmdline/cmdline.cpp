#include "cmdline.hpp"

unsigned long cmdline::size() { return input_content.size(); }

cmdline::cmdline(std::string_view name, unsigned int buff_size) :
        shell_name(name), _buff_size(buff_size) {}

std::string_view cmdline::getName() { return shell_name; }

bool cmdline::input(std::istream &inp_stream) {
    char input_buffer[_buff_size];
    input_content.clear();
    inp_stream.getline(input_buffer, _buff_size);
    std::stringstream stream(input_buffer);
    while (stream >> word_buffer) {
        input_content.push_back(word_buffer);
    }
    if (!input_content.empty())
        return true;
    return false;
}

std::vector<std::string> cmdline::get_v() { return input_content; }

pVector<char> cmdline::get_cv() {
    auto count = input_content.size();
    if (count == 0)
        throw Except("cmdline size is 0 cant return char vector");
    pVector<char> result;

    for (auto i = 0; i < count; i++) {
        auto word_size = input_content[i].size() + 1;
        auto el = new char[word_size];
        strcpy(el, input_content[i].c_str());
        result.push_back(el);
    }
    result.release();
    return result;
}

std::string &cmdline::operator[](const unsigned int index) {
    auto size = input_content.size();
    if (index > size || size == 0) {
        throw Except("cmdline index not exist");
    }
    return input_content[index];
}

void cmdline::pop_front() {
    if (input_content.empty()) {
        throw Except("cmdline size is 0 cant remove first");
    }
    input_content.erase(input_content.begin());
}