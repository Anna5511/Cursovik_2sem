#include "FileIO.h"
#include "Memory.h"

// Проверка возможности открыть файл на чтение
bool check_file_exists(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    file.close();
    return true;
}

// Посимвольное чтение строки до '\n' в динамическую структуру str
bool read_data(std::ifstream& file, str*& dynamic_str, bool& is_empty) {
    dynamic_str = nullptr;
    is_empty = true;
    char ch;
    bool has_chars = false;

    while (file.get(ch)) {
        has_chars = true;
        if (ch == '\n') break;   // Конец строки
        if (ch == '\r') continue;
        is_empty = false;
        append_char(dynamic_str, ch);
    }

    // Если строка прочитана, но осталась пустой — инициализируем пустой блок
    if (is_empty && dynamic_str == nullptr) {
        dynamic_str = create_empty_str();
    }
    return has_chars; // Возвращает false, если достигнут EOF без чтения символов
}

// Чтение текстовой строки и её конвертация в целое число (int)
bool read_int(std::ifstream& file, int& value, bool& is_empty) {
    str* temp_str = nullptr;
    bool result = read_data(file, temp_str, is_empty);
    if (!result || is_empty) {
        free_str(temp_str);
        return false;
    }

    value = 0;
    str* current = temp_str;
    bool has_digits = false;

    // Перевод символов цифр в число
    while (current != nullptr) {
        int i = 0;
        while (current->A[i] != '\0') {
            if (current->A[i] >= '0' && current->A[i] <= '9') {
                value = value * 10 + (current->A[i] - '0');
                has_digits = true;
            }
            i++;
        }
        current = current->next;
    }
    free_str(temp_str); // Очищаем временную строку
    return has_digits;
}

// Посимвольное сравнение двух блочных строк любой длины
bool are_strings_equal(const str* s1, const str* s2) {
    if (s1 == nullptr && s2 == nullptr) return true;
    if (s1 == nullptr || s2 == nullptr) return false;

    const str* p1 = s1;
    const str* p2 = s2;
    int i = 0, j = 0;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->A[i] != p2->A[j]) return false; // Символы не совпали
        if (p1->A[i] == '\0') return true;      // Обе строки успешно закончились
        i++; j++;

        // Переход на следующий блок для первой строки
        if (p1->A[i] == '\0' && p1->next != nullptr) {
            p1 = p1->next;
            i = 0;
        }
        // Переход на следующий блок для второй строки
        if (p2->A[j] == '\0' && p2->next != nullptr) {
            p2 = p2->next;
            j = 0;
        }
    }

    char c1 = (p1 != nullptr) ? p1->A[i] : '\0';
    char c2 = (p2 != nullptr) ? p2->A[j] : '\0';
    return c1 == c2;
}

// Обычный вывод блочной строки в поток (с сохранением форматирования)
void write_str(std::ostream& os, const str* s) {
    const str* current = s;
    while (current != nullptr) {
        os << current->A;
        current = current->next;
    }
}

// Вывод строки в одну линию (без символов переноса строки)
void write_str_inline(std::ostream& os, const str* s) {
    const str* current = s;
    while (current != nullptr) {
        int i = 0;
        while (current->A[i] != '\0') {
            if (current->A[i] != '\r' && current->A[i] != '\n') {
                os << current->A[i];
            }
            i++;
        }
        current = current->next;
    }
}