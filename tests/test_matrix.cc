#include <ctime>
#include <iostream>

#include "matrix.h"

namespace bla = ASC_bla;
// use Matrix instead of bla::Matrix<double>

int
main() {
    int n = 10000;
    bla::Matrix<double> mat1(n, n);
    bla::Matrix<double> mat2(n, n);
    bla::Vector<double> vec1(n);

    for (size_t i = 0; i < mat1.SizeRows(); i++) {
        for (size_t j = 0; j < mat1.SizeCols(); j++) {
            mat1(i, j) = 2;
            mat2(i, j) = 1;
            vec1(i) = 1;
        }
    }

    // time the matrix-matrix addition
    std::clock_t start = std::clock();
    bla::Matrix<double> mat3 = mat1 + mat2;
    // std::cout << "mat3 = " << mat3 << std::endl;
    std::cout << "Time for matrix-matrix addition: "
              << (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000)
              << " ms" << std::endl;

    // time the matrix-vector multiplication, take the transpose of mat3
    start = std::clock();
    bla::Vector<double> vec2 = mat3.Transpose() * vec1;
    std::cout << "Time for matrix-vector multiplication: "
              << (std::clock() - start) / (double) (CLOCKS_PER_SEC / 1000)
              << " ms" << std::endl;
    // std::cout << "vec2 = " << vec2 << std::endl;

    return 0;
}