#include "str_io.h"

str* read_line_from_stream(std::ifstream& file) {
    if (file.eof()) return nullptr;
    str* head = nullptr;
    str* tail = nullptr;
    char block[N + 1];
    int block_pos = 0;
    bool any_char = false;
    char ch;
    while (file.get(ch)) {
        any_char = true;
        if (ch == '\n') break;
        block[block_pos++] = ch;
        if (block_pos == N) {
            block[block_pos] = '\0';
            str* new_block = new str;
            for (int i = 0; i <= N; ++i) new_block->A[i] = block[i];
            new_block->next = nullptr;
            if (!head) head = new_block;
            else tail->next = new_block;
            tail = new_block;
            block_pos = 0;
        }
    }
    if (!any_char) return nullptr;
    if (block_pos > 0) {
        block[block_pos] = '\0';
        str* new_block = new str;
        for (int i = 0; i <= block_pos; ++i) new_block->A[i] = block[i];
        new_block->next = nullptr;
        if (!head) head = new_block;
        else tail->next = new_block;
    }
    else if (head == nullptr) {
        str* new_block = new str;
        new_block->A[0] = '\0';
        new_block->next = nullptr;
        head = new_block;
    }
    return head;
}