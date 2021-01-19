//
// Created by Shujian Qian on 2021-01-13.
//

#ifndef SYMPYLER_NASOQ_WRAPPER_H
#define SYMPYLER_NASOQ_WRAPPER_H

#include "nasoq/include/nasoq.h"

#include "pynasoq/includes/mp_format_converter_wrapper.h"

struct NasoqWrapper : public nasoq::Nasoq {
  NasoqWrapper(format::QPFormatConverter* QP)
      : nasoq::Nasoq (
      QP->ief_->H->n,QP->ief_->H->p,QP->ief_->H->i,QP->ief_->H->x,
      QP->ief_->q->a,QP->ief_->A->m,QP->ief_->A->n,QP->ief_->A->p,QP->ief_->A->i,
      QP->ief_->A->x,QP->ief_->b ? QP->ief_->b->a : NULLPNTR,
      QP->ief_->C->m,QP->ief_->C->n,QP->ief_->C->p,
      QP->ief_->C->i,QP->ief_->C->x,
      QP->ief_->d ? QP->ief_->d->a : NULLPNTR
  ) {}

  NasoqWrapper(
    CSCWrapper* H,
    DenseWrapper* q,
    CSCWrapper* A,
    DenseWrapper* b,
    CSCWrapper* C,
    DenseWrapper* d
  )
  : nasoq::Nasoq (
    H->n, H->p, H->i, H->x,
    q->a,
    A->m, A->n, A->p, A->i, A->x,
    b->a,
    C->m, C->n, C->p, C->i, C->x,
    d->a
  ) {}

  NasoqWrapper(
      CSCWrapper* H,
      DenseWrapper* q,
      CSCWrapper* A,
      CSCWrapper* C,
      DenseWrapper* d
  )
      : nasoq::Nasoq (
      H->n, H->p, H->i, H->x,
      q->a,
      A->m, A->n, A->p, A->i, A->x,
      NULLPNTR,
      C->m, C->n, C->p, C->i, C->x,
      d->a
  ) {}

  NasoqWrapper(
      CSCWrapper* H,
      DenseWrapper* q,
      CSCWrapper* A,
      DenseWrapper* b,
      CSCWrapper* C
  )
      : nasoq::Nasoq (
      H->n, H->p, H->i, H->x,
      q->a,
      A->m, A->n, A->p, A->i, A->x,
      b->a,
      C->m, C->n, C->p, C->i, C->x,
      NULLPNTR
  ) {}

  NasoqWrapper(
      CSCWrapper* H,
      DenseWrapper* q,
      CSCWrapper* A,
      CSCWrapper* C
  )
      : nasoq::Nasoq (
      H->n, H->p, H->i, H->x,
      q->a,
      A->m, A->n, A->p, A->i, A->x,
      NULLPNTR,
      C->m, C->n, C->p, C->i, C->x,
      NULLPNTR
  ) {}

  int solve_wrapper() {
    return nasoq::Nasoq::solve();
  }

  void print_log_wrapper() {
    nasoq::Nasoq::print_log();
  }
};

#endif //SYMPYLER_NASOQ_WRAPPER_H
