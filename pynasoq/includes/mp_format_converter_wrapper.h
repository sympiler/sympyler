//
// Created by Shujian Qian on 2021-01-13.
//

#ifndef SYMPYLER_MP_FORMAT_CONVERTER_WRAPPER_H
#define SYMPYLER_MP_FORMAT_CONVERTER_WRAPPER_H

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include "nasoq/smp-format/mp_format_converter.h"

#include "pynasoq/includes/def_wrapper.h"

namespace bp = boost::python;
namespace np = boost::python::numpy;

struct QPFormatConverterWrapper : public format::QPFormatConverter {
  bp::object get_H_copy() {
    this->smp_to_ie();
    return bp::object(new CSCWrapper(*(ief_->H)));
  }

  bp::object get_A_copy() {
    this->smp_to_ie();
    return bp::object(new CSCWrapper(*(ief_->A)));
  }

  bp::object get_C_copy() {
    this->smp_to_ie();
    return bp::object(new CSCWrapper(*(ief_->C)));
  }

  bp::object get_q_copy() {
    this->smp_to_ie();
    return bp::object(new DenseWrapper(*(ief_->q)));
  }

  bp::object get_b_copy() {
    this->smp_to_ie();
    return bp::object(new DenseWrapper(*(ief_->b)));
  }

  bp::object get_d_copy() {
    this->smp_to_ie();
    return bp::object(new DenseWrapper(*(ief_->d)));
  }
};

#endif //SYMPYLER_MP_FORMAT_CONVERTER_WRAPPER_H
