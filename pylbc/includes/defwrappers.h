//
// Created by Shujian Qian on 2020-12-24.
//

#ifndef SYMPYLER_DEFWRAPPERS_H
#define SYMPYLER_DEFWRAPPERS_H

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "lbc/utils/includes/def.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

struct CSCWrapper : public CSC {
  ///
  /// \param M
  /// \param N
  /// \param NNZ
  CSCWrapper(size_t M, size_t N, size_t NNZ) : CSC(M, N, NNZ) {}

  ///
  /// \param M
  /// \param N
  /// \param NNZ
  /// \param ip
  CSCWrapper(size_t M, size_t N, size_t NNZ, bool ip) : CSC(M, N, NNZ, ip) {}

  ///
  /// \param M
  /// \param N
  /// \param NNZ
  /// \param Ap
  /// \param Ai
  /// \param st
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

  ///
  /// \param M
  /// \param N
  /// \param NNZ
  /// \param Ap
  /// \param Ai
  /// \param Ax
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
};

struct CSRWrapper : public CSR {
  ///
  /// \param M
  /// \param N
  /// \param NNZ
  CSRWrapper(size_t M, size_t N, size_t NNZ) : CSR(M, N, NNZ) {}

  ///
  /// \param M
  /// \param N
  /// \param NNZ
  /// \param ip
  CSRWrapper(size_t M, size_t N, size_t NNZ, bool ip) : CSR(M, N, NNZ, ip) {}

  ///
  /// \param M
  /// \param N
  /// \param NNZ
  /// \param Ap
  /// \param Ai
  /// \param st
  CSRWrapper(
    size_t M, size_t N, size_t NNZ,
    np::ndarray& Ap,
    np::ndarray& Ai,
  int st
  )
  : CSR (
    M, N, NNZ,
    reinterpret_cast<int*>(Ap.get_data()),
    reinterpret_cast<int*>(Ai.get_data()),
    st
  ) {}
};

#endif //SYMPYLER_DEFWRAPPERS_H
