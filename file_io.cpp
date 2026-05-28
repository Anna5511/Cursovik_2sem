#include "file_io.h"
#include "str_io.h"
#include <fstream>

int my_str_to_int(const str* s) {
    int res = 0;
    const str* cur = s;
    while (cur) {
        for (int i = 0; i < N && cur->A[i]; ++i) {
            char ch = cur->A[i];
            if (ch < '0' || ch > '9') return -1;
            res = res * 10 + (ch - '0');
        }
        cur = cur->next;
    }
    return res;
}

int read_input(const char* filename,
    Car_List** car_head,
    UniqueStrNode** mark_head,
    UniqueIntNode** year_head,
    UniqueStrNode** color_head,
    UniqueStrNode** fio_head,
    UniqueStrNode** addr_head,
    std::ofstream& log)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        log << "Ошибка открытия файла " << filename << std::endl;
        return 0;
    }

    int block_num = 1;
    int total_blocks = 0;
    const int REQUIRED_LINES = 6;

    while (!file.eof()) {
        str* line = read_line_from_stream(file);
        if (!line) break;
        bool is_empty = (line->A[0] == '\0' && line->next == nullptr);
        if (is_empty) {
            str_free(line);
            continue;
        }

        str* lines[REQUIRED_LINES];
        int line_count = 0;
        lines[line_count++] = line;

        while (line_count < REQUIRED_LINES) {
            str* next_line = read_line_from_stream(file);
            if (!next_line) break;
            bool empty = (next_line->A[0] == '\0' && next_line->next == nullptr);
            if (empty) {
                str_free(next_line);
                break;
            }
            lines[line_count++] = next_line;
        }

        if (line_count == REQUIRED_LINES) {
            str* extra = read_line_from_stream(file);
            if (extra) {
                bool empty_extra = (extra->A[0] == '\0' && extra->next == nullptr);
                if (!empty_extra) {
                    str_free(extra);
                    while (true) {
                        str* next_extra = read_line_from_stream(file);
                        if (!next_extra) break;
                        bool e = (next_extra->A[0] == '\0' && next_extra->next == nullptr);
                        if (e) {
                            str_free(next_extra);
                            break;
                        }
                        str_free(next_extra);
                    }
                    line_count = 999;
                }
                else {
                    str_free(extra);
                }
            }
        }

        log << "Информация о машине №" << block_num << ":" << std::endl;
        for (int i = 0; i < line_count && i < REQUIRED_LINES; ++i) {
            str_print(log, lines[i]);
            log << std::endl;
        }

        bool valid = (line_count == REQUIRED_LINES);
        int year_val = 0;
        if (valid) {
            year_val = my_str_to_int(lines[2]);
            if (year_val == -1) valid = false;
        }

        if (valid) {
            log << "---------------- Блок информации корректен" << std::endl;
            UniqueStrNode* mark_node = add_str_node_from_str(mark_head, lines[1]);
            UniqueIntNode* year_node = add_int_node(year_head, year_val);
            UniqueStrNode* color_node = add_str_node_from_str(color_head, lines[3]);
            UniqueStrNode* fio_node = add_str_node_from_str(fio_head, lines[4]);
            UniqueStrNode* addr_node = add_str_node_from_str(addr_head, lines[5]);
            add_car(car_head, lines[0], mark_node, year_node, color_node, fio_node, addr_node);
            str_free(lines[0]);
        }
        else {
            log << "---------------- Блок информации некорректен" << std::endl;
            for (int i = 0; i < line_count && i < REQUIRED_LINES; ++i)
                str_free(lines[i]);
        }

        ++block_num;
        ++total_blocks;
    }

    file.close();
    return total_blocks;
}

void write_output(const char* filename, Car_List* head, std::ofstream& log) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        log << "Ошибка открытия output.txt" << std::endl;
        return;
    }
    Car_List* cur = head;
    while (cur) {
        print_car(out, &cur->car);
        out << std::endl;
        if (cur->next) out << std::endl;
        cur = cur->next;
    }
    out.close();
}