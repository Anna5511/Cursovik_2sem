#ifndef CAR_PARSER_H
#define CAR_PARSER_H

#include "Types.h"
#include <fstream>

// Чтение параметров одной машины
bool parse_single_car(std::ifstream& file, Car& car, int block_number, std::ofstream& prot);

// Парсинг всего входного файла
Car_List* parse_input_file(const char* filename, std::ofstream& prot);

#endif