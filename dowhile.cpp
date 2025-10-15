#include <iostream>
#include <string>
using namespace std;
 /*
int main() {
    int angka;

    {
    do {
      cout << "Masukkan angka (positive): ";
      cin >> angka;
    } while (angka <= 0);
    }
    cout << "Terima kasih! Anda memasukkan angka positif: " << angka << endl;


    return 0;
}*/
// melakukan codingan terlebih dahulu lalu jika benar maka akan lanjut ke proses selanjutnya
// jika salah maka akan mengulang proses tersebut hingga benar

int main () {
    int baris;
    int kolom;
    char symbols;

    cout << "Masukkan jumlah baris: ";
    cin >> baris;
    cout << "Masukkan jumlah kolom: ";
    cin >> kolom;
    cout << "Masukkan simbol yang diinginkan: ";
    cin >> symbols;

    for (int i = 1; i <= baris; i++) {
        for (int j = 1; j <= kolom; j++) {
            cout << symbols;
        }
        cout << '\n' ;
    }





    return 0;
}