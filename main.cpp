#include "lab_11_4.h"
#include <string>

// Допоміжна функція для контролю помилок введення
int getMenuChoice() {
    int choice = -1;
    while (true) {
        if (!(cin >> choice)) {
            // Контроль помилок: якщо введено не число
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear(); // Скидаємо прапор помилки cin
            // Очищаємо буфер від некоректного вводу
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            // Очищаємо буфер після коректного вводу, щоб не конфліктувати з getline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (choice >= 0 && choice <= 3) {
                return choice;
            } else {
                cout << "Invalid choice. Please select 0, 1, 2, or 3." << endl;
            }
        }
    }
}

int main() {
    // Використовуємо std::string для безпечного вводу імен файлів
    string fname_str = "input.txt"; // Початкове ім'я за замовчуванням
    string gname_str = "output.txt"; // Початкове ім'я за замовчуванням
    int choice;

    // Введення імен файлів на початку (згідно вимоги завдання)
    cout << "Enter name for the INPUT file (current: " << fname_str << "): ";
    if (cin >> fname_str) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter name for the OUTPUT file (current: " << gname_str << "): ";
    if (cin >> gname_str) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    do {
        ShowMenu();
        choice = getMenuChoice();

        switch (choice) {
            case 1: {
                // Створення файлу
                CreateTXT(fname_str.c_str());
                break;
            }
            case 2: {
                // Виведення вмісту
                PrintTXT(fname_str.c_str());
                break;
            }
            case 3: {
                // Обробка файлу
                cout << "\n--- Processing " << fname_str << " to " << gname_str << " ---" << endl;
                int linesProcessed = ProcessAndWriteTXT(fname_str.c_str(), gname_str.c_str());

                if (linesProcessed > 0) {
                    cout << "Processing complete. Total lines processed: " << linesProcessed << endl;
                    cout << "Results were written to file: " << gname_str << endl;
                    PrintTXT(gname_str.c_str());
                } else {
                    cout << "Processing failed or file is empty." << endl;
                }
                break;
            }
            case 0: {
                cout << "\nProgram finished." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}