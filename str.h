#ifndef STR_H
#define STR_H

#include <iostream>

const int N = 15;   // размер одного блока

struct str {
    char A[N + 1];    // блок + '\0'
    str* next;      // следующий блок
};

str* str_create(const char* src);
void str_free(str* s);
bool str_equal(const str* s1, const str* s2);
bool str_equal_cstr(const str* s, const char* cstr);
void str_print(std::ostream& os, const str* s);
str* str_copy(const str* src);

#endif