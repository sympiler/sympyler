//
// Created by Shujian Qian on 2020-12-26.
//

#ifndef SYMPYLER_SPTRSV_DEMO_UTILS_WRAPPER_H
#define SYMPYLER_SPTRSV_DEMO_UTILS_WRAPPER_H

#include <string>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "lbc/example/sptrsv_demo_utils.h"

#include "pylbc/includes/defwrappers.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

class SptrsvSerialWrapper : public sym_lib::SptrsvSerial {
  SptrsvSerialWrapper(
    CSRWrapper& L,
    CSCWrapper& L_csc,
    np::ndarray& x,
    std::string& name
  )
  : SptrsvSerial (
    static_cast<CSR*>(&L),
    static_cast<CSC*>(&L_csc),
    reinterpret_cast<double*>(x.get_data()),
    name
  ) {}
};

#endif //SYMPYLER_SPTRSV_DEMO_UTILS_WRAPPER_H
