//
// Created by Shujian Qian on 2020-12-26.
//

#ifndef SYMPYLER_SPARSE_BLAS_LIB_WRAPPER_H
#define SYMPYLER_SPARSE_BLAS_LIB_WRAPPER_H

#include <string>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "lbc/example/sparse_blas_lib.h"

#include "pylbc/includes/defwrappers.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

void sptrsv_csr_wrapper (CSRWrapper& L, np::ndarray& b) {
  sym_lib::sptrsv_csr(L.n, L.p, L.i, L.x, reinterpret_cast<double*>(b.get_data()));
}

#endif //SYMPYLER_SPARSE_BLAS_LIB_WRAPPER_H
