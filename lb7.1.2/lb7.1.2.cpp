#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** a, const int rowCount, const int colCount, int i = 0, int j = 0);
void Sort(int** a, const int rowCount, const int colCount, int i0 = 0, int i1 = 0);
void Change(int** a, const int row1, const int row2, const int colCount, int j = 0);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main()
{
    srand((unsigned)time(NULL));
    int Low = 11;
    int High = 67;
    int rowCount = 7;
    int colCount = 5;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    Print(a, rowCount, colCount);
    Sort(a, rowCount, colCount);
    Print(a, rowCount, colCount);

    int S = 0;
    int k = 0;
    Calc(a, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    if (i >= rowCount)
        return;

    a[i][j] = Low + rand() % (High - Low + 1); 

    
    if (j + 1 < colCount)
        Create(a, rowCount, colCount, Low, High, i, j + 1); 
    else
        Create(a, rowCount, colCount, Low, High, i + 1, 0); 
}

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
    if (i >= rowCount) 
    {
        cout << endl;
        return;
    }

    cout << setw(4) << a[i][j]; 

    
    if (j + 1 < colCount)
        Print(a, rowCount, colCount, i, j + 1); 
    else
    {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0); 
    }
}

void Sort(int** a, const int rowCount, const int colCount, int i0, int i1)
{
    if (i0 >= rowCount - 1) 
        return;

    if (i1 < rowCount - i0 - 1)
    {
        if ((a[i1][0] < a[i1 + 1][0]) ||
            (a[i1][0] == a[i1 + 1][0] && a[i1][1] < a[i1 + 1][1]) ||
            (a[i1][0] == a[i1 + 1][0] && a[i1][1] == a[i1 + 1][1] && a[i1][2] < a[i1 + 1][2]))


        Sort(a, rowCount, colCount, i0, i1 + 1); 
    }
    else
        Sort(a, rowCount, colCount, i0 + 1, 0); 
}

void Change(int** a, const int row1, const int row2, const int colCount, int j)
{
    if (j >= colCount) 
        return;

    int tmp = a[row1][j]; 
    a[row1][j] = a[row2][j];
    a[row2][j] = tmp;

    Change(a, row1, row2, colCount, j + 1); 
}

void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    if (i >= rowCount)
        return;

    if (j < colCount)
    {
        if (!((a[i][j] % 2 == 0) && (a[i][j] % 13 == 0)))
        {
            S += a[i][j];
            k++;
            a[i][j] = 0;
        }
        Calc(a, rowCount, colCount, S, k, i, j + 1);
    }
    else
        Calc(a, rowCount, colCount, S, k, i + 1, 0);
}