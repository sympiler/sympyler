//
// Created by Shujian Qian on 2020-12-24.
//
#include <string>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/return_value_policy.hpp>

#include "pylbc/includes/defwrappers.h"
#include "pylbc/includes/metis_interface_wrapper.h"
#include "pylbc/includes/sparse_blas_lib_wrapper.h"
#include "pylbc/includes/sparse_utilities_wrapper.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

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
  def("sptrsv_csr_levelset", sptrsv_csr_levelset_wrapper);
  def("sptrsv_csr_lbc", sptrsv_csr_lbc_wrapper);

  def("build_set_levelset_csc", build_set_levelset_csc_wrapper);
  def("build_set_lbc_csr", build_set_lbc_csr_wrapper);
}