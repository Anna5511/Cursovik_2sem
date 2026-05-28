#ifndef FILE_IO_H
#define FILE_IO_H

#include "car.h"
#include "unique_lists.h"
#include <fstream>

int read_input(const char* filename,
    Car_List** car_head,
    UniqueStrNode** mark_head,
    UniqueIntNode** year_head,
    UniqueStrNode** color_head,
    UniqueStrNode** fio_head,
    UniqueStrNode** addr_head,
    std::ofstream& log);

void write_output(const char* filename, Car_List* head, std::ofstream& log);

#endif