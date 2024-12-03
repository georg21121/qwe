#include <iostream>
#include "load.h"
#include <cstdlib>
//#include <dlfcn.h> Для работы с динамическими библиотеками (Linux)
#include <windows.h> // Для Windows
using namespace std;

typedef void (*FillArrayFunc)(int*, int);
typedef void (*FillMatrixFunc)(int[4][11]);
typedef int (*SumInRangeArrayFunc)(int*, int, int, int);
typedef int (*SumInRangeMatrixFunc)(int[4][11], int, int);

int main() {
    int choice;
    cout << "1 - array\n2 - matrix\n";
    cin >> choice;

    if (choice == 1) {
        // Работа с массивом
#ifdef _WIN32
        HINSTANCE arrayLib = LoadLibrary("array_lib.dll");
        if (!arrayLib) {
            cerr << "error array_lib.dll\n";
            return 1;
        }

        // Загрузка функций
        FillArrayFunc fill_array = (FillArrayFunc)GetProcAddress(arrayLib, "fill_array");
        if (!fill_array) {
            cerr << "error fill_array\n";
            FreeLibrary(arrayLib);
            return 1;
        }

        SumInRangeArrayFunc sum_in_range = (SumInRangeArrayFunc)GetProcAddress(arrayLib, "sum_in_range");
        if (!sum_in_range) {
            cerr << "error sum_in_range\n";
            FreeLibrary(arrayLib);
            return 1;
        }
#else
        void* arrayLib = dlopen("./array_lib.so", RTLD_LAZY);
        if (!arrayLib) {
            cerr << "error array_lib.so\n";
            return 1;
        }

        // Загрузка функций
        FillArrayFunc fill_array = (FillArrayFunc)dlsym(arrayLib, "fill_array");
        if (!fill_array) {
            cerr << "error fill_array\n";
            dlclose(arrayLib);
            return 1;
        }

        SumInRangeArrayFunc sum_in_range = (SumInRangeArrayFunc)dlsym(arrayLib, "sum_in_range");
        if (!sum_in_range) {
            cerr << "error sum_in_range\n";
            dlclose(arrayLib);
            return 1;
        }
#endif

        // Работа с массивом
        int arr[11];
        fill_array(arr, 11);

        int X, Y;
        cout << "[X,Y]: ";
        cin >> X >> Y;

        int sum = sum_in_range(arr, 11, X, Y);
        cout << "sum [" << X << ", " << Y << "] = " << sum << "\n";

#ifdef _WIN32
        FreeLibrary(arrayLib);
#else
        dlclose(arrayLib);
#endif
    }
    else if (choice == 2) {
        // Работа с матрицей
#ifdef _WIN32
        HINSTANCE matrixLib = LoadLibrary("matrix_lib.dll");
        if (!matrixLib) {
            cerr << "error matrix_lib.dll\n";
            return 1;
        }

        // Загрузка функций
        FillMatrixFunc fill_matrix = (FillMatrixFunc)GetProcAddress(matrixLib, "fill_matrix");
        if (!fill_matrix) {
            cerr << "error fill_matrix\n";
            FreeLibrary(matrixLib);
            return 1;
        }

        SumInRangeMatrixFunc sum_in_range = (SumInRangeMatrixFunc)GetProcAddress(matrixLib, "sum_in_range");
        if (!sum_in_range) {
            cerr << "error sum_in_range\n";
            FreeLibrary(matrixLib);
            return 1;
        }
#else
        void* matrixLib = dlopen("./matrix_lib.so", RTLD_LAZY);
        if (!matrixLib) {
            cerr << "error matrix_lib.so\n";
            return 1;
        }

        // Загрузка функций
        FillMatrixFunc fill_matrix = (FillMatrixFunc)dlsym(matrixLib, "fill_matrix");
        if (!fill_matrix) {
            cerr << "error fill_matrix\n";
            dlclose(matrixLib);
            return 1;
        }

        SumInRangeMatrixFunc sum_in_range = (SumInRangeMatrixFunc)dlsym(matrixLib, "sum_in_range");
        if (!sum_in_range) {
            cerr << "error sum_in_range\n";
            dlclose(matrixLib);
            return 1;
        }
#endif

        // Работа с матрицей
        int matrix[4][11];
        fill_matrix(matrix);

        int X, Y;
        cout << "[X, Y]: ";
        cin >> X >> Y;

        int sum = sum_in_range(matrix, X, Y);
        cout << "sum [" << X << ", " << Y << "] = " << sum << "\n";

#ifdef _WIN32
        FreeLibrary(matrixLib);
#else
        dlclose(matrixLib);
#endif
    }
    else {
        cout << "net.\n";
    }
    cin.get();
    cin.get();
    return 0;
}
