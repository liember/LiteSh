#ifndef __ARGEXEC_H__
#define __ARGEXEC_H__

#include <array>
#include <utility>
#include <algorithm>

#include "argpars.hpp"
#include "exeptions.hpp"
#include "file.hpp"
#include "procfs.hpp"

void argexec(int argc, char **argv);

#endif // __ARGEXEC_H__