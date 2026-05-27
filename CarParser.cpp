#include <iostream>
#include "CarParser.h"
#include "FileIO.h"
#include "Memory.h"

bool parse_single_car(std::ifstream& file, Car& car, int block_number) {
    init_car(car);
    bool is_empty = false;
    bool success = true;

    std::ofstream prot("C:\\Users\\Анечка\\Documents\\Cursovik\\protocol.txt");

    // Последовательно читаем параметры
    if (!read_data(file, car.num, is_empty) || is_empty) {
        free_car(car);
        return false; // Конец файла или пустая строка перед блоком
    }
    if (success && (!read_data(file, car.mark, is_empty) || is_empty)) success = false;
    if (success && (!read_int(file, car.year, is_empty) || is_empty)) success = false;
    if (success && (!read_data(file, car.color, is_empty) || is_empty)) success = false;
    if (success && (!read_data(file, car.fio, is_empty) || is_empty)) success = false;
    if (success && (!read_data(file, car.adress, is_empty) || is_empty)) success = false;

    if (!success) {
        //Вывод номера пропущенного блока
        prot << "Неправильный формат ввода информации о машине. Блок "
            << block_number << " пропущен." << std::endl;

        free_car(car);

        // Пропускаем остатки битого блока до следующей пустой строки
        str* trash = nullptr;
        while (read_data(file, trash, is_empty) && !is_empty) {
            free_str(trash);
            trash = nullptr;
        }
        free_str(trash);
    }
    prot.close();
    return success;
}

Car_List* parse_input_file(const char* filename) {

    std::ofstream prot("C:\\Users\\Анечка\\Documents\\Cursovik\\protocol.txt");

    if (!check_file_exists(filename)) {
        prot << "Входной файл не найден: " << filename << std::endl;
        prot.close();
        return nullptr;
    }
    std::ifstream file(filename);
    Car_List* head = nullptr;
    Car_List* tail = nullptr;

    int current_block = 0; // Счетчик абсолютно всех блоков в файле

    while (!file.eof()) {
        if (file.peek() == EOF) break;

        current_block++; // Входим в чтение нового блока данных
        Car temporary_car;

        if (parse_single_car(file, temporary_car, current_block)) {
            Car_List* new_node = new Car_List;
            new_node->C = temporary_car;
            new_node->next = nullptr;

            if (head == nullptr) {
                head = new_node;
                tail = new_node;
            }
            else {
                tail->next = new_node;
                tail = new_node;
            }
        }
    }
    file.close();
    prot.close();
    
    return head;
}