#include <iostream>

#include "matrix.h"

namespace bla = ASC_bla;
// use Matrix instead of bla::Matrix<double>

int
main() {
    bla::Matrix<double> mat1(10, 10);
    bla::Matrix<double> mat2(10, 10);

    bla::Matrix<double> mat3 = mat1 + mat2;

    for (int i = 0; i < mat3.SizeRows(); i++) {
        for (int j = 0; j < mat3.SizeCols(); j++) {
            std::cout << mat3(i, j) << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}