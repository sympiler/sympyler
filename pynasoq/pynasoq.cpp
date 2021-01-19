//
// Created by Shujian Qian on 2021-01-10.
//

#include <string>

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/manage_new_object.hpp>
#include <boost/python/return_value_policy.hpp>

#include "pynasoq/includes/def_wrapper.h"
#include "pynasoq/includes/nasoq_wrapper.h"
#include "pynasoq/includes/mp_format_converter_wrapper.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

BOOST_PYTHON_MODULE(pynasoq) {
  using namespace boost::python;

  class_<CSCWrapper>("CSC", "Compressed Sparse Column Format (CSC)",
                     init<size_t, size_t, size_t>(args("M", "N", "NNZ")))
    .def(init<size_t, size_t, size_t, bool>(args("M", "N", "NNZ", "ip")))
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, np::ndarray&>(
        args("M", "N", "NNZ", "Ap", "Ai", "Ax")
    ))
    .def(init<size_t, size_t, size_t, np::ndarray&, np::ndarray&, int>(
        args("M", "N", "NNZ", "Ap", "Ai", "st")
    ))
    .def("equality_check", &CSCWrapper::equality_check)
    .def_readonly("m",   &CSCWrapper::m)
    .def_readonly("n",   &CSCWrapper::n)
    .def_readonly("nnz", &CSCWrapper::nnz)
  ;

  class_<DenseWrapper>("Dense", init<size_t, size_t, size_t>())
    .def(init<size_t, size_t, size_t, double>())
    .def(init<const DenseWrapper&>())
    .def("equality_check", &DenseWrapper::equality_check)
    .def("is_finite",      &DenseWrapper::is_finite)
    .def_readonly("row", &DenseWrapper::row)
    .def_readonly("col", &DenseWrapper::col)
    .def_readonly("lda", &DenseWrapper::lda)
  ;

  class_<format::QPFormatConverter>("QPFormatConverter")
    .def("load_smp",  &format::QPFormatConverter::load_smp)
    .def("smp_to_ie", &format::QPFormatConverter::smp_to_ie)
  ;

  enum_<nasoq::nasoq_mode>("nasoq_mode")
    .value("FIXED",  nasoq::nasoq_mode::Fixed)
    .value("AUTO",   nasoq::nasoq_mode::AUTO)
    .value("TUNED",  nasoq::nasoq_mode::Tuned)
    .value("PREDET", nasoq::nasoq_mode::PREDET)
  ;

  enum_<nasoq::nasoq_status>("nasoq_status")
    .value("Optimal",      nasoq::nasoq_status::Optimal)
    .value("Inaccurate",   nasoq::nasoq_status::Inaccurate)
    .value("NotConverged", nasoq::nasoq_status::NotConverged)
    .value("Infeasible",   nasoq::nasoq_status::Infeasible)
    .value("NotFinished",  nasoq::nasoq_status::NotFinished)
  ;

  class_<NasoqWrapper>("Nasoq", init<format::QPFormatConverter*>(args("QP")))
    .def(init<CSCWrapper*, DenseWrapper*, CSCWrapper*, DenseWrapper*, CSCWrapper*, DenseWrapper*>())
    .def(init<CSCWrapper*, DenseWrapper*, CSCWrapper*, CSCWrapper*, DenseWrapper*>())
    .def(init<CSCWrapper*, DenseWrapper*, CSCWrapper*, DenseWrapper*, CSCWrapper*>())
    .def(init<CSCWrapper*, DenseWrapper*, CSCWrapper*, CSCWrapper*>())
    .def("solve",     &NasoqWrapper::solve_wrapper)
    .def("print_log", &NasoqWrapper::print_log_wrapper)

    .def_readwrite("diag_perturb", &NasoqWrapper::diag_perturb)
    .def_readwrite("eps_abs",      &NasoqWrapper::eps_abs)
    .def_readwrite("max_iter",     &NasoqWrapper::max_iter)
    .def_readwrite("stop_tol",     &NasoqWrapper::stop_tol)
    .def_readwrite("max_iter_nas", &NasoqWrapper::max_iter_nas)
    .def_readwrite("variant",      &NasoqWrapper::variant)
  ;
}