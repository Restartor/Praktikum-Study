#include <iostream>
using namespace std;

struct Mahasiswa {
    int id;
    string nim;
    string nama;
    string mataKuliah;
};

int main() {
    Mahasiswa data[100];
    int total = 0;
    int autoID = 1;
    int pilihan;

    do {
        cout << "\nMENU SISTEM PERKULIAHAN\n";
        cout << "1. Tambah Data\n";
        cout << "2. Tampilkan Semua Data\n";
        cout << "3. Tampilkan Data Berdasarkan ID\n";
        cout << "4. Ubah Data Berdasarkan ID\n";
        cout << "5. Hapus Data Berdasarkan ID\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            data[total].id = autoID;
            cout << "NIM: ";
            cin >> data[total].nim;
            cout << "Nama: ";
            cin >> data[total].nama;
            cout << "Mata Kuliah: ";
            cin >> data[total].mataKuliah;

            total++;
            autoID++;

            cout << "Data berhasil ditambahkan\n";
        }

        else if (pilihan == 2) {
            if (total == 0) {
                cout << "Data kosong\n";
            } else {
                for (int i = 0; i < total; i++) {
                    cout << data[i].id << " "
                         << data[i].nim << " "
                         << data[i].nama << " "
                         << data[i].mataKuliah << endl;
                }
            }
        }

        else if (pilihan == 3) {
            int cariID;
            bool ditemukan = false;

            cout << "Masukkan ID: ";
            cin >> cariID;

            for (int i = 0; i < total; i++) {
                if (data[i].id == cariID) {
                    cout << data[i].id << " "
                         << data[i].nim << " "
                         << data[i].nama << " "
                         << data[i].mataKuliah << endl;
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                cout << "Data tidak ditemukan\n";
            }
        }

        else if (pilihan == 4) {
            int cariID;
            bool ditemukan = false;

            cout << "Masukkan ID: ";
            cin >> cariID;

            for (int i = 0; i < total; i++) {
                if (data[i].id == cariID) {
                    cout << "NIM baru: ";
                    cin >> data[i].nim;
                    cout << "Nama baru: ";
                    cin >> data[i].nama;
                    cout << "Mata Kuliah baru: ";
                    cin >> data[i].mataKuliah;
                    ditemukan = true;         
                    cout << "Data berhasil diubah\n";
                    break;
                }
            }

            if (!ditemukan) {
                cout << "Data tidak ditemukan\n";
            }
        }

        else if (pilihan == 5) {
            int cariID;
            bool ditemukan = false;

            cout << "Masukkan ID: ";
            cin >> cariID;

            for (int i = 0; i < total; i++) {
                if (data[i].id == cariID) {
                    for (int j = i; j < total - 1; j++) {
                        data[j] = data[j + 1];
                    }
                    total--;
                    ditemukan = true;
                    cout << "Data berhasil dihapus\n";
                    break;
                }
            }

            if (!ditemukan) {
                cout << "Data tidak ditemukan\n";
            }
        }

    } while (pilihan != 6);

    return 0;
}
