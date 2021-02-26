//
// Created by Shujian Qian on 2021-01-18.
//

#ifndef SYMPYLER_DEF_WRAPPER_H
#define SYMPYLER_DEF_WRAPPER_H

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "nasoq/smp-format/def.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

struct CSCWrapper : public format::CSC {
  CSCWrapper () : CSC() {}

  CSCWrapper(size_t M, size_t N, size_t NNZ) : CSC(M, N, NNZ) {}

  CSCWrapper(size_t M, size_t N, size_t NNZ, bool ip) : CSC(M, N, NNZ, ip) {}

  CSCWrapper(
    size_t M, size_t N, size_t NNZ,
    np::ndarray& Ap,
    np::ndarray& Ai,
    int st
  )
  : CSC(
    M, N, NNZ,
    reinterpret_cast<int*>   (Ap.get_data()),
    reinterpret_cast<int*>   (Ai.get_data()),
    st
  ) {}

  CSCWrapper(
    size_t M, size_t N, size_t NNZ,
    np::ndarray& Ap,
    np::ndarray& Ai,
    np::ndarray& Ax
  )
  : CSC(
    M, N, NNZ,
    reinterpret_cast<int*>   (Ap.get_data()),
    reinterpret_cast<int*>   (Ai.get_data()),
    reinterpret_cast<double*>(Ax.get_data())
  ) {}

  bool equality_check(const CSCWrapper& in_c) {
    return CSC::equality_check(static_cast<const format::CSC*>(&in_c));
  }

  /* Not exposed */

  // Internal helper function that creates a copy of CSCWrapper from CSC
  explicit CSCWrapper(const format::CSC& rhs)
  : CSC(rhs.m, rhs.n, rhs.nnz) {
    for (int j = 0; j < rhs.n + 1; ++j) {
      p[j] = rhs.p[j];
    }
    for (int j = 0; j < rhs.nnz; ++j) {
      i[j] = rhs.i[j];
      x[j] = rhs.x[j];
    }
  }
};

struct DenseWrapper : public format::Dense {
  DenseWrapper(size_t M, size_t N, size_t LDA) : Dense(M, N, LDA) {}

  DenseWrapper(size_t M, size_t N, size_t LDA, double init) : Dense(M, N, LDA, init) {}

  DenseWrapper(const DenseWrapper& d) : Dense(d) {}

  bool equality_check(const DenseWrapper& in_d) {
    return Dense::equality_check(static_cast<const format::Dense*>(&in_d));
  }

  bool is_finite() {
    return Dense::is_finite();
  }

  /* Not exposed */
  explicit DenseWrapper(const format::Dense& rhs) : Dense(rhs) {}
};

#endif //SYMPYLER_DEF_WRAPPER_H
