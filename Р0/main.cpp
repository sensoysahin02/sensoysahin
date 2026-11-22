#include <iostream>
#include <new> // std::nothrow için

// Referans olarak alınan işaretçiyi temizler ve güvenli şekilde nullptr yapar
void freeMatrix(int**& matrix, int rows) {
    if (matrix == nullptr) {
        return;
    }

    for (int i = 0; i < rows; ++i) {
        if (matrix[i] != nullptr) {
            delete[] matrix[i];
            matrix[i] = nullptr;
        }
    }

    delete[] matrix;
    matrix = nullptr;
}

// Dinamik 2D matris ayırır; başarısız olursa temizlik yapıp nullptr döndürür
int** allocateMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** matrix = new (std::nothrow) int*[rows];
    if (matrix == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = nullptr;
    }

    for (int i = 0; i < rows; ++i) {
        matrix[i] = new (std::nothrow) int[cols];
        if (matrix[i] == nullptr) {
            freeMatrix(matrix, i);
            return nullptr;
        }
    }

    return matrix;
}

int main() {
    // Sabit matris boyutları: 3 satır, 4 sütun
    const int rows = 3;
    const int cols = 4;

    // 1. Orijinal matris (3x4) için bellek ayır
    int** matrix = nullptr;
    matrix = allocateMatrix(rows, cols);
    if (matrix == nullptr) {
        return 2;
    }

    // 2. 12 adet matris elemanını standart girişten oku
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                freeMatrix(matrix, rows);
                return 1;
            }
        }
    }

    // 3. Transpoz matris (4x3) için bellek ayır
    int** transposed = nullptr;
    transposed = allocateMatrix(cols, rows);
    if (transposed == nullptr) {
        freeMatrix(matrix, rows);
        return 2;
    }

    // 4. Transpoz işlemini gerçekleştir
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    // 5. Transpoz matrisi (4 satır x 3 sütun) standart çıkışa yazdır
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            std::cout << transposed[i][j] << (j + 1 < rows ? " " : "");
        }
        std::cout << "\n";
    }

    // 6. Kullanılan tüm belleği serbest bırak
    freeMatrix(matrix, rows);
    freeMatrix(transposed, cols);

    return 0;
}
