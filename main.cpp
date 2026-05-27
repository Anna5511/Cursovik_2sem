#include <iostream>
#include <fstream> // ИСПРАВЛЕНО: Добавлено для работы std::ofstream и устранения ошибок C2079/C2297
#include <clocale>
#include "CarParser.h"
#include "QueryParser.h"
#include "SearchEngine.h"
#include "Memory.h"

int main() {
    std::setlocale(LC_ALL, ".UTF-8");

    // ИСПРАВЛЕНО: Заменили \n на std::endl, чтобы консоль не склеивала твои строки в кашу
    std::cout << "==================================================" << std::endl;
    std::cout << "СПРАВКА: Допустимые ключи для поиска в query.txt:" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "Госномер:" << std::endl;
    std::cout << "Марка:" << std::endl;
    std::cout << "Год выпуска:" << std::endl;
    std::cout << "Цвет:" << std::endl;
    std::cout << "ФИО владельца:" << std::endl;
    std::cout << "Адрес регистрации :" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "num=A123BE" << std::endl;
    std::cout << "mark=Toyota" << std::endl;
    std::cout << "year=2015" << std::endl;
    std::cout << "color=красный" << std::endl;
    std::cout << "fio=Иванов Иван Иванович" << std::endl;
    std::cout << "adress=г.Москва" << std::endl;
    std::cout << "==================================================" << std::endl << std::endl;

    const char* inf = "C:\\Users\\Анечка\\Documents\\Cursovik\\input.txt";
    const char* quef = "C:\\Users\\Анечка\\Documents\\Cursovik\\query.txt";
    const char* outf = "C:\\Users\\Анечка\\Documents\\Cursovik\\output.txt";
    const char* prof = "C:\\Users\\Анечка\\Documents\\Cursovik\\protocol.txt";

    std::ofstream prot(prof);
    if (!prot.is_open()) {
        std::cout << "Не удалось открыть файл протокола: " << prof << std::endl;
        return 0;
    }

    prot << "Инициализация структур данных..." << std::endl;
    Car_List* db_head = nullptr;
    SearchCriteria current_request;

    prot << "Запуск парсинга базы данных из input.txt..." << std::endl;
    db_head = parse_input_file(inf);

    if (db_head == nullptr) {
        std::cout << "Файл поврежден/отсутствует." << std::endl;
        prot.close(); // Не забываем закрыть файл перед выходом
        return 0;
    }

    prot << "Запуск  файла запроса query.txt..." << std::endl;
    if (parse_query_file(quef, current_request)) {

        prot << "Поиск запущен." << std::endl;

        // Передаем строку пути prof, как и было заложено в твоем проекте
        find(db_head, current_request, prof, outf);

    }
    else {
        prot << "Запрос не может быть обработан (ошибка файла query.txt)." << std::endl;
    }

    prot << "Освобождение выделенной динамической памяти..." << std::endl;
    free_criteria(current_request);
    free_car_list(db_head);

    prot << "Программа успешно завершила работу." << std::endl;
    prot.close();
    return 0;
}