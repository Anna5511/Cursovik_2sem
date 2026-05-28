#include "find.h"

void find_cars(Car_List* head, const SearchCriteria& crit,
    std::ofstream& log, std::ofstream& out)
{
    int total_checked = 0;
    int found = 0;
    Car_List* cur = head;
    int index = 1;

    log << "==================" << std::endl;
    log << "КРИТЕРИИ ПОИСКА:" << std::endl;
    if (crit.use_num) {
        log << "  госномер = ";
        str_print(log, crit.num);
        log << std::endl;
    }
    if (crit.use_mark) {
        log << "  марка = ";
        str_print(log, crit.mark);
        log << std::endl;
    }
    if (crit.use_year)     log << "  год = " << crit.year << std::endl;
    if (crit.use_color) {
        log << "  цвет = ";
        str_print(log, crit.color);
        log << std::endl;
    }
    if (crit.use_fio) {
        log << "  ФИО = ";
        str_print(log, crit.fio);
        log << std::endl;
    }
    if (crit.use_address) {
        log << "  адрес = ";
        str_print(log, crit.address);
        log << std::endl;
    }
    log << "==================" << std::endl;

    while (cur) {
        ++total_checked;
        log << "=== Машина " << index << " ===" << std::endl;
        log << "  Данные: ";
        str_print(log, cur->car.num);                log << " ";
        str_print(log, cur->car.mark->value);        log << " ";
        log << cur->car.year->value;                 log << " ";
        str_print(log, cur->car.color->value);       log << " ";
        str_print(log, cur->car.fio->value);         log << " ";
        str_print(log, cur->car.address->value);
        log << std::endl;

        bool match = true;

        if (crit.use_num) {
            bool eq = str_equal(cur->car.num, crit.num);
            log << "  Проверка госномера: ";
            str_print(log, crit.num);
            log << (eq ? " == " : " != ");
            str_print(log, cur->car.num);
            log << (eq ? " +" : " -") << std::endl;
            if (!eq) match = false;
        }
        if (crit.use_mark && match) {
            bool eq = str_equal(cur->car.mark->value, crit.mark);
            log << "  Проверка марки: ";
            str_print(log, crit.mark);
            log << (eq ? " == " : " != ");
            str_print(log, cur->car.mark->value);
            log << (eq ? " +" : " -") << std::endl;
            if (!eq) match = false;
        }
        if (crit.use_year && match) {
            bool eq = (cur->car.year->value == crit.year);
            log << "  Проверка года: " << crit.year << " ";
            log << (eq ? "== " : "!= ");
            log << cur->car.year->value;
            log << (eq ? " +" : " -") << std::endl;
            if (!eq) match = false;
        }
        if (crit.use_color && match) {
            bool eq = str_equal(cur->car.color->value, crit.color);
            log << "  Проверка цвета: ";
            str_print(log, crit.color);
            log << (eq ? " == " : " != ");
            str_print(log, cur->car.color->value);
            log << (eq ? " +" : " -") << std::endl;
            if (!eq) match = false;
        }
        if (crit.use_fio && match) {
            bool eq = str_equal(cur->car.fio->value, crit.fio);
            log << "  Проверка ФИО: ";
            str_print(log, crit.fio);
            log << (eq ? " == " : " != ");
            str_print(log, cur->car.fio->value);
            log << (eq ? " +" : " -") << std::endl;
            if (!eq) match = false;
        }
        if (crit.use_address && match) {
            bool eq = str_equal(cur->car.address->value, crit.address);
            log << "  Проверка адреса: ";
            str_print(log, crit.address);
            log << (eq ? " == " : " != ");
            str_print(log, cur->car.address->value);
            log << (eq ? " +" : " -") << std::endl;
            if (!eq) match = false;
        }

        if (match) {
            log << "  >>> МАШИНА ПОДХОДИТ <<<" << std::endl;
            ++found;
            print_car(out, &cur->car);
            out << std::endl << std::endl;
        }
        else {
            log << "  >>> МАШИНА НЕ ПОДХОДИТ <<<" << std::endl;
        }

        cur = cur->next;
        ++index;
    }

    log << "ИТОГО: проверено " << total_checked << " машин, найдено " << found << std::endl;
    if (found == 0) {
        out << "Машин, соответствующих критериям поиска нет" << std::endl;
    }
}

void free_search_criteria(SearchCriteria& crit) {
    if (crit.use_num) str_free(crit.num);
    if (crit.use_mark) str_free(crit.mark);
    if (crit.use_color) str_free(crit.color);
    if (crit.use_fio) str_free(crit.fio);
    if (crit.use_address) str_free(crit.address);
}