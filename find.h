#ifndef FIND_H
#define FIND_H

#include "car.h"
#include <fstream>

struct SearchCriteria {
    bool use_num;
    str* num;
    bool use_mark;
    str* mark;
    bool use_year;
    int year;
    bool use_color;
    str* color;
    bool use_fio;
    str* fio;
    bool use_address;
    str* address;
};

void find_cars(Car_List* head, const SearchCriteria& crit,
    std::ofstream& log, std::ofstream& out);

void free_search_criteria(SearchCriteria& crit);

#endif