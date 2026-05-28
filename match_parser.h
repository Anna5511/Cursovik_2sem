#ifndef MATCH_PARSER_H
#define MATCH_PARSER_H

#include "str.h"
#include "find.h"

str* read_match_file(const char* filename);
void parse_criteria_from_str(const str* s, SearchCriteria& crit);

#endif