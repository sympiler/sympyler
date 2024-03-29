//
// Created by Shujian Qian on 2020-12-25.
//

#ifndef SYMPYLER_METIS_INTERFACE_WRAPPER_H
#define SYMPYLER_METIS_INTERFACE_WRAPPER_H

#include <iostream>

#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "lbc/utils/includes/metis_interface.h"

#include "pylbc/includes/defwrappers.h"
#include "pylbc/includes/destroy_manager.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

np::ndarray metis_partition_general_wrapper(CSCWrapper& A) {
  int* perm = nullptr;
  int ret = sym_lib::metis_perm_general(&A, perm);

  // Create a boost python handle (smart pointer) to automatically delete
  // dynamically allocated C array.
  bp::handle<> h(::PyCapsule_New(
    (void*) perm, nullptr,
    (PyCapsule_Destructor) &destroy_manager_carray<int>)
  );
  np::dtype dt = np::dtype::get_builtin<int>();
  bp::tuple shape = bp::make_tuple(A.n);
  bp::tuple stride = bp::make_tuple(sizeof(int));

  // Create numpy ndarray from dynamically allocated C array and set a boost
  // python object with previously defined handle as owner.
  np::ndarray arr = np::from_data(perm, dt, shape, stride, bp::object(h));

  return arr;
}

#endif //SYMPYLER_METIS_INTERFACE_WRAPPER_H
