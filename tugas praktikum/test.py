from dataclasses import dataclass
@dataclass
class Dosen:
    nama: str
    nim : str

def tampilkan_dosen(dosen: Dosen):
    print(f"Nama Dosen: {dosen.nama}, NIM: {dosen.nim}")

input_nama = input("Masukkan nama dosen: ")
input_nim = input("Masukkan NIM dosen: ")

tampilkan_dosen(Dosen(nama=input_nama, nim=input_nim))

    