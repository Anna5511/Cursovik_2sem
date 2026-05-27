#ifndef FILE_IO_H
#define FILE_IO_H

#include <fstream>
#include "Types.h"

// Проверка возможности открытия файла на чтение
bool check_file_exists(const char* filename);

// Функции чтения
bool read_data(std::ifstream& file, str*& dynamic_str, bool& is_empty);
bool read_int(std::ifstream& file, int& value, bool& is_empty);

// Инструменты посимвольного сравнения и печати строк
bool are_strings_equal(const str* s1, const str* s2);
void write_str(std::ostream& os, const str* s);
void write_str_inline(std::ostream& os, const str* s);

#endif