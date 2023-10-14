#include <nanobind/ndarray.h>

#include "naive.h"

#if defined(__aarch64__)
#  include "arm_neon.h"
#elif defined(__AVX512F__)
#  include "intel_avx512.h"
#elif defined(__AVX__)
#  include "intel_avx.h"
#else
#  error No known instruction set extension found
#endif

NB_MODULE(psum, m) {
    namespace nb = nanobind;

    using Array = nb::ndarray<float, nb::shape<nb::any>, nb::c_contig>;

    m.def("psum_0", [](Array a) { return psum_0(a.data(), a.shape(0)); })
     .def("psum_1", [](Array a) { return psum_1(a.data(), a.shape(0)); })
     .def("psum_2", [](Array a) { return psum_2(a.data(), a.shape(0)); })
     .def("psum_3", [](Array a) { return psum_3(a.data(), a.shape(0)); });
}
