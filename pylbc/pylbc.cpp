//
// Created by Shujian Qian on 2020-12-24.
//
#include <string>
#include <iostream>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/return_value_policy.hpp>

#include "pylbc/includes/defwrappers.h"
#include "pylbc/includes/metis_interface_wrapper.h"
#include "pylbc/includes/sparse_blas_lib_wrapper.h"
#include "pylbc/includes/sparse_utilities_wrapper.h"
//#include "pylbc/includes/sptrsv_demo_utils_wrapper.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

/*
int f (np::ndarray& x, np::ndarray& y) {
  std::cout << std::hex << (unsigned long int) &x << std::endl;
  std::cout << std::hex << (unsigned long int) x.get_data() << std::endl;
  std::cout << std::hex << (unsigned long int) &y << std::endl;
  std::cout << std::hex << (unsigned long int) y.get_data() << std::endl;
  
  auto x_data = reinterpret_cast<double*>(x.get_data());
  auto y_data = reinterpret_cast<double*>(y.get_data());
  for (int i = 0; i < 10; ++i) {
    std::cout << x_data[i] << "  ";
  }
  std::cout << std::endl;
  for (int i = 0; i < 10; ++i) {
    std::cout << y_data[i] << "  ";
  }
  std::cout << std::endl;

  return (int) (x.shape(0) + y.shape(0));
}
*/

BOOST_PYTHON_MODULE(pylbc) {
  using namespace boost::python;
  numpy::initialize();

  class_<CSCWrapper>("CSC", init<size_t, size_t, size_t>())
    .def(init<size_t, size_t, size_t, bool>())
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, np::ndarray&>())
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, int>())
    .def_readonly("m",   &CSCWrapper::m)
    .def_readonly("n",   &CSCWrapper::n)
    .def_readonly("nnz", &CSCWrapper::nnz)
  ;

  class_<CSRWrapper>("CSR", init<size_t, size_t, size_t>())
    .def(init<size_t, size_t, size_t, bool>())
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, int>())
    .def_readonly("m",   &CSRWrapper::m)
    .def_readonly("n",   &CSRWrapper::n)
    .def_readonly("nnz", &CSRWrapper::nnz)
  ;
//
//  class_<SptrsvSerialWrapper>("SptrsvSerial", init<CSRWrapper&, CSCWrapper&, np::ndarray&, std::string&>())
//    .def("evaluate", &SptrsvSerialWrapper::evaluate)
//    .def("solution")
//  ;

  CSCWrapper* (*make_half_1)(CSCWrapper&)       = &make_half_wrapper;
  CSCWrapper* (*make_half_2)(CSCWrapper&, bool) = &make_half_wrapper;

  CSCWrapper* (*transpose_symmetric_1)(CSCWrapper&)               = &transpose_symmetric_wrapper;
  CSCWrapper* (*transpose_symmetric_2)(CSCWrapper&, np::ndarray&) = &transpose_symmetric_wrapper;

  def("make_full", make_full_wrapper, return_value_policy<manage_new_object>());
  def("make_half", make_half_1, return_value_policy<manage_new_object>());
  def("make_half", make_half_2, return_value_policy<manage_new_object>());
  def("transpose_symmetric", transpose_symmetric_1, return_value_policy<manage_new_object>());
  def("transpose_symmetric", transpose_symmetric_2, return_value_policy<manage_new_object>());
  def("csc_to_csr", csc_to_csr_wrapper, return_value_policy<manage_new_object>());
  def("metis_perm_general", metis_partition_general_wrapper);

  def("sptrsv_csr", sptrsv_csr_wrapper);
//  def("f", f);
}