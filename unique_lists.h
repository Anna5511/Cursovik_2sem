#ifndef UNIQUE_LISTS_H
#define UNIQUE_LISTS_H

#include "str.h"

struct UniqueStrNode {
    str* value;
    UniqueStrNode* next;
};

struct UniqueIntNode {
    int value;
    UniqueIntNode* next;
};

UniqueStrNode* find_str_node(UniqueStrNode* head, const str* val);
UniqueStrNode* find_str_node_cstr(UniqueStrNode* head, const char* val);
UniqueStrNode* add_str_node(UniqueStrNode** head, const char* val);
UniqueStrNode* add_str_node_from_str(UniqueStrNode** head, str* val);
void free_unique_str_list(UniqueStrNode* head);

UniqueIntNode* find_int_node(UniqueIntNode* head, int val);
UniqueIntNode* add_int_node(UniqueIntNode** head, int val);
void free_unique_int_list(UniqueIntNode* head);

#endif