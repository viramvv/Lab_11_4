#ifndef LAB_11_4_H
#define LAB_11_4_H

// Включаємо всі необхідні бібліотеки тут, щоб вони були доступні
// в .cpp файлах, де оголошені прототипи.
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip> // Необхідний для std::fixed та std::setprecision
#include <stdexcept>

using namespace std;

// Структура має бути оголошена тут
struct LineStats {
    vector<double> numbers;
    double arithmeticMean;
    double geometricMean;
};

// Прототипи функцій
void ShowMenu();
void CreateTXT(const char* fname);
void PrintTXT(const char* fname);
int ProcessAndWriteTXT(const char* fname, const char* gname);
LineStats CalculateMeans(const vector<double>& numbers);

#endif // LAB_11_4_H