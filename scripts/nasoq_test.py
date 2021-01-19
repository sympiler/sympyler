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

solver.print_log()