#include <iostream>

#include "matrix.h"

namespace bla = ASC_bla;
// use Matrix instead of bla::Matrix<double>

int
main() {
    bla::Matrix<double> mat1(10, 9);
    bla::Matrix<double> mat2(9, 10);
    bla::Vector<double> vec1(10);

    for (size_t i = 0; i < mat1.SizeRows(); i++) {
        for (size_t j = 0; j < mat1.SizeCols(); j++) {
            mat1(i, j) = (i + 1) * (j + 1);
            mat2(i, j) = 0;
            vec1(i) = 1;
        }
    }

    // print mat1

    bla::Matrix<double> mat3 = mat1 + mat2;
    std::cout << "mat3 = " << mat3 << std::endl;

    bla::Vector<double> vec2 = mat1 * vec1;
    std::cout << "vec2 = " << vec2 << std::endl;
    // for (int i = 0; i < mat1.SizeRows(); i++) {
    //     for (int j = 0; j < mat1.SizeCols(); j++) {
    //         std::cout << mat1(i, j) << ", ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}