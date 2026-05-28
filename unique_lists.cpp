#include "unique_lists.h"

UniqueStrNode* find_str_node(UniqueStrNode* head, const str* val) {
    UniqueStrNode* cur = head;
    while (cur) {
        if (str_equal(cur->value, val)) return cur;
        cur = cur->next;
    }
    return nullptr;
}

UniqueStrNode* find_str_node_cstr(UniqueStrNode* head, const char* val) {
    UniqueStrNode* cur = head;
    while (cur) {
        if (str_equal_cstr(cur->value, val)) return cur;
        cur = cur->next;
    }
    return nullptr;
}

UniqueStrNode* add_str_node(UniqueStrNode** head, const char* val) {
    UniqueStrNode* exist = find_str_node_cstr(*head, val);
    if (exist) return exist;
    UniqueStrNode* node = new UniqueStrNode;
    node->value = str_create(val);
    node->next = *head;
    *head = node;
    return node;
}

UniqueStrNode* add_str_node_from_str(UniqueStrNode** head, str* val) {
    UniqueStrNode* exist = find_str_node(*head, val);
    if (exist) {
        str_free(val);
        return exist;
    }
    UniqueStrNode* node = new UniqueStrNode;
    node->value = val;
    node->next = *head;
    *head = node;
    return node;
}

void free_unique_str_list(UniqueStrNode* head) {
    while (head) {
        UniqueStrNode* next = head->next;
        str_free(head->value);
        delete head;
        head = next;
    }
}

UniqueIntNode* find_int_node(UniqueIntNode* head, int val) {
    UniqueIntNode* cur = head;
    while (cur) {
        if (cur->value == val) return cur;
        cur = cur->next;
    }
    return nullptr;
}

UniqueIntNode* add_int_node(UniqueIntNode** head, int val) {
    UniqueIntNode* exist = find_int_node(*head, val);
    if (exist) return exist;
    UniqueIntNode* node = new UniqueIntNode;
    node->value = val;
    node->next = *head;
    *head = node;
    return node;
}

void free_unique_int_list(UniqueIntNode* head) {
    while (head) {
        UniqueIntNode* next = head->next;
        delete head;
        head = next;
    }
}