import os
from os import system

system("clear")

# Fuzzy Tsukamoto: Produksi CPU

min_req, max_req = 200, 1000
min_stock, max_stock = 20, 120
min_prod, max_prod = 400, 1400

# Input
req = float(input("Permintaan (200-1000): "))
stock = float(input("Persediaan (20-120): "))

# Derajat keanggotaan
mu_T = (max_req - req) / (max_req - min_req)
mu_N = (req - min_req) / (max_req - min_req)
mu_S = (max_stock - stock) / (max_stock - min_stock)
mu_B = (stock - min_stock) / (max_stock - min_stock)

# Alpha (aturan: T&B→BR, N&S→BT, N&B→BT, T&S→BR)
a1, a2, a3, a4 = min(mu_T, mu_B), min(mu_N, mu_S), min(mu_N, mu_B), min(mu_T, mu_S)

# z per aturan
z1, z4 = max_prod - a1*(max_prod-min_prod), max_prod - a4*(max_prod-min_prod)
z2, z3 = min_prod + a2*(max_prod-min_prod), min_prod + a3*(max_prod-min_prod)

# Defuzzifikasi
z_star = (a1*z1 + a2*z2 + a3*z3 + a4*z4) / (a1 + a2 + a3 + a4)

print(f"Produksi disarankan: {z_star:.0f} unit/hari")