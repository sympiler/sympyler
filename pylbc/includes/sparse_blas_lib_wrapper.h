//
// Created by Shujian Qian on 2020-12-26.
//

#ifndef SYMPYLER_SPARSE_BLAS_LIB_WRAPPER_H
#define SYMPYLER_SPARSE_BLAS_LIB_WRAPPER_H

#include <string>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "lbc/lbc/includes/lbc.h"
#include "lbc/example/sparse_blas_lib.h"
#include "lbc/utils/includes/sparse_inspector.h"

#include "pylbc/includes/defwrappers.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

void sptrsv_csr_wrapper (CSRWrapper& L, np::ndarray& b) {
  sym_lib::sptrsv_csr(L.n, L.p, L.i, L.x, reinterpret_cast<double*>(b.get_data()));
}

void sptrsv_csr_levelset_wrapper (
  CSRWrapper& L, np::ndarray& b,
  int level_no, np::ndarray& level_ptr,
  np::ndarray& level_set
) {
  sym_lib::sptrsv_csr_levelset(
    L.n, L.p, L.i, L.x,
    reinterpret_cast<double*>(b.get_data()),
    level_no,
    reinterpret_cast<int*>(level_ptr.get_data()),
    reinterpret_cast<int*>(level_set.get_data())
  );
}

void sptrsv_csr_lbc_wrapper (
  CSRWrapper& L, np::ndarray& b,
  int level_no,
  np::ndarray& level_ptr,
  np::ndarray& part_ptr,
  np::ndarray& partition
) {
  sym_lib::sptrsv_csr_lbc(
    L.n, L.p, L.i, L.x,
    reinterpret_cast<double*>(b.get_data()),
    level_no,
    reinterpret_cast<int*>(level_ptr.get_data()),
    reinterpret_cast<int*>(part_ptr.get_data()),
    reinterpret_cast<int*>(partition.get_data())
  );
}

boost::python::tuple build_set_levelset_csc_wrapper (CSCWrapper& L) {
  int* level_set,* level_ptr;
  int level_no;
  CSC* L_csc = static_cast<CSC*>(&L);
  level_no = sym_lib::build_levelSet_CSC(L_csc->n, L_csc->p, L_csc->i,
                                         level_ptr, level_set);

  // Create a boost python handle (smart pointer) to automatically delete
  // dynamically allocated C array.
  bp::handle<> h_set(::PyCapsule_New(
      (void*) level_set, nullptr,
      (PyCapsule_Destructor) &destroy_manager_carray<int>)
  );

  bp::handle<> h_ptr(::PyCapsule_New(
      (void*) level_ptr, nullptr,
      (PyCapsule_Destructor) &destroy_manager_carray<int>)
  );

  np::dtype dt = np::dtype::get_builtin<int>();
  bp::tuple shape_set = bp::make_tuple(L_csc->n);
  bp::tuple shape_ptr = bp::make_tuple(L_csc->n + 1);
  bp::tuple stride = bp::make_tuple(sizeof(int));

  // Create numpy ndarray from dynamically allocated C array and set a boost
  // python object with previously defined handle as owner.
  np::ndarray level_set_arr = np::from_data(level_set, dt, shape_set, stride, bp::object(h_set));
  np::ndarray level_ptr_arr = np::from_data(level_ptr, dt, shape_ptr, stride, bp::object(h_ptr));

  // Create a Python tuple that holds the objects to be returned.
  return bp::make_tuple(level_no, level_ptr_arr, level_set_arr);
}

///
/// \param L
/// \param lp num_threads
/// \param cp p2
/// \param ic p3
/// \return
bp::tuple build_set_lbc_csr_wrapper (CSRWrapper& L, int lp, int cp, int ic) {
  int final_level_no, *fina_level_ptr, *final_part_ptr, *final_node_ptr;
  int part_no;
  CSR* L_csr = static_cast<CSR*>(&L);
  int n = L_csr->n;
  auto *cost = new double[n]();
  for (int i = 0; i < n; ++i) {
  cost[i] = L_csr->p[i+1] - L_csr->p[i];
  }

  sym_lib::get_coarse_levelSet_DAG_CSC_tree(n, L_csr->p, L_csr->i,
                                            final_level_no,
                                            fina_level_ptr,part_no,
                                            final_part_ptr,final_node_ptr,
                                            lp,cp, ic, cost);
  delete []cost;

  // Create a boost python handle (smart pointer) to automatically delete
  // dynamically allocated C array.
  bp::handle<> h_part(::PyCapsule_New(
      (void*) final_part_ptr, nullptr,
      (PyCapsule_Destructor) &destroy_manager_carray<int>)
  );
  bp::handle<> h_node(::PyCapsule_New(
      (void*) final_node_ptr, nullptr,
      (PyCapsule_Destructor) &destroy_manager_carray<int>)
  );
  bp::handle<> h_ptr(::PyCapsule_New(
      (void*) fina_level_ptr, nullptr,
      (PyCapsule_Destructor) &destroy_manager_carray<int>)
  );

  np::dtype dt = np::dtype::get_builtin<int>();
  bp::tuple shape_part_node = bp::make_tuple(L_csr->n);
  bp::tuple shape_ptr = bp::make_tuple(L_csr->n + 1);
  bp::tuple stride = bp::make_tuple(sizeof(int));

  // Create numpy ndarray from dynamically allocated C array and set a boost
  // python object with previously defined handle as owner.
  np::ndarray final_part_ptr_arr = np::from_data(final_part_ptr, dt, shape_part_node, stride, bp::object(h_part));
  np::ndarray final_node_ptr_arr = np::from_data(final_node_ptr, dt, shape_part_node, stride, bp::object(h_node));
  np::ndarray final_level_ptr_arr = np::from_data(fina_level_ptr, dt, shape_ptr, stride, bp::object(h_ptr));

  // Create a Python tuple that holds the objects to be returned.
  return bp::make_tuple(final_level_no, final_level_ptr_arr, final_part_ptr_arr, final_node_ptr_arr);
}

#endif //SYMPYLER_SPARSE_BLAS_LIB_WRAPPER_H
