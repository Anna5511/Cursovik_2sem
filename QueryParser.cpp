#include "QueryParser.h"
#include "Memory.h"
#include "FileIO.h"

// Вспомогательная функция копирования си-строки в динамический str
void copy_c_str_to_str(str*& dest, const char* src) {
    free_str(dest);
    dest = nullptr;
    int idx = 0;
    while (src[idx] != '\0') {
        append_char(dest, src[idx]);
        idx++;
    }
}

// Кастомное сравнение си-строк без библиотек
bool match_c_strings(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return false;
        i++;
    }
    return s1[i] == s2[i];
}

bool parse_query_file(const char* filename, SearchCriteria& criteria) {
    if (!check_file_exists(filename)) {
        return false;
    }
    std::ifstream file(filename);
    init_criteria(criteria);

    char buf[300];
    if (!file.getline(buf, 300)) {
        file.close();
        return false;
    }
    file.close();

    int i = 0;
    while (buf[i] != '\0') {
        // Пропуск пробелов и разделителей
        while (buf[i] == ' ' || buf[i] == ',' || buf[i] == '\r' || buf[i] == '\n') {
            if (buf[i] == '\0') break;
            i++;
        }
        if (buf[i] == '\0') break;

        // Чтение ключа (например, mark, year)
        char key[50];
        int k = 0;
        while (buf[i] != '=' && buf[i] != '\0' && buf[i] != ' ') {
            if (k < 49) key[k++] = buf[i];
            i++;
        }
        key[k] = '\0';

        if (buf[i] == '=') i++;

        // Чтение значения (например, Toyota, 2015)
        char val[150];
        int v = 0;
        while (buf[i] != ',' && buf[i] != '\0') {
            if (v < 149) val[v++] = buf[i];
            i++;
        }
        while (v > 0 && val[v - 1] == ' ') v--;
        val[v] = '\0';

        if (match_c_strings(key, "num")) {
            copy_c_str_to_str(criteria.num, val);
        }
        else if (match_c_strings(key, "mark")) {
            copy_c_str_to_str(criteria.mark, val);
        }
        else if (match_c_strings(key, "year")) {
            int y = 0;
            for (int d = 0; val[d] != '\0'; d++) {
                if (val[d] >= '0' && val[d] <= '9') y = y * 10 + (val[d] - '0');
            }
            criteria.year = y;
        }
        else if (match_c_strings(key, "color")) {
            copy_c_str_to_str(criteria.color, val);
        }
        else if (match_c_strings(key, "fio")) {
            copy_c_str_to_str(criteria.fio, val);
        }
        else if (match_c_strings(key, "adress")) {
            copy_c_str_to_str(criteria.adress, val);
        }
    }
    return true;
}