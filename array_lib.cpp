#include <iostream>
#include <cstdlib>
#include <ctime>

extern "C" {
    __declspec(dllexport) void fill_array(int* arr, int size) {
        std::srand(std::time(0));
        for (int i = 0; i < size; ++i) {
            arr[i] = std::rand() % 101 - 50; // Случайные числа от -50 до 50
        }
    }

    __declspec(dllexport) int sum_in_range(int* arr, int size, int X, int Y) {
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            if (arr[i] >= X && arr[i] <= Y) {
                sum += arr[i];
            }
        }
        return sum;
    }
}
