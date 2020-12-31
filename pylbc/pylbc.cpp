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

  class_<CSCWrapper>("CSC", "Compressed Sparse Column Format (CSC)",
                     init<size_t, size_t, size_t>(args("M", "N", "NNZ")))
    .def(init<size_t, size_t, size_t, bool>(args("M", "N", "NNZ", "ip")))
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, np::ndarray&>(
        args("M", "N", "NNZ", "Ap", "Ai", "Ax")
        ))
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, int>(
        args("M", "N", "NNZ", "Ap", "Ai", "st")
        ))
    .def_readonly("m",   &CSCWrapper::m)
    .def_readonly("n",   &CSCWrapper::n)
    .def_readonly("nnz", &CSCWrapper::nnz)
  ;

  class_<CSRWrapper>("CSR", "Compressed Sparse Row Format (CSR)",
                     init<size_t, size_t, size_t>(args("M", "N", "NNZ")))
    .def(init<size_t, size_t, size_t, bool>(args("M", "N", "NNZ", "ip")))
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, int>(
        args("M", "N", "NNZ", "Ap", "Ai", "st")
        ))
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
  def("transpose_symmetric", transpose_symmetric_1, return_value_policy<manage_new_object>(), args("test"), "test docstring");
  def("transpose_symmetric", transpose_symmetric_2, return_value_policy<manage_new_object>());

  def("csc_to_csr", csc_to_csr_wrapper, return_value_policy<manage_new_object>(),
      args("A"),
      "brief: Converts pylbc.CSC array to pylbc.CSR format\n"
      "param: A a pylbc.CSC object\n"
      "return: a pylbc.CSR object corresponding to input A"
      );

  def("metis_perm_general", metis_partition_general_wrapper,
      args("A"),
      "brief: Calculate permutation using metis\n"
      "param: A a pylbc.CSC object\n"
      "return: a numpy ndarray of type int"
      );

  def("sptrsv_csr", sptrsv_csr_wrapper,
      args("L", "b"),
      "brief: Serial sparse triangular solve\n"
      "param: L a pylbc.CSR object\n"
      "param: b a numpy ndarray of type double in which the R.H.S is passed in and the solution is returned"
      );

  def("sptrsv_csr_levelset", sptrsv_csr_levelset_wrapper,
      args("L", "b", "level_no", "level_ptr", "level_set"),
      "brief: Levelset sparse triangular solve\n"
      "param: L a pylbc.CSR object\n"
      "param: b a numpy ndarray of type double in which the R.H.S is passed in and the solution is returned\n"
      "param: level_no int number of levels\n"
      "param: level_ptr numpy ndarray of type int that contains indices of levels\n"
      "param: level_set numpy ndarray of type int that contains the level set of matrix L"
      );

  def("sptrsv_csr_lbc", sptrsv_csr_lbc_wrapper,
      args("L", "b", "level_no", "level_ptr", "part_ptr", "partition"),
      "brief: LBC sparse triangular solve\n"
      "param: L a pylbc.CSR object\n"
      "param: b a numpy ndarray of type double in which the R.H.S is passed in and the solution is returned\n"
      "param: level_no int\n"
      "param: level_ptr numpy ndarray of type int\n"
      "param: part_ptr numpy ndarray of type int\n"
      "return: partition numpy ndarray of type int"
      );

  def("build_set_levelset_csc", build_set_levelset_csc_wrapper,
      args("L"),
      "brief: Creates levelset from a pylbc.CSC matrix\n"
      "\n"
      "the matrix should form DAG i.e., no cycle. It returns -1 if\n"
      "the input graph has a cycle.\n"
      "param: L a pylbc.CSC object\n"
      "return: (level_no, level_ptr, level_set)\n"
      "return: level_no int number of levels\n"
      "return: level_ptr numpy ndarray of type int that contains indices of levels\n"
      "return: level_set numpy ndarray of type int that contains the level set of matrix L"
      );

  def("build_set_lbc_csr", build_set_lbc_csr_wrapper,
      args("L", "lp", "cp", "ic"),
      "brief: Creates coarse levelset DAG from a pylbc.CSC matrix\n"
      "param: L a pylbc.CSC object\n"
      "param: lp int\n"
      "param: cp int\n"
      "param: ic int\n"
      "return: (level_no, level_ptr, part_ptr, partition)\n"
      "return: level_no int\n"
      "return: level_ptr numpy ndarray of type int\n"
      "return: part_ptr numpy ndarray of type int\n"
      "return: partition numpy ndarray of type int"
      );
}