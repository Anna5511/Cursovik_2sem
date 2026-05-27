#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include "Types.h"

// Разбор строки запроса из файла
bool parse_query_file(const char* filename, SearchCriteria& criteria);

#endif