#!/usr/bin/python
# -*- coding: <encoding name> -*-
import numpy as np
import scipy.io
import scipy.sparse

from pylbc import *

A = scipy.io.mmread("../../data/test_A.mtx").tocsc()
A = scipy.sparse.tril(A, format="csc")
b = scipy.io.mmread("../../data/test_b.mtx").reshape(-1)

A_CSC = CSC(*A.shape, A.nnz, A.indptr, A.indices, A.data)
A_CSR = csc_to_csr(A_CSC)
x1 = b.copy()
sptrsv_csr(A_CSR, x1)
print(x1)

x2 = b.copy()
ret = build_set_levelset_csc(A_CSC)
sptrsv_csr_levelset(A_CSR, x2, *ret)
print(x2)

x3 = b.copy()
ret = build_set_lbc_csr(A_CSR, 6, -1, 4000)
sptrsv_csr_lbc(A_CSR, x3, *ret)
print(x3)



