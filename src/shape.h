#ifndef FILE_SHAPE_H
#define FILE_SHAPE_H

namespace ASC_bla {
class Shape {
    size_t rows_, cols_;

   public:
    Shape(size_t rows = 0, size_t cols = 0) : rows_(rows), cols_(cols) {}

    Shape(const Shape &s) : Shape(s.NumRows(), s.NumCols()) { *this = s; }

    ~Shape() {}

    Shape &operator=(const Shape &s2) { return *this; }

    Shape(Shape &&s) : rows_{0}, cols_{0}
    {
        std::swap(rows_, s.rows_);
        std::swap(cols_, s.cols_);
    }

    Shape &operator=(Shape &&v2) { return *this; }
    size_t NumRows() const { return rows_; }
    size_t NumCols() const { return cols_; }
};

}  // namespace ASC_bla

#endif
