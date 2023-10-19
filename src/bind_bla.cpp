#define PYBIND11_DETAILED_ERROR_MESSAGES

#include <pybind11/pybind11.h>

#include <sstream>

#include "matrix.h"
#include "vector.h"

using namespace ASC_bla;
namespace py = pybind11;

PYBIND11_MODULE(bla, m) {
  m.doc() = "Basic linear algebra module";  // optional module docstring

  py::class_<Vector<double>>(m, "Vector")
      .def(py::init<size_t>(), py::arg("size"), "create vector of given size")
      .def("__len__", &Vector<double>::Size, "return size of vector")
      .def("__setitem__",
           [](Vector<double>& self, int i, double v) {
             if (i < 0) i += self.Size();
             if (i < 0 || i >= self.Size())
               throw py::index_error("vector index out of range");
             self(i) = v;
           })
      .def("__getitem__", [](Vector<double>& self, int i) { return self(i); })

      .def("__setitem__",
           [](Vector<double>& self, py::slice inds, double val) {
             size_t start, stop, step, n;
             if (!inds.compute(self.Size(), &start, &stop, &step, &n))
               throw py::error_already_set();
             self.Range(start, stop).Slice(0, step) = val;
           })
      .def("__getitem__",
           [](Vector<double>& self, py::slice inds) {
             size_t start, stop, step, n;
             if (!inds.compute(self.Size(), &start, &stop, &step, &n))
               throw py::error_already_set();
             return self.Range(start, stop).Slice(0, step);
           })

      .def("__add__",
           [](Vector<double>& self, Vector<double>& other) {
             return Vector<double>(self + other);
           })

      .def("__rmul__", [](Vector<double>& self,
                          double scal) { return Vector<double>(scal * self); })
      
      .def("__mul__", [](Vector<double>& self,
                          double scal) { return Vector<double>(scal * self); })

      .def("__str__",
           [](const Vector<double>& self) {
             std::stringstream str;
             str << self;
             return str.str();
           })

      .def(py::pickle(
          [](Vector<double>& self) {  // __getstate__
            /* return a tuple that fully encodes the state of the object */
            return py::make_tuple(self.Size(),
                                  py::bytes((char*)(void*)&self(0),
                                            self.Size() * sizeof(double)));
          },
          [](py::tuple t) {  // __setstate__
            if (t.size() != 2) throw std::runtime_error("should be a 2-tuple!");

            Vector<double> v(t[0].cast<size_t>());
            py::bytes mem = t[1].cast<py::bytes>();
            std::memcpy(&v(0), PYBIND11_BYTES_AS_STRING(mem.ptr()),
                        v.Size() * sizeof(double));
            return v;
          }))

      ;

  // from here my Matrix implementation
  py::class_<Matrix<double, RowMajor>>(m, "Matrix")
      //.def(py::init<size_t, size_t>(), py::arg("rows"), py::arg("cols"),
      //     "create matrix : rows x cols")
      //  .def("__getitem__",
      //       [](Matrix<double, RowMajor> self, py::tuple i) {
      //         return self(i[0].cast<size_t>(), i[1].cast<size_t>());
      //       })
      .def(py::init([](size_t rows, size_t cols) {
        Matrix<double, RowMajor> m(rows, cols);
        m = 0;
        return m;
      }))

      .def("__getitem__",
           [](Matrix<double, RowMajor> & self, std::tuple<int, int> i) {
             return self(std::get<0>(i), std::get<1>(i));
           })
      .def("__setitem__",
           [](Matrix<double, RowMajor>& self, std::tuple<int, int> i,
              double val) { self(std::get<0>(i), std::get<1>(i)) = val; })

      .def("__getitem__",
           [](Matrix<double, RowMajor>& self,
              std::tuple<py::slice, py::slice> inds) {
             size_t start1, stop1, step1, n1;
             size_t start2, stop2, step2, n2;
             if (!std::get<0>(inds).compute(self.SizeRows(), &start1, &stop1,
                                            &step1, &n1))
               throw py::error_already_set();
             if (!std::get<1>(inds).compute(self.SizeCols(), &start2, &stop2,
                                            &step2, &n2))
               throw py::error_already_set();
             return Matrix<double , RowMajor>(self.Cols(start1, stop1).Rows(start2, stop2));
           })

      .def("__setitem__",
           [](Matrix<double, RowMajor>& self,
              std::tuple<py::slice, py::slice> inds, double val) {
             size_t start1, stop1, step1, n1;
             size_t start2, stop2, step2, n2;
             if (!std::get<0>(inds).compute(self.SizeRows(), &start1, &stop1,
                                            &step1, &n1))
               throw py::error_already_set();
             if (!std::get<1>(inds).compute(self.SizeCols(), &start2, &stop2,
                                            &step2, &n2))
               throw py::error_already_set();
             self.Cols(start1, stop1).Rows(start2, stop2) = val;
           })
      .def("__setitem__",
           [](Matrix<double, RowMajor>& self, std::tuple<int, py::slice> inds,
              double val) {
             size_t start, stop, step, n;
             if (!std::get<1>(inds).compute(self.SizeCols(), &start, &stop,
                                            &step, &n))
               throw py::error_already_set();
             self.Rows(std::get<0>(inds), std::get<0>(inds) + 1)
                 .Cols(start, stop) = val;
           })
      .def("__setitem__",
           [](Matrix<double, RowMajor>& self, std::tuple<py::slice, int> inds,
              double val) {
             size_t start, stop, step, n;
             if (!std::get<0>(inds).compute(self.SizeRows(), &start, &stop,
                                            &step, &n))
               throw py::error_already_set();
             self.Rows(start, stop)
                 .Cols(std::get<1>(inds), std::get<1>(inds) + 1) = val;
           })

      .def("__add__",
           [](Matrix<double, RowMajor>& self, Matrix<double, RowMajor>& other) {
             return Matrix<double, RowMajor>(self + other);
           })

      // mult by scalar matrix
      .def("__rmul__",
           [](Matrix<double, RowMajor>& self, double scal) {
             return Matrix<double, RowMajor>(scal * self);
           })
      .def("__mul__",
           [](Matrix<double, RowMajor>& self, double scal) {
             return Matrix<double, RowMajor>(scal * self);
           })

      // mult matrix matrix
      .def("__mul__",
           [](Matrix<double, RowMajor>& self, Matrix<double, RowMajor>& other) {
             return Matrix<double, RowMajor>(self * other);
           })
      .def("__rmul__",
           [](Matrix<double, RowMajor>& self, Matrix<double, RowMajor>& other) {
             return Matrix<double, RowMajor>(self * other);
           })

      // mult matrix vector
      .def("__mul__",
           [](Matrix<double, RowMajor>& self, Vector<double>& other) {
             return Vector<double>(self * other);
           })
      .def("__rmul__",
           [](Matrix<double, RowMajor>& self, Vector<double>& other) {
             return Vector<double>(self * other);
           })

      .def("__str__",
           [](const Matrix<double, RowMajor>& self) {
             std::stringstream str;
             str << self;
             return str.str();
           })

      // shape of the matrix
      .def_property_readonly("shape",
                             [](const Matrix<double, RowMajor>& self) {
                               return std::tuple(self.SizeRows(),
                                                 self.SizeCols());
                             })

      // transpose
      .def_property_readonly("T",
                             [](const Matrix<double, RowMajor>& self) {
                               return Matrix<double, RowMajor>(Transpose(self));
                             })

      
      // inverse
      .def_property_readonly("inv",
                             [](const Matrix<double, RowMajor>& self) {
                               return Matrix<double, RowMajor>(Inverse(self));
                             })
      

      ;
}
