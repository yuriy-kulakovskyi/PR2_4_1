#include <iostream>
#include "./classes/Matrix.h"

int main() {
    try {
        Matrix m1, m2;

        std::cout << "--- Enter matrix m1 ---\n";
        std::cin >> m1;
        std::cout << "\nMatrix m1:\n" << m1;
        std::cout << "Norm m1: " << m1.norm() << "\n\n";

        std::cout << "--- Enter matrix m2 ---\n";
        std::cin >> m2;
        std::cout << "\nMatrix m2:\n" << m2;
        std::cout << "Norm m2: " << m2.norm() << "\n\n";

        if (m1.getSize() == m2.getSize()) {
            Matrix m3 = m1 * m2;
            std::cout << "Multiplication result m1 * m2:\n" << m3;
        }
        else {
            std::cout << "Cannot multiply matrices of different sizes.\n";
        }

        std::cout << "m1 == m2? " << (m1 == m2 ? "Yes" : "No") << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
