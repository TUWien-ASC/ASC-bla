#include <vector.h>
#include <pybind11/pybind11.h>


using namespace ASC_bla;
namespace py = pybind11;


PYBIND11_MODULE(ASC_bla, m) {
    m.doc() = "Basic linear algebra module"; // optional module docstring

    py::class_<Vector<double>> (m, "Vector")
      ;
}
