#include <iostream>
#include "CarParser.h"
#include "FileIO.h"
#include "Memory.h"

bool parse_single_car(std::ifstream& file, Car& car, int block_number, std::ofstream& prot) {
    init_car(car);
    bool is_empty = false;
    bool success = true;

    // Последовательно читаем параметры
    if (!read_data(file, car.num, is_empty) || is_empty) {
        free_car(car);
        return false; // Конец файла или пустая строка перед блоком
    }

    if (!read_data(file, car.mark, is_empty) || is_empty) success = false;
    if (!read_int(file, car.year, is_empty) || is_empty) success = false;
    if (!read_data(file, car.color, is_empty) || is_empty) success = false;
    if (!read_data(file, car.fio, is_empty) || is_empty) success = false;

    // adress - необязательное поле
    if (!read_data(file, car.adress, is_empty) || is_empty) {
        if (car.adress == nullptr) {
            car.adress = create_empty_str();
        }
    }

    if (!success) {
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
    return success;
}

Car_List* parse_input_file(const char* filename, std::ofstream& prot) {
    if (!check_file_exists(filename)) {
        prot << "Входной файл не найден: " << filename << std::endl;
        return nullptr;
    }

    std::ifstream file(filename);
    Car_List* head = nullptr;
    Car_List* tail = nullptr;

    int current_block = 0;

    while (!file.eof()) {
        if (file.peek() == EOF) break;

        current_block++;
        Car temporary_car;

        if (parse_single_car(file, temporary_car, current_block, prot)) {
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
    return head;
}