#include "FileIO.h"
#include "Memory.h"

bool check_file_exists(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    file.close();
    return true;
}

bool read_data(std::ifstream& file, str*& dynamic_str, bool& is_empty) {
    dynamic_str = nullptr;
    is_empty = true;
    char ch;
    bool has_chars = false;

    while (file.get(ch)) {
        has_chars = true;
        if (ch == '\n') break;
        if (ch == '\r') continue;
        is_empty = false;
        append_char(dynamic_str, ch);
    }

    if (is_empty && dynamic_str == nullptr) {
        dynamic_str = create_empty_str();
    }
    return has_chars;
}

bool read_int(std::ifstream& file, int& value, bool& is_empty) {
    str* temp_str = nullptr;
    bool result = read_data(file, temp_str, is_empty);
    if (!result || is_empty) {
        free_str(temp_str);
        return false;
    }

    value = 0;
    str* current = temp_str;
    bool has_digits = false;
    bool is_negative = false;

    // Сначала ищем знак минуса
    str* check_current = temp_str;
    while (check_current != nullptr) {
        int i = 0;
        while (check_current->A[i] != '\0') {
            if (check_current->A[i] == '-') {
                is_negative = true;
            }
            i++;
        }
        check_current = check_current->next;
    }

    // Собираем цифры
    current = temp_str;
    while (current != nullptr) {
        int i = 0;
        while (current->A[i] != '\0') {
            char ch = current->A[i];
            if (ch >= '0' && ch <= '9') {
                value = value * 10 + (ch - '0');
                has_digits = true;
            }
            i++;
        }
        current = current->next;
    }

    free_str(temp_str);

    if (!has_digits) {
        return false;
    }

    if (is_negative) {
        value = -value;
    }

    return true;
}

bool are_strings_equal(const str* s1, const str* s2) {
    if (s1 == nullptr && s2 == nullptr) return true;
    if (s1 == nullptr || s2 == nullptr) return false;

    const str* p1 = s1;
    const str* p2 = s2;
    int i = 0, j = 0;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->A[i] != p2->A[j]) return false;
        if (p1->A[i] == '\0') return true;
        i++; j++;

        if (p1->A[i] == '\0' && p1->next != nullptr) {
            p1 = p1->next;
            i = 0;
        }
        if (p2->A[j] == '\0' && p2->next != nullptr) {
            p2 = p2->next;
            j = 0;
        }
    }

    char c1 = (p1 != nullptr) ? p1->A[i] : '\0';
    char c2 = (p2 != nullptr) ? p2->A[j] : '\0';
    return c1 == c2;
}

void write_str(std::ostream& os, const str* s) {
    const str* current = s;
    while (current != nullptr) {
        os << current->A;
        current = current->next;
    }
}

void write_str_inline(std::ostream& os, const str* s) {
    const str* current = s;
    while (current != nullptr) {
        int i = 0;
        while (current->A[i] != '\0') {
            if (current->A[i] != '\r' && current->A[i] != '\n') {
                os << current->A[i];
            }
            i++;
        }
        current = current->next;
    }
}