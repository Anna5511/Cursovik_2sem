#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Types.h"

// Главная функция поиска
void find(Car_List* head, const SearchCriteria& criteria, const char* protocol_file, const char* output_file);

#endif