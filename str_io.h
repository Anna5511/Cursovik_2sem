#ifndef STR_IO_H
#define STR_IO_H

#include "str.h"
#include <fstream>

str* read_line_from_stream(std::ifstream& file);

#endif