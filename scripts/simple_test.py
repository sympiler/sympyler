#!/usr/bin/python
# -*- coding: utf-8 -*-

import time

import numpy as np
import scipy.io
import scipy.sparse

from pylbc import *

A = scipy.io.mmread("../../data/af_0_k101.mtx").tocsc()
A = scipy.sparse.tril(A, format="csc")
b = scipy.io.mmread("../../data/b_dense_af_0_k101.mtx").reshape(-1)

A_CSC = CSC(*A.shape, A.nnz, A.indptr, A.indices, A.data)
A_CSR = csc_to_csr(A_CSC)
x1 = b.copy()
t0 = time.time()
sptrsv_csr(A_CSR, x1)
t1 = time.time()
print(x1)
print(f"Time used serial {t1-t0}")

x2 = b.copy()
t0 = time.time()
ret = build_set_levelset_csc(A_CSC)
t1 = time.time()
sptrsv_csr_levelset(A_CSR, x2, *ret)
t2 = time.time()
print(ret)
print(x2)
print(f"Time used levelset build_set {t1-t0}, solve {t2-t1}")

x3 = b.copy()
t0 = time.time()
ret = build_set_lbc_csr(A_CSR, 6, -1, 4000)
t1 = time.time()
sptrsv_csr_lbc(A_CSR, x3, *ret)
t2 = time.time()
print(x3)
print(ret)
print(f"Time used lbc build_set {t1-t0}, solve {t2-t1}")


