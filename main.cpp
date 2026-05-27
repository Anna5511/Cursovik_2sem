#include <iostream>
#include "CarParser.h"
#include "QueryParser.h"
#include "SearchEngine.h"
#include "Memory.h"

int main() {
    // 1. Вывод справочного шаблона для пользователя в консоль
    std::cout << "==================================================\n";
    std::cout << "СПРАВКА: Допустимые ключи для поиска в query.txt:\n";
    std::cout << "Госномер:           num=A123BE\n";
    std::cout << "Марка:              mark=Toyota\n";
    std::cout << "Год выпуска:        year=2015\n";
    std::cout << "Цвет:               color=красный\n";
    std::cout << "ФИО владельца:      fio=Иванов Иван Иванович\n";
    std::cout << "Адрес регистрации:  adress=г.Москва\n";
    std::cout << "==================================================\n\n";

    Car_List* db_head = nullptr;
    SearchCriteria current_request;
    db_head = parse_input_file("input.txt");

    if (db_head == nullptr) {
        std::cout << "Ошибка файла" << std::endl;
        return 0;
    }

    if (parse_query_file("query.txt", current_request)) {

        find(db_head, current_request, "protocol.txt", "output.txt");

    }
    else {
        std::cout << "Запрос не может быть обработан (ошибка файла query.txt)." << std::endl;
    }

    free_criteria(current_request);
    free_car_list(db_head);

    std::cout << "Программа завершила работу." << std::endl;
    return 0;
}