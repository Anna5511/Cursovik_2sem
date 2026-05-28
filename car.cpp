#include "car.h"

void add_car(Car_List** head,
    str* num_str,
    UniqueStrNode* mark_node,
    UniqueIntNode* year_node,
    UniqueStrNode* color_node,
    UniqueStrNode* fio_node,
    UniqueStrNode* addr_node)
{
    Car_List* new_node = new Car_List;
    new_node->car.num = str_copy(num_str);
    new_node->car.mark = mark_node;
    new_node->car.year = year_node;
    new_node->car.color = color_node;
    new_node->car.fio = fio_node;
    new_node->car.address = addr_node;
    new_node->next = nullptr;

    if (*head == nullptr) {
        *head = new_node;
    }
    else {
        Car_List* cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = new_node;
    }
}

void free_car_list(Car_List* head) {
    while (head) {
        Car_List* next = head->next;
        str_free(head->car.num);
        delete head;
        head = next;
    }
}

void print_car(std::ostream& os, const Car* car) {
    str_print(os, car->num);          os << std::endl;
    str_print(os, car->mark->value);  os << std::endl;
    os << car->year->value;           os << std::endl;
    str_print(os, car->color->value); os << std::endl;
    str_print(os, car->fio->value);   os << std::endl;
    str_print(os, car->address->value);
}