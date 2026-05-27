#ifndef TYPES_H
#define TYPES_H

const int N = 50;

// Структура динамической блочной строки
struct str {
    char A[N + 1];    // Блок 50 символов + '\0'
    str* next;        // Следующий блок для длинных строк
};

// Данные об одной машине
struct Car {
    str* num;
    str* mark;
    int year;
    str* color;
    str* fio;
    str* adress;
};

// Однонаправленный динамический список машин
struct Car_List {
    Car C;
    Car_List* next;
};

// Параметры текущего поискового запроса
struct SearchCriteria {
    str* num;
    str* mark;
    int year;
    str* color;
    str* fio;
    str* adress;
};

#endif