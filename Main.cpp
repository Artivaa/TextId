#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm> // Для std::all_of


int main() {
    setlocale(LC_ALL, "Russian");

    std::string s;
    std::cout << "Введите строку: "; 
    std::getline(std::cin, s); 

    std::stringstream ss(s);
    std::string word;
    std::string result;

    while (ss >> word) {
        // Более идиоматичная проверка, что слово состоит только из цифр
        bool isDigitWord = std::all_of(word.begin(), word.end(), ::isdigit); // ::isdigit из <cctype>

        if (!isDigitWord) {
            std::string identifier;
            bool lastCharWasUnderscore = false; // Флаг для предотвращения дублирования '_'

            // Добавляем '_' в начале, если первый символ не подходит для идентификатора
            if (!std::isalpha(word[0]) && word[0] != '_') {
                identifier += '_';
                lastCharWasUnderscore = true; // После добавления '_' считаем, что последний символ был '_'
            }

            for (char c : word) {
                if (std::isalnum(c) || c == '_') {
                    identifier += c;
                    lastCharWasUnderscore = false; // Допустимый символ, значит, последний '_' был давно
                }
                else {
                    if (!lastCharWasUnderscore) { // Добавляем '_' только если предыдущий символ не был '_'
                        identifier += '_';
                        lastCharWasUnderscore = true;
                    }
                }
            }
            result += identifier + " ";
        }
    }

    if (!result.empty()) {
        result.back() = '.'; // Заменяем последний пробел на точку
    }
    else {
        result = "."; // Если result пустой, то просто "."
    }

    std::cout << "Результат: " << result << std::endl;

    return 0;
}