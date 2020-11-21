//
// Created by liember on 11/21/20.
//

#ifndef AWS_SHELL_H
#define AWS_SHELL_H

#include <iostream>

#include "cmdline.hpp"
#include "proc.hpp"
#include "http/client.hpp"

class shell {

private:
    static constexpr std::string_view fctrl_path = "./fctrl/fctrl";
    static constexpr  int buff_size = 2048;

    cmdline input_line;
    subproc procs;

public:
    explicit shell(std::string shell_name);
    void input(std::istream &inp_stream);
};


#endif //AWS_SHELL_H
