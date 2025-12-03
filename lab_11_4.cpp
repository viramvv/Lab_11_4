#include "lab_11_4.h"

// Функція для відображення меню
void ShowMenu() {
    cout << "1. Створити/перезаписати вхідний файл" << endl;
    cout << "2. Вивести вміст вхідного файлу" << endl;
    cout << "3. Обробка файлу та запис результатів у новий файл" << endl;
    cout << "0. Вихід" << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "Ваш вибір: ";
}

// 1. Функція, що створює текстовий файл
void CreateTXT(const char* fname) {
    ofstream fout(fname, ios::trunc);
    if (!fout.is_open()) {
        cout << "Error: Could not open file for writing: " << fname << endl;
        return;
    }

    char ch;
    string s;
    cout << "\n--- Створення файлу: " << fname << " ---" << endl;
    do {
        cout << "Enter line (with numbers and symbols):" << endl;
        // cin.get() або cin.sync() може знадобитися на деяких компіляторах, але
        // getline(cin, s) після cin.ignore() у main.cpp має бути достатнім.
        getline(cin, s);

        fout << s << endl; // Записуємо рядок у файл

        cout << "Continue? (y/n): ";
        cin >> ch;
        // Очищаємо буфер після cin >> ch
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "File " << fname << " created successfully." << endl;
}

// 2. Функція, що виводить файл на екран
void PrintTXT(const char* fname) {
    ifstream fin(fname);
    if (!fin.is_open()) {
        cout << "\nError: Could not open file for reading: " << fname << endl;
        return;
    }

    string s;
    cout << "\nContent of file " << fname << ":" << endl;
    cout << "--------------------------------------------------" << endl;
    while (getline(fin, s)) {
        cout << s << endl;
    }
    cout << "--------------------------------------------------" << endl;

    fin.close();
}

// 4. Функція, що обчислює середні значення
// Повертає LineStats (відповідно до вимоги "функція, яка повертає/обчислює/шукає")
LineStats CalculateMeans(const vector<double>& numbers) {
    LineStats stats;
    stats.numbers = numbers;
    int count = numbers.size();

    if (count == 0) {
        stats.arithmeticMean = 0.0;
        stats.geometricMean = 0.0;
        return stats;
    }

    // Середнє арифметичне
    double sum = 0.0;
    for (double num : numbers) {
        sum += num;
    }
    stats.arithmeticMean = sum / count;

    // Середнє геометричне
    double productLog = 0.0;
    bool hasZeroOrNegative = false;
    for (double num : numbers) {
        if (num <= 0) {
            hasZeroOrNegative = true;
            break;
        }
        productLog += log(num);
    }

    if (hasZeroOrNegative) {
        stats.geometricMean = 0.0;
    } else {
        stats.geometricMean = exp(productLog / count);
    }

    return stats;
}

// 3. Функція, що обробляє файл та записує результати у новий файл
// Повертає кількість оброблених рядків
int ProcessAndWriteTXT(const char* fname, const char* gname) {
    ifstream fin(fname);
    ofstream fout(gname, ios::trunc);

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Error: Could not open files for processing." << endl;
        return 0;
    }

    // !!! КРИТИЧНЕ ВИПРАВЛЕННЯ: Скидаємо прапор EOF та повертаємо курсор на початок.
    // Це забезпечує, що файл буде прочитаний коректно після CreateTXT/PrintTXT.
    fin.clear();
    fin.seekg(0, ios::beg);

    string s;
    int lineCount = 0;

    // Всі дії над даними виконуються у файлі (немає копіювання всього файлу в масив)
    while (getline(fin, s)) {
        lineCount++;
        stringstream ss(s);
        double num;
        vector<double> numbersInLine; // Використовується лише для обробки одного рядка

        // Вилучаємо числа з рядка. ss >> num ігнорує символи.
        while (ss >> num) {
            numbersInLine.push_back(num);
        }
        LineStats stats = CalculateMeans(numbersInLine);

        // Записуємо у новий файл
        fout << "Line " << lineCount << ": ";

        // 1. Записуємо вихідні числа
        for (double n : stats.numbers) {
            fout << fixed << setprecision(4) << n << " ";
        }

        // 2. Записуємо середні значення
        fout << "| AM: " << fixed << setprecision(4) << stats.arithmeticMean
             << " | GM: " << fixed << setprecision(4) << stats.geometricMean
             << endl;
    }

    fin.close();
    fout.close();

    return lineCount;
}