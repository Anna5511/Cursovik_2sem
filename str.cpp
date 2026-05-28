#include "str.h"

int my_cstr_len(const char* s) {
    int len = 0;
    while (s[len]) ++len;
    return len;
}

void my_cstr_copy(char* dest, const char* src) {
    while ((*dest++ = *src++));
}

str* str_create(const char* src) {
    if (!src) return nullptr;
    int len = my_cstr_len(src);
    str* head = nullptr;
    str* tail = nullptr;
    int pos = 0;
    while (pos < len) {
        str* block = new str;
        block->next = nullptr;
        int i = 0;
        while (i < N && pos < len) {
            block->A[i] = src[pos];
            ++i; ++pos;
        }
        block->A[i] = '\0';
        if (!head) {
            head = block;
            tail = block;
        }
        else {
            tail->next = block;
            tail = block;
        }
    }
    return head;
}

void str_free(str* s) {
    while (s) {
        str* next = s->next;
        delete s;
        s = next;
    }
}

bool str_equal(const str* s1, const str* s2) {
    while (s1 && s2) {
        int i = 0;
        while (i <= N && s1->A[i] && s2->A[i]) {
            if (s1->A[i] != s2->A[i]) return false;
            ++i;
        }
        if (s1->A[i] != s2->A[i]) return false;
        s1 = s1->next;
        s2 = s2->next;
    }
    return (s1 == nullptr && s2 == nullptr);
}

bool str_equal_cstr(const str* s, const char* cstr) {
    if (!s && (!cstr || !*cstr)) return true;
    if (!s || !cstr) return false;
    int pos = 0;
    const str* cur = s;
    while (cur) {
        for (int i = 0; i < N && cur->A[i]; ++i) {
            if (cstr[pos] == '\0') return false;
            if (cur->A[i] != cstr[pos]) return false;
            ++pos;
        }
        cur = cur->next;
    }
    return cstr[pos] == '\0';
}

void str_print(std::ostream& os, const str* s) {
    while (s) {
        os << s->A;
        s = s->next;
    }
}

str* str_copy(const str* src) {
    if (!src) return nullptr;
    str* new_head = nullptr;
    str* new_tail = nullptr;
    const str* cur = src;
    while (cur) {
        str* block = new str;
        block->next = nullptr;
        int i = 0;
        while (i < N && cur->A[i]) {
            block->A[i] = cur->A[i];
            ++i;
        }
        block->A[i] = '\0';
        if (!new_head) {
            new_head = block;
            new_tail = block;
        }
        else {
            new_tail->next = block;
            new_tail = block;
        }
        cur = cur->next;
    }
    return new_head;
}