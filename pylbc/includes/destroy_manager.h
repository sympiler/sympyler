//
// Created by Shujian Qian on 2020-12-28.
//

#ifndef SYMPYLER_DESTROY_MANAGER_H
#define SYMPYLER_DESTROY_MANAGER_H

#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace bp = boost::python;
namespace np = boost::python::numpy;

template <class T>
void destroy_manager_carray(PyObject* obj) {
  int* a = reinterpret_cast<T*>(PyCapsule_GetPointer(obj, nullptr));
  delete [] a;
}

#endif //SYMPYLER_DESTROY_MANAGER_H
