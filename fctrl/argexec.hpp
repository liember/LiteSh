#ifndef __ARGEXEC_H__
#define __ARGEXEC_H__

#include <array>
#include <utility>
#include <algorithm>

#include "argsParser.hpp"
#include "file.hpp"
#include "procfs.hpp"
#include "exeptions.hpp"

void args_execute(int argc, char **argv);

#endif // __ARGEXEC_H__