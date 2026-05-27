#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <fstream>
#include "Types.h"

void write_protocol_header(std::ofstream& proto, const SearchCriteria& criteria);
void write_car_to_output(std::ofstream& out, const Car& car);

// Изменено: третий параметр принимает ссылку на поток протокола (std::ofstream& proto)
void find(Car_List* head, const SearchCriteria& criteria, std::ofstream& proto, const char* output_file);

#endif