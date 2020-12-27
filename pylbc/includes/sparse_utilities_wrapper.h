//
// Created by Shujian Qian on 2020-12-25.
//

#ifndef SYMPYLER_SPARSE_UTILITIES_WRAPPER_H
#define SYMPYLER_SPARSE_UTILITIES_WRAPPER_H

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "lbc/utils/includes/sparse_utilities.h"

#include "pylbc/includes/defwrappers.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

///
/// \param A
/// \return
CSCWrapper* make_half_wrapper(CSCWrapper& A) {
  return static_cast<CSCWrapper*>(
    sym_lib::make_half(A.n, A.p, A.i, A.x)
  );
}

///
/// \param A
/// \param lower
/// \return
CSCWrapper* make_half_wrapper(CSCWrapper& A, bool lower) {
  return static_cast<CSCWrapper*>(
      sym_lib::make_half(A.n, A.p, A.i, A.x, lower)
  );
}

///
/// \param A
/// \return
CSCWrapper* make_full_wrapper(CSCWrapper& A) {
  return static_cast<CSCWrapper*>(sym_lib::make_full(&A));
}

///
/// \param A
/// \return
CSCWrapper* transpose_symmetric_wrapper(CSCWrapper& A) {
  return static_cast<CSCWrapper*>(sym_lib::transpose_symmetric(&A, nullptr));
}

///
/// \param A
/// \param perm
/// \return
CSCWrapper* transpose_symmetric_wrapper(CSCWrapper& A, np::ndarray& perm) {
  return static_cast<CSCWrapper*>(
    sym_lib::transpose_symmetric(&A, reinterpret_cast<int*>(perm.get_data()))
  );
}

CSRWrapper* csc_to_csr_wrapper(CSCWrapper& A) {
  return static_cast<CSRWrapper*>(sym_lib::csc_to_csr(static_cast<CSCWrapper*>(&A)));
}

#endif //SYMPYLER_SPARSE_UTILITIES_WRAPPER_H
