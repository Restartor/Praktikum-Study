#include <iostream>
#include <string>
using namespace std;

struct alamat {
    string kota;
    string provinsi;
};

struct mahasiswa {
    string nama;
    string nim;
    double ipk;
    alamat addr;
};

void inputMahasiswa(mahasiswa& m) {
    cout << "Masukkan Nama anda: ";
    getline(cin, m.nama);

    cout << "Masukkan NIM anda: ";
    getline(cin, m.nim);

    cout << "Masukkan Nilai IPK anda: ";
    cin >> m.ipk;

    cin.ignore();

    cout << "Masukkan Kota anda: ";
    getline(cin, m.addr.kota);

    cout << "Masukkan Provinsi anda: ";
    getline(cin, m.addr.provinsi);
}

void tampilMahasiswa(const mahasiswa& m, int idx) {
    cout << "====================================\n";
    cout << "Data Mahasiswa ke-" << idx << ":\n";
    cout << "Nama : " << m.nama << '\n';
    cout << "NIM  : " << m.nim  << '\n';
    cout << "IPK  : " << m.ipk  << '\n';
    cout << "Alamat : " << m.addr.kota << " Provinsi : "<< m.addr.provinsi << '\n';
}
void hitungRataRataIPK(const mahasiswa data[], int N) {
    double total = 0.0;
    for (int i = 0; i < N; ++i) {
        total += data[i].ipk;
    }
    double rata = (N > 0) ? total / N : 0.0;
    cout << "\nRata-rata IPK kelas: " << rata << '\n';
}

int main() {
    const int N = 3;
    mahasiswa data[N];

    int i = 0;
    do {
        cout << "Input Data Mahasiswa ke-" << (i+1) << '\n';
        inputMahasiswa(data[i]);
        i++; // dihitung dari 1 jika i = 0 maka akan bertambah hingga 3
    } while (i < N); // jika i sudah menjadi 3 maka stop dan rekap

    cout << "\n===== REKAP DATA MAHASISWA =====\n";
    for (int j = 0; j < N; ++j) {
        tampilMahasiswa(data[j], j+1);} // hasil dari sebuah syntax do

        cout << "=========================\n";

        hitungRataRataIPK(data, N); // memanggil ulang sebuah fungsi hitung rata rata

    return 0;
}
