#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    string s;
    cout << "¬ведите строку: ";
    getline(cin, s);

    stringstream ss(s);
    string word;
    string result;

    while (ss >> word)
    {
        bool isDigitWord = all_of(word.begin(), word.end(), ::isdigit);

        if (!isDigitWord)
        {
            string identifier;
            bool lastCharWasUnderscore = false;

            if (!isalpha(word[0]) && word[0] != '_')
            {
                identifier += '_';
                lastCharWasUnderscore = true;
            }

            for (char c : word)
            {
                if (isalnum(c) || c == '_')
                {
                    identifier += c;
                    lastCharWasUnderscore = false;
                }
                else
                {
                    if (!lastCharWasUnderscore)
                    {
                        identifier += '_';
                        lastCharWasUnderscore = true;
                    }
                }
            }
            result += identifier + " ";
        }
    }

    if (!result.empty())
    {
        result.back() = '.';
    }
    else
    {
        result = ".";
    }

    cout << "–езультат: " << result << endl;

    return 0;
}