//
// Created by liember on 11/21/20.
//

#ifndef AWS_SHELL_H
#define AWS_SHELL_H

#include <iostream>

#include "cmdline.hpp"
#include "proc.hpp"
#include "boost/asio.hpp"

class shell : private cmdline {

private:
    static constexpr std::string_view fctrl_path = "/usr/local/bin/fctrl";
    static constexpr int buff_size = 2048;

    subproc procs;

    std::string exec_result;
public:
    std::string getExecResult();

    explicit shell(const std::string &shell_name);

    bool inputData(std::istream &inp_stream);

    std::string_view getShellName();
};


#endif //AWS_SHELL_H
