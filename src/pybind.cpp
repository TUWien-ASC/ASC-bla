#include <sstream>
#include <pybind11/pybind11.h>

#include "vector.h"

using namespace ASC_bla;
namespace py = pybind11;




PYBIND11_MODULE(ASC_bla, m) {
    m.doc() = "Basic linear algebra module"; // optional module docstring
    
    py::class_<Vector<double>> (m, "Vector")
      .def(py::init<size_t>())
      .def("__len__", [](Vector<double> & self) { return self.Size(); },
           "return size of vector")
      
      .def("__setitem__", [](Vector<double> & self, size_t i, double v) { self(i) = v; })
      .def("__getitem__", [](Vector<double> & self, size_t i) { return self(i); })

      .def("__add__", [](Vector<double> & self, Vector<double> & other)
      { return Vector<double> (self+other); })
      
      .def("__str__", [](const Vector<double> & self)
      {
        std::stringstream str;
        str << self;
        return str.str();
      })
    ;
}
