#include <fstream>
#include <iostream>
#include <windows.h>
#include "car.h"
#include "unique_lists.h"
#include "file_io.h"
#include "find.h"
#include "match_parser.h"

int main() {
    const char* inf = "C:\\Users\\Анечка\\Documents\\Cursovik\\input.txt";
    const char* match = "C:\\Users\\Анечка\\Documents\\Cursovik\\match.txt";
    const char* outf = "C:\\Users\\Анечка\\Documents\\Cursovik\\output.txt";
    const char* logf = "C:\\Users\\Анечка\\Documents\\Cursovik\\protocol.txt";

    
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "==================================================" << std::endl;
    std::cout << "match.txt:" << std::endl;
    std::cout << "num= , mark= , year= , color= , fio= , adress=" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::ofstream log(logf, std::ios::trunc);
    if (!log.is_open()) {
        std::cerr << "Не удалось открыть protocol.txt" << std::endl;
        return 1;
    }

    Car_List* car_head = nullptr;
    UniqueStrNode* mark_head = nullptr;
    UniqueIntNode* year_head = nullptr;
    UniqueStrNode* color_head = nullptr;
    UniqueStrNode* fio_head = nullptr;
    UniqueStrNode* addr_head = nullptr;

    log << "СПИСОК МАШИН" << std::endl;
    log << "====================" << std::endl;

    int correct_blocks = 0;
    int incorrect_blocks = 0;
    int total_blocks = read_input(inf, &car_head,
        &mark_head, &year_head, &color_head,
        &fio_head, &addr_head, log,
        correct_blocks, incorrect_blocks);

    log << "====================" << std::endl;
    log << "СТАТИСТИКА ЧТЕНИЯ:" << std::endl;
    log << "  Всего блоков (машин): " << total_blocks << std::endl;
    log << "  Корректных блоков: " << correct_blocks << std::endl;
    log << "  Некорректных блоков: " << incorrect_blocks << std::endl;
    log << "====================" << std::endl;

    SearchCriteria crit = {};
    str* match_line = read_match_file(match);
    if (match_line) {
        parse_criteria_from_str(match_line, crit);
        str_free(match_line);
    }

    std::ofstream out(outf, std::ios::trunc);
    if (!out.is_open()) {
        log << "Ошибка открытия output.txt" << std::endl;
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