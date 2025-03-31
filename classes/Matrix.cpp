#include "Matrix.h"

Matrix::Matrix() : size(0), data(nullptr) {}

Matrix::Matrix(int n) : size(n), data(nullptr) {
    if (n <= 0) throw std::invalid_argument("Size must be positive");
    data = new int* [n];
    for (int i = 0; i < n; ++i) {
        data[i] = new int[n]();
    }
}

Matrix::Matrix(const Matrix& other) : size(other.size), data(nullptr) {
    if (other.data) {
        data = new int* [size];
        for (int i = 0; i < size; ++i) {
            data[i] = new int[size];
            for (int j = 0; j < size; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }
}

Matrix::~Matrix() {
    if (data) {
        for (int i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

int Matrix::getSize() const {
    return size;
}

void Matrix::setSize(int newSize) {
    if (newSize <= 0) throw std::invalid_argument("Size must be positive");

    if (data) {
        for (int i = 0; i < size; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    size = newSize;
    data = new int* [size];
    for (int i = 0; i < size; ++i) {
        data[i] = new int[size]();
    }
}

void Matrix::checkIndex(int i, int j) const {
    if (i < 0 || i >= size || j < 0 || j >= size)
        throw std::out_of_range("Index out of range");
}

int Matrix::getElement(int i, int j) const {
    checkIndex(i, j);
    return data[i][j];
}

void Matrix::setElement(int i, int j, int value) {
    checkIndex(i, j);
    data[i][j] = value;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
    if (a.size != b.size)
        throw std::invalid_argument("Matrix dimensions do not match for multiplication");

    Matrix result(a.size);
    for (int i = 0; i < a.size; ++i) {
        for (int j = 0; j < a.size; ++j) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.size; ++k) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

bool operator==(const Matrix& a, const Matrix& b) {
    if (a.size != b.size) return false;
    for (int i = 0; i < a.size; ++i) {
        for (int j = 0; j < a.size; ++j) {
            if (a.getElement(i, j) != b.getElement(i, j))
                return false;
        }
    }
    return true;
}
bool operator!=(const Matrix& a, const Matrix& b) {
    return !(a == b);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        setSize(other.size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                setElement(i, j, other.getElement(i, j));
            }
        }
    }
    return *this;
}

int* Matrix::operator[](int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

const int* Matrix::operator[](int index) const {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

Matrix::operator std::string() const {
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

std::istream& operator>>(std::istream& in, Matrix& matrix) {
    int n;
    std::cout << "Enter matrix size: ";
    while (!(in >> n) || n <= 0) {
        in.clear();
        in.ignore(10000, '\n');
        std::cout << "Error! Enter positive integer: ";
    }
    matrix.setSize(n);

    std::cout << "Enter " << n * n << " elements:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(in >> matrix.data[i][j])) {
                std::cout << "Error! Enter integer: ";
                in.clear();
                in.ignore(10000, '\n');
                --j;
            }
        }
    }

    std::string leftover;
    std::getline(in, leftover);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Matrix& matrix) {
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {
            out << matrix.data[i][j] << "\t";
        }
        out << "\n";
    }
    return out;
}

double Matrix::norm() const {
    if (size == 0) return 0.0;

    int sumOfSquares = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            sumOfSquares += data[i][j] * data[i][j];
        }
    }
    return std::sqrt(sumOfSquares);
}
