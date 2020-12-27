#!/usr/bin/python
# -*- coding: <encoding name> -*-
import numpy as np
import scipy.io
import scipy.sparse

from pylbc import *

A = scipy.io.mmread("../../data/af_0_k101.mtx").tocsc()
b = scipy.io.mmread("../../data/b_dense_af_0_k101.mtx").reshape(-1)
A = scipy.sparse.tril(A, format="csc")

A_CSC = CSC(*A.shape, A.nnz, A.indptr, A.indices, A.data)
A_CSR = csc_to_csr(A_CSC)
sptrsv_csr(A_CSR, b)

print(b)



