#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cassert>
#include <windows.h>

using namespace std;

// Алгоритм
void shellSort(vector<int>& arr) {
    int n = static_cast<int>(arr.size());
    if (n <= 1) return;

    int gap = 1;
    while (gap < n / 3) gap = gap * 3 + 1; // Последовательность Кнута

    for (; gap > 0; gap /= 3) {
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// Визуализация
void printArrayState(const vector<int>& arr, int gap, int highlightIdx) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (static_cast<int>(i) == highlightIdx)
            cout << "[" << setw(3) << arr[i] << "] ";
        else
            cout << " " << setw(3) << arr[i] << "  ";
    }
    if (gap > 0) cout << " | gap = " << gap;
    cout << "\n";
}

void visualizeShellSort(vector<int> arr) {
    int n = static_cast<int>(arr.size());
    int gap = 1;
    while (gap < n / 3) gap = gap * 3 + 1;

    cout << "\nВизуализация\n";
    printArrayState(arr, gap, -1);
    this_thread::sleep_for(chrono::milliseconds(300));

    for (; gap > 0; gap /= 3) {
        cout << "\n[ Переход к шагу gap = " << gap << " ]\n";
        for (int i = gap; i < n; ++i) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
                printArrayState(arr, gap, j + gap);
                this_thread::sleep_for(chrono::milliseconds(150));
            }
            arr[j] = temp;
            printArrayState(arr, gap, j);
            this_thread::sleep_for(chrono::milliseconds(150));
        }
    }
    cout << "\nСортировка завершена\n\n";
}

// Тестирование
void runTests() {
    cout << "\nЗапуск автотестов\n";

    auto test = [](vector<int> input, const string& name) {
        vector<int> original = input;
        shellSort(input);
        bool passed = is_sorted(input.begin(), input.end());
        cout << (passed ? "[PASS] " : "[FAIL] ") << name << "\n";
        assert(passed);
        };

    test({ 1, 2, 3, 4, 5 }, "Уже отсортирован");
    test({ 5, 4, 3, 2, 1 }, "Обратный порядок");
    test({ 3, 1, 4, 1, 5, 9, 2, 6 }, "С дубликатами");
    test({ 42 }, "Один элемент");
    test({}, "Пустой массив");
    test({ 10, -3, 0, 7, -1, 5 }, "Отрицательные числа");

    cout << "Все тесты пройдены успешно.\n\n";
}

// Точка входа
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<int> defaultData = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50, 42 };

    cout << "Проект: Сортировка методом Шелла\n";
    cout << "1. Быстрая сортировка (без вывода шагов)\n";
    cout << "2. Пошаговая визуализация\n";
    cout << "3. Запуск автотестов\n";
    cout << "0. Выход\n";
    cout << "Выберите действие (0-3): ";

    int choice;
    if (!(cin >> choice)) return 1;

    switch (choice) {
    case 1: {
        vector<int> arr = defaultData;
        shellSort(arr);
        cout << "\nРезультат: ";
        for (int x : arr) cout << x << " ";
        cout << "\n";
        break;
    }
    case 2:
        visualizeShellSort(defaultData);
        break;
    case 3:
        runTests();
        break;
    case 0:
        return 0;
    default:
        cout << "Некорректный выбор, завершение работы программы.\n";
    }
    return 0;
}