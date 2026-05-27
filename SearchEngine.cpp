#include "SearchEngine.h"
#include "FileIO.h"

void write_protocol_header(std::ofstream& proto, const SearchCriteria& criteria) {
    proto << "КРИТЕРИИ ПОИСКА:\n";
    if (criteria.num) { proto << "госномер = "; write_str(proto, criteria.num); proto << "\n"; }
    if (criteria.mark) { proto << "марка = "; write_str(proto, criteria.mark); proto << "\n"; }
    if (criteria.year != -1) { proto << "год = " << criteria.year << "\n"; }
    if (criteria.color) { proto << "цвет = "; write_str(proto, criteria.color); proto << "\n"; }
    if (criteria.fio) { proto << "ФИО = "; write_str(proto, criteria.fio); proto << "\n"; }
    if (criteria.adress) { proto << "адрес = "; write_str(proto, criteria.adress); proto << "\n"; }
    proto << "----------------------------------------\n";
}

void write_car_to_output(std::ofstream& out, const Car& car) {
    write_str(out, car.num); out << "\n";
    write_str(out, car.mark); out << "\n";
    out << car.year << "\n";
    write_str(out, car.color); out << "\n";
    write_str(out, car.fio); out << "\n";
    write_str(out, car.adress); out << "\n";
    out << "\n"; // Разделитель между записями
}

void find(Car_List* head, const SearchCriteria& criteria, const char* protocol_file, const char* output_file) {
    std::ofstream proto(protocol_file, std::ios::app);
    std::ofstream out(output_file);

    if (!proto.is_open() || !out.is_open()) return;

    write_protocol_header(proto, criteria);

    Car_List* current = head;
    int checked_count = 0;
    int found_count = 0;
    int car_index = 1;

    while (current != nullptr) {
        checked_count++;

        proto << "= Машина " << car_index++ << " =\nДанные: ";
        write_str_inline(proto, current->C.num); proto << " ";
        write_str_inline(proto, current->C.mark); proto << " ";
        proto << current->C.year << " ";
        write_str_inline(proto, current->C.color); proto << "\n";

        bool match = true;

        if (criteria.num) {
            bool res = are_strings_equal(current->C.num, criteria.num);
            proto << "Проверка госномера: "; write_str_inline(proto, current->C.num);
            proto << (res ? " == " : " != "); write_str_inline(proto, criteria.num);
            proto << (res ? " +\n" : " -\n");
            if (!res) match = false;
        }
        if (criteria.mark) {
            bool res = are_strings_equal(current->C.mark, criteria.mark);
            proto << "Проверка марки: "; write_str_inline(proto, current->C.mark);
            proto << (res ? " == " : " != "); write_str_inline(proto, criteria.mark);
            proto << (res ? " +\n" : " -\n");
            if (!res) match = false;
        }
        if (criteria.year != -1) {
            bool res = (current->C.year == criteria.year);
            proto << "Проверка года: " << current->C.year << (res ? " == " : " != ") << criteria.year;
            proto << (res ? " +\n" : " -\n");
            if (!res) match = false;
        }
        if (criteria.color) {
            bool res = are_strings_equal(current->C.color, criteria.color);
            proto << "Проверка цвета: "; write_str_inline(proto, current->C.color);
            proto << (res ? " == " : " != "); write_str_inline(proto, criteria.color);
            proto << (res ? " +\n" : " -\n");
            if (!res) match = false;
        }
        if (criteria.fio) {
            bool res = are_strings_equal(current->C.fio, criteria.fio);
            proto << "Проверка ФИО: "; write_str_inline(proto, current->C.fio);
            proto << (res ? " == " : " != "); write_str_inline(proto, criteria.fio);
            proto << (res ? " +\n" : " -\n");
            if (!res) match = false;
        }
        if (criteria.adress) {
            bool res = are_strings_equal(current->C.adress, criteria.adress);
            proto << "Проверка адреса: "; write_str_inline(proto, current->C.adress);
            proto << (res ? " == " : " != "); write_str_inline(proto, criteria.adress);
            proto << (res ? " +\n" : " -\n");
            if (!res) match = false;
        }

        if (match) {
            proto << "МАШИНА ПОДХОДИТ <<<\n\n";
            found_count++;
            write_car_to_output(out, current->C);
        }
        else {
            proto << "МАШИНА НЕ ПОДХОДИТ <<<\n\n";
        }

        current = current->next;
    }

    proto << "ИТОГО: проверено " << checked_count << " машин, найдено " << found_count << "\n";
    proto.close();
    out.close();
}