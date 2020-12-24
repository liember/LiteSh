#include "file.hpp"

#include <utility>

using namespace file;

namespace {
    void createDirsToFile(const std::string &destination) {
        fs::path file_path = destination;
        file_path.remove_filename();
        fs::path current_dir = fs::current_path();
        fs::create_directories(current_dir / file_path);
    }
}

void File::Copy(const std::string &destination) {
    if (destination != file_name) {
        createDirsToFile(destination);
        fs::copy(file_name, destination);
    }
}

void File::Move(const std::string &destination) {
    if (destination != file_name) {
        createDirsToFile(destination);
        fs::copy(file_name, destination);
        Delete();
    }
}

unsigned int File::Size() {
    size_t size = 0;
    auto info = fs::status(file_name);
    if (fs::is_directory(info)) {
        for (auto &p : fs::recursive_directory_iterator(file_name)) {
            if (!fs::is_directory(p))
                size += fs::file_size(p);
        }
    } else {
        size = fs::file_size(file_name);
    }
    return size;
}

void File::Delete() { fs::remove_all(file_name.c_str()); }

std::string File::GetContent() {
    std::string content;
    auto info = fs::status(file_name);
    if (fs::is_directory(info)) {
        for (auto &p : fs::directory_iterator(file_name))
            content += p.path().filename().string() + '\n';
    } else {
        std::string line;
        std::ifstream in(file_name);
        while (getline(in, line))
            content += line + "\n";
        in.close();
    }
    return content;
}

File::File(std::string filename) : file_name(std::move(filename)) {
    const std::string msg = "lab2::File error: File is not exist: [" + file_name + "]";
    if (!fs::exists(file_name))
        throw Except(msg);
}
