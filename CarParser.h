#ifndef CAR_PARSER_H
#define CAR_PARSER_H

#include "Types.h"

// Чтение параметров одной машины (теперь передаем номер блока для логирования ошибок)
bool parse_single_car(std::ifstream& file, Car& car, int block_number);

// Парсинг всего входного файла
Car_List* parse_input_file(const char* filename);

#endif