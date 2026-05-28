#include "match_parser.h"
#include "str_io.h"
#include <fstream>

bool mp_cstr_eq_literal(const char* cstr, const char* lit) {
    int i = 0;
    while (cstr[i] && lit[i]) {
        if (cstr[i] != lit[i]) return false;
        ++i;
    }
    return (cstr[i] == '\0' && lit[i] == '\0');
}

void mp_skip_spaces(const str*& cur, int& idx) {
    while (cur) {
        while (idx < N && cur->A[idx] == ' ') ++idx;
        if (idx < N && cur->A[idx] != '\0') break;
        idx = 0;
        cur = cur->next;
    }
}

char mp_next_char(const str*& cur, int& idx) {
    if (!cur) return '\0';
    if (idx >= N || cur->A[idx] == '\0') {
        cur = cur->next;
        idx = 0;
        if (!cur) return '\0';
    }
    return cur->A[idx++];
}

void parse_criteria_from_str(const str* s, SearchCriteria& crit) {
    crit.use_num = crit.use_mark = crit.use_year = crit.use_color = crit.use_fio = crit.use_address = false;
    crit.num = crit.mark = crit.color = crit.fio = crit.address = nullptr;
    crit.year = 0;

    if (!s) return;

    const str* cur = s;
    int idx = 0;

    while (true) {
        mp_skip_spaces(cur, idx);
        if (!cur) break;

        char key[32];
        int key_pos = 0;
        char ch;
        while ((ch = mp_next_char(cur, idx)) != '\0' && ch != '=' && ch != ' ' && ch != ',') {
            if (key_pos < 31) key[key_pos++] = ch;
        }
        key[key_pos] = '\0';
        if (ch != '=') break;

        mp_skip_spaces(cur, idx);
        const str* val_start_cur = cur;
        int val_start_idx = idx;
        int val_len = 0;
        bool comma_found = false;
        const str* val_end_cur = cur;
        int val_end_idx = idx;
        while (true) {
            ch = mp_next_char(val_end_cur, val_end_idx);
            if (ch == '\0') break;
            if (ch == ',') {
                comma_found = true;
                break;
            }
            ++val_len;
        }

        str* value = nullptr;
        str* tail = nullptr;
        int global_pos = 0;
        const str* scan_cur = val_start_cur;
        int scan_idx = val_start_idx;
        while (global_pos < val_len) {
            char c = mp_next_char(scan_cur, scan_idx);
            if (c == '\0') break;
            if (!value) {
                value = new str;
                value->next = nullptr;
                value->A[0] = c;
                value->A[1] = '\0';
                tail = value;
            }
            else {
                int len = 0;
                while (tail->A[len]) ++len;
                if (len < N) {
                    tail->A[len] = c;
                    tail->A[len + 1] = '\0';
                }
                else {
                    str* new_block = new str;
                    new_block->next = nullptr;
                    new_block->A[0] = c;
                    new_block->A[1] = '\0';
                    tail->next = new_block;
                    tail = new_block;
                }
            }
            ++global_pos;
        }
        if (!value) {
            value = new str;
            value->A[0] = '\0';
            value->next = nullptr;
        }

        if (mp_cstr_eq_literal(key, "num")) {
            crit.use_num = true;
            crit.num = value;
        }
        else if (mp_cstr_eq_literal(key, "mark")) {
            crit.use_mark = true;
            crit.mark = value;
        }
        else if (mp_cstr_eq_literal(key, "year")) {
            crit.use_year = true;
            int year_val = 0;
            const str* ycur = value;
            while (ycur) {
                for (int i = 0; i < N && ycur->A[i]; ++i) {
                    char c = ycur->A[i];
                    if (c < '0' || c > '9') { year_val = -1; break; }
                    year_val = year_val * 10 + (c - '0');
                }
                ycur = ycur->next;
            }
            crit.year = year_val;
            str_free(value);
        }
        else if (mp_cstr_eq_literal(key, "color")) {
            crit.use_color = true;
            crit.color = value;
        }
        else if (mp_cstr_eq_literal(key, "fio")) {
            crit.use_fio = true;
            crit.fio = value;
        }
        else if (mp_cstr_eq_literal(key, "adress")) {
            crit.use_address = true;
            crit.address = value;
        }
        else {
            str_free(value);
        }

        if (!comma_found) break;
        cur = val_end_cur;
        idx = val_end_idx;
        mp_skip_spaces(cur, idx);
        if (!cur) break;
    }
}

str* read_match_file(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return nullptr;
    str* line = read_line_from_stream(file);
    file.close();
    return line;
}