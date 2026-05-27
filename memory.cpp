#include "Memory.h"

// Создание пустого блока для кастомной динамической строки
str* create_empty_str() {
    str* new_node = new str;
    new_node->A[0] = '\0'; // Зануляем строку в блоке
    new_node->next = nullptr;
    return new_node;
}

// Добавление одного символа в конец блочной динамической строки
void append_char(str*& head, char ch) {
    if (head == nullptr) {
        head = create_empty_str();
    }

    // Идем до последнего (активного) блока цепочки
    str* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    // Считаем количество символов в текущем блоке
    int len = 0;
    while (current->A[len] != '\0' && len < N) {
        len++;
    }

    // Если лимит блока исчерпан (49 символов), создаем следующий блок
    if (len >= N - 1) {
        current->next = create_empty_str();
        current = current->next;
        len = 0;
    }

    // Записываем символ и закрываем строку нулем
    current->A[len] = ch;
    current->A[len + 1] = '\0';
}

// Инициализация полей машины дефолтными значениями (nullptr и 0)
void init_car(Car& car) {
    car.num = nullptr;
    car.mark = nullptr;
    car.year = 0;
    car.color = nullptr;
    car.fio = nullptr;
    car.adress = nullptr;
}

// Инициализация критериев поиска (year = -1 означает игнорирование поля)
void init_criteria(SearchCriteria& criteria) {
    criteria.num = nullptr;
    criteria.mark = nullptr;
    criteria.year = -1;
    criteria.color = nullptr;
    criteria.fio = nullptr;
    criteria.adress = nullptr;
}

// Последовательное удаление всех блоков одной строки str
void free_str(str* s) {
    while (s != nullptr) {
        str* temp = s->next; // Сохраняем адрес следующего блока
        delete s;            // Удаляем текущий блок
        s = temp;            // Сдвигаемся дальше
    }
}

// Каскадное удаление всех динамических строк внутри структуры Car
void free_car(Car& car) {
    free_str(car.num);    car.num = nullptr;
    free_str(car.mark);   car.mark = nullptr;
    free_str(car.color);  car.color = nullptr;
    free_str(car.fio);    car.fio = nullptr;
    free_str(car.adress); car.adress = nullptr;
    car.year = 0;
}

// Полная очистка динамического списка Car_List (данные + узлы списка)
void free_car_list(Car_List*& head) {
    Car_List* current = head;
    while (current != nullptr) {
        Car_List* next_node = current->next; // Сохраняем адрес следующего узла
        free_car(current->C);               // Очищаем строки внутри машины
        delete current;                     // Удаляем сам узел списка
        current = next_node;                // Переходим к следующему
    }
    head = nullptr; // Зануляем голову списка
}

// Очистка памяти динамических строк в структуре параметров поиска
void free_criteria(SearchCriteria& criteria) {
    free_str(criteria.num);    criteria.num = nullptr;
    free_str(criteria.mark);   criteria.mark = nullptr;
    free_str(criteria.color);  criteria.color = nullptr;
    free_str(criteria.fio);    criteria.fio = nullptr;
    free_str(criteria.adress); criteria.adress = nullptr;
    criteria.year = -1;
}