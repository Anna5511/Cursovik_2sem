#include <iostream>
#include <fstream>
#include <clocale>
#include "CarParser.h"
#include "QueryParser.h"
#include "SearchEngine.h"
#include "Memory.h"

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251 > nul");
    

    // ИСПРАВЛЕНО: Заменили \n на std::endl, чтобы Windows не склеивала твою справку в одну строку
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
    std::cout << "num= , mark= , year= , color= , fio= , adress=" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "Пример данных:" << std::endl;
    std::cout << std::endl;
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
        prot.close();
        return 0;
    }

    prot << "Запуск  файла запроса query.txt..." << std::endl;
    if (parse_query_file(quef, current_request)) {

        prot << "Поиск запущен." << std::endl;

        // Закрываем дескриптор, чтобы функция find могла открыть этот же файл внутри себя
        prot.close();

        // Передаем строки путей, как изначально требовала твоя программа
        find(db_head, current_request, prof, outf);

    }
    else {
        prot << "Запрос не может быть обработан (ошибка файла query.txt)." << std::endl;
        prot.close();
    }

    // Записываем финальные логи в конец протокола
    std::ofstream prot_end(prof, std::ios::app);
    if (prot_end.is_open()) {
        prot_end << "Освобождение выделенной динамической памяти..." << std::endl;
        prot_end << "Программа успешно завершила работу." << std::endl;
        prot_end.close();
    }

    free_criteria(current_request);
    free_car_list(db_head);

    return 0;
}