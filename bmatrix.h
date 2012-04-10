#ifndef BMATRIX_H
#define BMATRIX_H
#include <memory>
template<typename Type>
struct Matrix {
    Matrix(int width_, int height_, Type * values)
        : width(width_), height(height_) {
        matrix = new Type[width*height];
        std::memcpy(matrix, values, width*height*sizeof(Type));
    }

    ~Matrix() {
        delete matrix;
        matrix = 0;
    }
    Matrix(const Matrix<Type> & matrix) {
        width = matrix.width;
        height = matrix.height;
        this->matrix = new Type[width*height];
        std::memcpy(this->matrix, matrix.matrix, width*height*sizeof(Type));
    }

    Type Get(int row, int col) const {
        return matrix[row*width + col];
    }

    void operator *=(const Type value) {
        for (int i = 0; i < width*height; ++i) {
            matrix[i] = matrix[i] * value;
        }
    }

    int width;
    int height;

private:
    Matrix & operator= (const Matrix & matrix);
    Type * matrix;
};
#endif // BMATRIX_H
