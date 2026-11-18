// Lab_7_1.cpp
// Боднар Роман
// Лабораторна робота № 7.1.
// Пошук заданих елементів та впорядкування рядків / стовпчиків матриці.
// Варіант 2
// 
// Умова завдання:
// 1. За допомогою генератора випадкових чисел формується матриця T розмірністю (7 x 9) 
//    із елементів цілого типу, значення яких належать діапазону (-41, ..., 23).
//    Обчислити кількість (k) та суму (S) тих елементів, які задовольняють критерію 
//    (усі, крім додатних, хоча б один індекс яких непарний), а також замінити ці елементи нулями.
// 2. Впорядковується матриця, переставляючи місцями її рядки відповідно до ключів впорядкування: ↑ ↑ ↓
//    - елементи першого стовпчика впорядковані за зростанням;
//    - якщо перші стовпчики рівні, елементи другого стовпчика впорядковані за зростанням;
//    - якщо перші та другі стовпчики рівні, елементи третього стовпчика впорядковані за спаданням.

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

// Прототипи функцій
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** a, const int rowCount, const int colCount);
void Sort(int** a, const int rowCount, const int colCount);
void Change(int** a, const int row1, const int row2, const int colCount);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k);

int main()
{
    // Оголошення змінних на початку функції main
    int Low;
    int High;
    int rowCount;
    int colCount;
    int S;
    int k;
    int** T;

    // Ініціалізація генератора випадкових чисел
    srand((unsigned)time(NULL));

    // Задання параметрів згідно з варіантом 2
    Low = -41;
    High = 23;
    rowCount = 7;
    colCount = 9;

    // Виділення пам'яті для динамічної матриці T
    T = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        T[i] = new int[colCount];

    // 1. Формування та виведення початкової матриці
    Create(T, rowCount, colCount, Low, High);
    cout << "Initial matrix T:" << endl;
    Print(T, rowCount, colCount);

    // 2. Впорядкування рядків матриці згідно з ключами: ↑ ↑ ↓
    Sort(T, rowCount, colCount);
    cout << "Sorted matrix T:" << endl;
    Print(T, rowCount, colCount);

    // 3. Обчислення кількості, суми та заміна нулями елементів за критерієм
    S = 0;
    k = 0;
    Calc(T, rowCount, colCount, S, k);

    cout << "Sum (S) = " << S << endl;
    cout << "Count (k) = " << k << endl;

    // Виведення модифікованої матриці
    cout << "Modified matrix T:" << endl;
    Print(T, rowCount, colCount);

    // Звільнення динамічної пам'яті
    for (int i = 0; i < rowCount; i++)
        delete[] T[i];
    delete[] T;

    return 0;
}

// Функція формування матриці випадковими числами у заданому діапазоні
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High)
{
    int i, j; // Оголошення змінних на початку функції
    for (i = 0; i < rowCount; i++)
        for (j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

// Функція виведення матриці на екран у вигляді таблиці
void Print(int** a, const int rowCount, const int colCount)
{
    int i, j; // Оголошення змінних на початку функції
    cout << endl;
    for (i = 0; i < rowCount; i++)
    {
        for (j = 0; j < colCount; j++)
            cout << setw(5) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

// Функція сортування рядків матриці за ключами: ↑ ↑ ↓ (стовпчики 0, 1, 2)
void Sort(int** a, const int rowCount, const int colCount)
{
    int i0, i1; // Оголошення змінних на початку функції
    for (i0 = 0; i0 < rowCount - 1; i0++)
    {
        for (i1 = 0; i1 < rowCount - i0 - 1; i1++)
        {
            if (
                // 1. Перший стовпчик за зростанням (↑)
                (a[i1][0] > a[i1 + 1][0])
                ||
                // 2. Якщо перші стовпчики рівні, другий стовпчик за зростанням (↑)
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] > a[i1 + 1][1])
                ||
                // 3. Якщо перші та другі стовпчики рівні, третій стовпчик за спаданням (↓)
                (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][2] < a[i1 + 1][2])
                )
            {
                Change(a, i1, i1 + 1, colCount);
            }
        }
    }
}

// Допоміжна функція для обміну місцями двох рядків матриці
void Change(int** a, const int row1, const int row2, const int colCount)
{
    int tmp, j; // Оголошення змінних на початку функції
    for (j = 0; j < colCount; j++)
    {
        tmp = a[row1][j];
        a[row1][j] = a[row2][j];
        a[row2][j] = tmp;
    }
}

// Функція обчислення суми, кількості та заміни нулями елементів за критерієм Варіанту 2:
// Критерій: усі, крім додатних, хоча б один індекс яких непарний.
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k)
{
    int i, j; // Оголошення змінних на початку функції
    bool isPositive, hasOddIndex;

    S = 0;
    k = 0;
    for (i = 0; i < rowCount; i++)
    {
        for (j = 0; j < colCount; j++)
        {
            isPositive = (a[i][j] < 0);
            hasOddIndex = (i % 2 != 0 || j % 2 != 0);

            // Критерій: елемент підходить, якщо він НЕ є (додатним з хоча б одним непарним індексом)
            if (!(isPositive && hasOddIndex))
            {
                S += a[i][j];
                k++;
                a[i][j] = 0; // Заміна елемента нулем
            }
        }
    }
}