#include <iostream>
#include <Windows.h>

using namespace std;

const int MAX_LEN = 1024;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char input[MAX_LEN] = { 0 };
    cout << "Введите строку: ";
    cin.getline(input, MAX_LEN);

    char result[MAX_LEN] = { 0 };
    char word[MAX_LEN] = { 0 };
    char ident[MAX_LEN] = { 0 };
    int res_pos = 0;
    int word_pos = 0;
    bool in_word = false;

    for (int i = 0; input[i]; ++i)
    {
        if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
        {
            if (!in_word)
            {
                word_pos = 0;
                in_word = true;
            }
            if (word_pos < MAX_LEN - 1) word[word_pos++] = input[i];
        }
        else
        {
            if (in_word)
            {
                word[word_pos] = '\0';
                bool number_word = true;
                bool check_complete = false;

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

                word[0] = '\0';
                in_word = false;
            }
        }
    }

    if (in_word)
    {
        word[word_pos] = '\0';
        bool number_word = true;
        bool check_complete = false;

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

    if (res_pos > 0)
    {
        result[res_pos - 1] = '.';
    }
    else
    {
        result[0] = '.';
        result[1] = '\0';
    }

    cout << "Результат: " << result << endl;

    return 0;
}