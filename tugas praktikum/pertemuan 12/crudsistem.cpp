#include <iostream>
#include <string>
using namespace std;
/*STRUKTUR Mahasiswa
    id      : integer
    nim     : integer
    nama    : string
    jurusan : string
AKHIR STRUKTUR
*/
struct Mahasiswa {
    int id;
    int nim;
    string nama;
    string jurusan;
};
/*PROSEDUR TambahData(data, total, autoID)
    JIKA total >= 100 MAKA
        TAMPILKAN "Kapasitas data penuh"
        KEMBALI
    AKHIR JIKA

    data[total].id ← autoID
    INPUT data[total].nim
    INPUT data[total].nama
    INPUT data[total].jurusan

    total ← total + 1
    autoID ← autoID + 1

    TAMPILKAN "Data berhasil ditambahkan"
AKHIR PROSEDUR
*/
void tambahData(Mahasiswa data[], int &total, int &autoID) {
    if (total >= 100) {
        cout << "Kapasitas data penuh\n";
        return;
    }
    data[total].id = autoID;
    cout << "NIM: ";
    cin >> data[total].nim;
    cout << "Nama: ";
    cin >> data[total].nama;
    cout << "Jurusan: ";
    cin >> data[total].jurusan;

    total++;
    autoID++;
    cout << "Data berhasil ditambahkan\n";
}
/*PROSEDUR TampilkanSemuaData(data, total)
    JIKA total = 0 MAKA
        TAMPILKAN "Data kosong"
        KEMBALI
    AKHIR JIKA

    UNTUK i ← 0 SAMPAI total - 1 LAKUKAN
        TAMPILKAN data[i].id, data[i].nim, data[i].nama, data[i].jurusan
    AKHIR UNTUK
AKHIR PROSEDUR
*/
void showAllData(Mahasiswa data[], int total) {
    if (total == 0) {
        cout << "Data kosong\n";
        return;
    }
    for (int i = 0; i < total; i++) {
        cout << data[i].id << " "
             << data[i].nim << " "
             << data[i].nama << " "
             << data[i].jurusan << endl;
    }
}
/*PROSEDUR TampilkanDataByID(data, total)
    ditemukan ← SALAH
    INPUT cariID

    UNTUK i ← 0 SAMPAI total - 1 LAKUKAN
        JIKA data[i].id = cariID MAKA
            TAMPILKAN data[i].id, data[i].nim, data[i].nama, data[i].jurusan
            ditemukan ← BENAR
            HENTIKAN PERULANGAN
        AKHIR JIKA
    AKHIR UNTUK

    JIKA ditemukan = SALAH MAKA
        TAMPILKAN "Data tidak ditemukan"
    AKHIR JIKA
AKHIR PROSEDUR
*/
void showDataById(Mahasiswa data[], int total) {
    int cariID;
    bool ditemukan = false;
    cout << "Masukkan ID: ";
    cin >> cariID;
    for (int i = 0; i < total; i++) {
        if (data[i].id == cariID) {
            cout << data[i].id << " "
                 << data[i].nim << " "
                 << data[i].nama << " "
                 << data[i].jurusan << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Data tidak ditemukan\n";
    }
}
/*PROSEDUR UbahDataByID(data, total)
    ditemukan ← SALAH
    INPUT cariID

    UNTUK i ← 0 SAMPAI total - 1 LAKUKAN
        JIKA data[i].id = cariID MAKA
            INPUT data[i].nim
            INPUT data[i].nama
            INPUT data[i].jurusan
            ditemukan ← BENAR
            TAMPILKAN "Data berhasil diubah"
            HENTIKAN PERULANGAN
        AKHIR JIKA
    AKHIR UNTUK

    JIKA ditemukan = SALAH MAKA
        TAMPILKAN "Data tidak ditemukan"
    AKHIR JIKA
AKHIR PROSEDUR
*/
void ubahDataById(Mahasiswa data[], int total) {
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
            cout << "Jurusan baru: ";
            cin >> data[i].jurusan;
            ditemukan = true;
            cout << "Data berhasil diubah\n";
            break;
        }
    }
    if (!ditemukan) {
        cout << "Data tidak ditemukan\n";
    }
}
/*PROSEDUR HapusDataByID(data, total)
    ditemukan ← SALAH
    INPUT cariID

    UNTUK i ← 0 SAMPAI total - 1 LAKUKAN
        JIKA data[i].id = cariID MAKA
            UNTUK j ← i SAMPAI total - 2 LAKUKAN
                data[j] ← data[j + 1]
            AKHIR UNTUK

            total ← total - 1
            ditemukan ← BENAR
            TAMPILKAN "Data berhasil dihapus"
            HENTIKAN PERULANGAN
        AKHIR JIKA
    AKHIR UNTUK

    JIKA ditemukan = SALAH MAKA
        TAMPILKAN "Data tidak ditemukan"
    AKHIR JIKA
AKHIR PROSEDUR
*/
void hapusDataById(Mahasiswa data[], int &total) {
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
/*
MULAI
    DEKLARASI data[100] SEBAGAI Mahasiswa
    total ← 0
    autoID ← 1

    ULANGI
        TAMPILKAN "MENU SISTEM PERKULIAHAN"
        TAMPILKAN "1. Tambah Data"
        TAMPILKAN "2. Tampilkan Semua Data"
        TAMPILKAN "3. Tampilkan Data Berdasarkan ID"
        TAMPILKAN "4. Ubah Data Berdasarkan ID"
        TAMPILKAN "5. Hapus Data Berdasarkan ID"
        TAMPILKAN "6. Keluar"

        INPUT pilihan

        PILIH pilihan
            KASUS 1:
                TambahData(data, total, autoID)
            KASUS 2:
                TampilkanSemuaData(data, total)
            KASUS 3:
                TampilkanDataByID(data, total)
            KASUS 4:
                UbahDataByID(data, total)
            KASUS 5:
                HapusDataByID(data, total)
            KASUS 6:
                SELESAI
            LAINNYA:
                TAMPILKAN "Pilihan tidak valid"
        AKHIR PILIH

    SELAMA pilihan ≠ 6
SELESAI

*/
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

        switch (pilihan) {
            case 1:
                tambahData(data, total, autoID);
                break;
            case 2:
                showAllData(data, total);
                break;
            case 3:
                showDataById(data, total);
                break;
            case 4:
                ubahDataById(data, total);
                break;
            case 5:
                hapusDataById(data, total);
                break;
            case 6:
                break;
            default:
                cout << "Pilihan tidak valid\n";
                break;
        }

    } while (pilihan != 6);

    return 0;
}
