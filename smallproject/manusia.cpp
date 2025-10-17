#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Definisikan struct 'manusia'
struct manusia {
    string nama;
    int umur;

    // Fungsi makan
    void makan() {
        cout << nama << " sedang makan." << endl;
    }

    // Fungsi minum
    void minum() {
        cout << nama << " sedang minum." << endl;
    }
};

int main() {
    int jumlahManusia;

    // 1. Minta pengguna memasukkan jumlah manusia
    cout << "Masukkan jumlah manusia: ";
    cin >> jumlahManusia;

    // Buat vektor untuk menyimpan objek 'manusia'
    vector<manusia> daftarManusia(jumlahManusia);

    // 2. Lakukan perulangan untuk menginput data setiap manusia
    for (int i = 0; i < jumlahManusia; ++i) {
        cout << "\n--- Data Manusia ke-" << i + 1 << " ---" << endl;
        cout << "Nama: ";
        cin >> daftarManusia[i].nama; // Menggunakan cin >> untuk string sederhana
        cout << "Umur: ";
        cin >> daftarManusia[i].umur;
    }

    // 3. (Opsional) Menampilkan data dan memanggil fungsi
    cout << "\n--- Daftar Manusia ---" << endl;
    for (int i = 0; i < jumlahManusia; ++i) {
        cout << "Nama: " << daftarManusia[i].nama << ", Umur: " << daftarManusia[i].umur << endl;
        daftarManusia[i].makan();
        daftarManusia[i].minum();
    }

    return 0;
}