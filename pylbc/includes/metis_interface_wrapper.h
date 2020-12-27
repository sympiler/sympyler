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

namespace bp = boost::python;
namespace np = boost::python::numpy;

void destroy_manager_cobject_int_array(PyObject* obj) {
  int* a = reinterpret_cast<int*>(PyCapsule_GetPointer(obj, nullptr));
  delete [] a;
}

np::ndarray metis_partition_general_wrapper(CSCWrapper& A) {
  int* perm = nullptr;
  int ret = sym_lib::metis_perm_general(&A, perm);

  // Creates a PyCapsule which is essentially a smart pointer for the perm array
  // created in metis_perm_general
  bp::handle<> h(::PyCapsule_New(
    (void*) perm, nullptr,
    (PyCapsule_Destructor) &destroy_manager_cobject_int_array)
  );
  np::dtype dt = np::dtype::get_builtin<int>();
  bp::tuple shape = bp::make_tuple(A.n);
  bp::tuple stride = bp::make_tuple(sizeof(int));
  np::ndarray arr = np::from_data(perm, dt, shape, stride, bp::object(h));

  return arr;
}

#endif //SYMPYLER_METIS_INTERFACE_WRAPPER_H
