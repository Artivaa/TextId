#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm> // ��� std::all_of


int main() {
    setlocale(LC_ALL, "Russian");

    std::string s;
    std::cout << "������� ������: "; 
    std::getline(std::cin, s); 

    std::stringstream ss(s);
    std::string word;
    std::string result;

    while (ss >> word) {
        // ����� ������������ ��������, ��� ����� ������� ������ �� ����
        bool isDigitWord = std::all_of(word.begin(), word.end(), ::isdigit); // ::isdigit �� <cctype>

        if (!isDigitWord) {
            std::string identifier;
            bool lastCharWasUnderscore = false; // ���� ��� �������������� ������������ '_'

            // ��������� '_' � ������, ���� ������ ������ �� �������� ��� ��������������
            if (!std::isalpha(word[0]) && word[0] != '_') {
                identifier += '_';
                lastCharWasUnderscore = true; // ����� ���������� '_' �������, ��� ��������� ������ ��� '_'
            }

            for (char c : word) {
                if (std::isalnum(c) || c == '_') {
                    identifier += c;
                    lastCharWasUnderscore = false; // ���������� ������, ������, ��������� '_' ��� �����
                }
                else {
                    if (!lastCharWasUnderscore) { // ��������� '_' ������ ���� ���������� ������ �� ��� '_'
                        identifier += '_';
                        lastCharWasUnderscore = true;
                    }
                }
            }
            result += identifier + " ";
        }
    }

    if (!result.empty()) {
        result.back() = '.'; // �������� ��������� ������ �� �����
    }
    else {
        result = "."; // ���� result ������, �� ������ "."
    }

    std::cout << "���������: " << result << std::endl;

    return 0;
}