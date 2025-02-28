#include <iostream>
#include <Windows.h>

using namespace std;

const int MAX_LEN = 1024;

// Функция processWord: обрабатывает слово, преобразует в идентификатор, добавляет в результат.
void processWord(char* word, char* ident, char* result, int& res_pos)
{
    bool number_word = true;
    bool check_complete = false;

    // Проверяем, является ли слово числом (состоит только из цифр).
    for (int j = 0; word[j] && !check_complete; ++j)
    {
        if (word[j] < '0' || word[j] > '9')
        {
            number_word = false;
            check_complete = true;
        }
    }

    if (!number_word)
    {
        int ident_pos = 0;
        bool last_underscore = false;

        // Если первый символ не буква и не подчеркивание, добавляем подчеркивание в начало идентификатора.
        if ((word[0] < 'A' || (word[0] > 'Z' && word[0] < 'a') || word[0] > 'z') && word[0] != '_')
        {
            if (ident_pos < MAX_LEN - 1) ident[ident_pos++] = '_';
            last_underscore = true;
        }

        for (int j = 0; word[j]; ++j)
        {
            bool valid = (word[j] >= 'A' && word[j] <= 'Z') ||
                (word[j] >= 'a' && word[j] <= 'z') ||
                (word[j] >= '0' && word[j] <= '9') ||
                word[j] == '_';

            if (valid)
            {
                if (ident_pos < MAX_LEN - 1)
                {
                    ident[ident_pos++] = word[j];
                    last_underscore = (word[j] == '_');
                }
            }
            // Заменяем недопустимые символы на подчеркивание, избегая повторных подчеркиваний.
            else if (!last_underscore)
            {
                if (ident_pos < MAX_LEN - 1)
                {
                    ident[ident_pos++] = '_';
                    last_underscore = true;
                }
            }
        }
        ident[ident_pos] = '\0';

        for (int j = 0; ident[j] && res_pos < MAX_LEN - 1; ++j)
        {
            result[res_pos++] = ident[j];
        }
        if (res_pos < MAX_LEN - 1) result[res_pos++] = ' ';
    }
}


int main()
{
    SetConsoleCP(1251);       // Устанавливаем кодовую страницу ввода для корректного отображения кириллицы.
    SetConsoleOutputCP(1251);  // Устанавливаем кодовую страницу вывода для корректного отображения кириллицы.

    char input[MAX_LEN] = { 0 };
    cout << "Введите строку: ";
    cin.getline(input, MAX_LEN);

    char result[MAX_LEN] = { 0 };
    char word[MAX_LEN] = { 0 };
    char ident[MAX_LEN] = { 0 };
    int res_pos = 0;
    int word_pos = 0;

    for (int i = 0; input[i]; ++i)
    {
        if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
        {
            if (word_pos < MAX_LEN - 1)
            {
                word[word_pos++] = input[i];
            }
        }
        else
        {
            // Обрабатываем слово, когда встречаем разделитель.
            if (word_pos > 0) // Проверяем, что слово не пустое.
            {
                word[word_pos] = '\0';
                processWord(word, ident, result, res_pos);
                word_pos = 0;
            }
        }
    }

    // Обрабатываем последнее слово после окончания цикла (если строка не заканчивается разделителем).
    if (word_pos > 0)
    {
        word[word_pos] = '\0';
        processWord(word, ident, result, res_pos);
    }


    if (res_pos > 0)
    {
        result[res_pos - 1] = '.'; // Заменяем последний пробел на точку.
    }
    else
    {
        result[0] = '.';        // Если результат пустой, ставим точку.
        result[1] = '\0';
    }

    cout << "Результат: " << result << endl;

    return 0;
}