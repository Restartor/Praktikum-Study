from itertools import product
import os
from os import system

system("clear")

def eval_sop(expr, vars):
    X, Y, Z = vars
    return eval(expr)

def truth_table(expr):
    print(f"\nTabel kebenaran: {expr}")
    print("X Y Z | F")
    for X, Y, Z in product([0,1], repeat=3):
        val = eval_sop(expr, (X, Y, Z))
        print(f"{X} {Y} {Z} | {int(val)}")

# Soal a
F_a_simplified = "(Y and Z) or (X and not Z)"
print("a) F = YZ + XZ'")
truth_table(F_a_simplified)

# Soal b
F_b_simplified = "Z or (X and not Y)"
print("\nb) F = Z + XY'")
truth_table(F_b_simplified)

# Soal c
F_c_simplified = "(not Z) or (X and not Y)"
print("\nc) F = Z' + XY'")
truth_table(F_c_simplified)

# Verifikasi minterm soal a: Σm(3,4,6,7)
def minterms_to_expr(minterms):
    terms = []
    for m in minterms:
        X, Y, Z = (m>>2)&1, (m>>1)&1, m&1
        term = []
        if X==0: term.append("not X")
        elif X==1: term.append("X")
        if Y==0: term.append("not Y")
        elif Y==1: term.append("Y")
        if Z==0: term.append("not Z")
        elif Z==1: term.append("Z")
        terms.append(" and ".join(term))
    return " or ".join(terms)

print("\nVerifikasi soal a minterms (3,4,6,7):")
orig_a = minterms_to_expr([3,4,6,7])
print("Original SOP:", orig_a)
truth_table(orig_a)
print("Hasil sama dengan F = YZ + XZ'")