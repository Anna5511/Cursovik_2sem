#ifndef CAR_H
#define CAR_H

#include "str.h"
#include "unique_lists.h"

struct Car {
    str* num;
    UniqueStrNode* mark;
    UniqueIntNode* year;
    UniqueStrNode* color;
    UniqueStrNode* fio;
    UniqueStrNode* address;
};

struct Car_List {
    Car car;
    Car_List* next;
};

void add_car(Car_List** head,
    str* num_str,
    UniqueStrNode* mark_node,
    UniqueIntNode* year_node,
    UniqueStrNode* color_node,
    UniqueStrNode* fio_node,
    UniqueStrNode* addr_node);

void free_car_list(Car_List* head);
void print_car(std::ostream& os, const Car* car);

#endif