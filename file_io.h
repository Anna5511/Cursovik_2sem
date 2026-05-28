#ifndef FILE_IO_H
#define FILE_IO_H

#include "car.h"
#include "unique_lists.h"
#include <fstream>

// Возвращает количество обработанных блоков
// Через параметры возвращает количество корректных и некорректных блоков
int read_input(const char* filename,
    Car_List** car_head,
    UniqueStrNode** mark_head,
    UniqueIntNode** year_head,
    UniqueStrNode** color_head,
    UniqueStrNode** fio_head,
    UniqueStrNode** addr_head,
    std::ofstream& log,
    int& correct_blocks,
    int& incorrect_blocks);

void write_output(const char* filename, Car_List* head, std::ofstream& log);

#endif