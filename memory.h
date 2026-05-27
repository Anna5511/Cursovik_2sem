#ifndef MEMORY_H
#define MEMORY_H

#include "Types.h"

// Создание пустого блока строки
str* create_empty_str();

// Добавление символа в конец структуры str
void append_char(str*& head, char ch);

// Инициализация полей Car значениями по умолчанию
void init_car(Car& car);

// Инициализация критериев поиска
void init_criteria(SearchCriteria& criteria);

// Освобождение памяти
void free_str(str* s);
void free_car(Car& car);
void free_car_list(Car_List*& head);
void free_criteria(SearchCriteria& criteria);

#endif