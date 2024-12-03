#include <iostream>
#include <cstdlib>
#include <ctime>

extern "C" {
    __declspec(dllexport) void fill_matrix(int matrix[4][11]) {
        std::srand(std::time(0));
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 11; ++j) {
                matrix[i][j] = std::rand() % 101 - 50; // Случайные числа от -50 до 50
            }
        }
    }

    __declspec(dllexport) int sum_in_range(int matrix[4][11], int X, int Y) {
        int sum = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 11; ++j) {
                if (matrix[i][j] >= X && matrix[i][j] <= Y) {
                    sum += matrix[i][j];
                }
            }
        }
        return sum;
    }
}
