#!/usr/bin/python3
# -*- coding: utf-8 -*-

from pynasoq import *

QPFC = QPFormatConverter()
if not QPFC.load_smp("../../nasoq/data/alligator1.yml"): exit(1)
QPFC.smp_to_ie()

diag_perturb = 1e-9;
eps = 1e-6;
inner_iter = 2;
stop_tol = 1e-15;
solver_mode = nasoq_mode.FIXED
max_iter_nas = 200000

solver = Nasoq(QPFC)

# update solver settings
solver.diag_perturb = diag_perturb
solver.eps_abs = eps
solver.max_iter = inner_iter
solver.stop_tol = stop_tol
solver.max_iter_nas = max_iter_nas

solver.solve()

print(solver.get_log())


# Here I'm getting copies the CSC and Dense matrices from the QPFormatConverter
# but they can also be directly instantiated from numpy arrays.
H = QPFC.get_H_copy()
A = QPFC.get_A_copy()
C = QPFC.get_C_copy()
q = QPFC.get_q_copy()
b = QPFC.get_b_copy()
d = QPFC.get_d_copy()

print(H)
print(q)

solver_from_matrix = Nasoq(H, q, A, b, C, d)

solver_from_matrix.diag_perturb = diag_perturb
solver_from_matrix.eps_abs = eps
solver_from_matrix.max_iter = inner_iter
solver_from_matrix.stop_tol = stop_tol
solver_from_matrix.max_iter_nas = max_iter_nas

solver_from_matrix.solve()
print(solver_from_matrix.get_log())