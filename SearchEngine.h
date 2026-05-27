#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <fstream>
#include "Types.h"

void write_protocol_header(std::ofstream& proto, const SearchCriteria& criteria);
void write_car_to_output(std::ofstream& out, const Car& car);

// Сигнатура строго под оригинальный вызов из main.cpp
void find(Car_List* head, const SearchCriteria& criteria, const char* protocol_file, const char* output_file);

#endif