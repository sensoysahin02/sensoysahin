#include <iostream>
#include <new>

void freeMatrix(int** matrix, int rows) {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int main() {
    int rows = 0, cols = 0;

    if(!(std::cin >> rows >> cols) || rows <= 0 || cols <= 0) {
        return 1;
    }

    int** matrix = new(std::nothrow) int*[rows];
    if (matrix == nullptr) {
        return 2;
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = nullptr;
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = new(std::nothrow) int[cols];
        if (matrix[i] == nullptr) {
            freeMatrix(matrix, rows);
            return 2;
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                freeMatrix(matrix, rows);
                return 1;
            }
        }
    }

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            std::cout << matrix[i][j];
            if (i < rows - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl,
    }

    freeMatrix(matrix, rows);
    return 0;
}