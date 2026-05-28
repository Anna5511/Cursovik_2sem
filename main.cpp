#include <fstream>
#include <iostream>
#include "car.h"
#include "unique_lists.h"
#include "file_io.h"
#include "find.h"
#include "match_parser.h"

int main() {
    std::ofstream log("protocol.txt", std::ios::trunc);
    if (!log.is_open()) {
        std::cerr << "Íå óäàëîñü îòêðûòü protocol.txt" << std::endl;
        return 1;
    }

    Car_List* car_head = nullptr;
    UniqueStrNode* mark_head = nullptr;
    UniqueIntNode* year_head = nullptr;
    UniqueStrNode* color_head = nullptr;
    UniqueStrNode* fio_head = nullptr;
    UniqueStrNode* addr_head = nullptr;

    log << "ÑÏÈÑÎÊ ÌÀØÈÍ" << std::endl;
    log << "====================" << std::endl;
    read_input("input.txt", &car_head,
        &mark_head, &year_head, &color_head,
        &fio_head, &addr_head, log);
    log << "====================" << std::endl;

    SearchCriteria crit = {};
    str* match_line = read_match_file("match.txt");
    if (match_line) {
        parse_criteria_from_str(match_line, crit);
        str_free(match_line);
    }

    std::ofstream out("output.txt", std::ios::trunc);
    if (!out.is_open()) {
        log << "Îøèáêà îòêðûòèÿ output.txt" << std::endl;
        return 1;
    }

    find_cars(car_head, crit, log, out);

    out.close();
    log.close();

    free_car_list(car_head);
    free_unique_str_list(mark_head);
    free_unique_int_list(year_head);
    free_unique_str_list(color_head);
    free_unique_str_list(fio_head);
    free_unique_str_list(addr_head);
    free_search_criteria(crit);

    return 0;
}