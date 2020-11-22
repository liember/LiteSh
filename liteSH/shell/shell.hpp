//
// Created by liember on 11/21/20.
//

#ifndef AWS_SHELL_H
#define AWS_SHELL_H

#include <iostream>

#include "cmdline.hpp"
#include "proc.hpp"
#include "boost/asio.hpp"

class shell {

private:
    static constexpr std::string_view fctrl_path = "./fctrl/fctrl";
    static constexpr int buff_size = 2048;

    cmdline input_line;
    subproc procs;

    std::string exec_result;
public:
    std::string getExecResult();

    explicit shell(const std::string &shell_name);

    bool input(std::istream &inp_stream);

    std::string_view getShellName();
};


#endif //AWS_SHELL_H
