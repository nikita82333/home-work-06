#include <iostream>
#include <vector>

#include "Matrix.hpp"

int main(int, char**) {

    Matrix<int, 0> matrix;

    for (int i = 0; i < 10; ++i) {
        matrix[i][i] = i;
        matrix[i][9 - i] = 9 - i;
    }

    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Cell count: " << matrix.size() << std::endl;

    for (const auto& [index, v] : matrix) {
        std::cout << "[" << index[0] << ", " << index[1] << "] = " << v << std::endl;
    }

    return 0;
}
