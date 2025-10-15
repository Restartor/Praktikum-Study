#include <iostream>
using namespace std;


 // Untuk mempelajari && (AND) || (OR) operator dan ! (NOT) operator
 
int main() {
    int temperature;
    bool isRaining = false;

    cout << "Masukkan suhu dalam derajat Celsius: ";
    cin >> temperature;

    isRaining = (temperature < 15); // contoh penggunaan !
    // isRaining akan true jika suhu < 20, false jika suhu >= 20

    if (temperature < 0) {
        cout << "Suhu sangat dingin! Pakailah jaket tebal." << endl;

    } else if (temperature >= 0 && temperature < 15) {
        cout << "Suhu dingin. Pakailah pakaian hangat." << endl;

    } else if (temperature >= 15 && temperature < 25) {
        cout << "Suhu sedang. Pakaian biasa sudah cukup." << endl;

    } else if (temperature >= 25 && temperature < 35) {
        cout << "Suhu hangat. Pakailah pakaian ringan." << endl;
    }
    if (!isRaining) {
        cout << "Tidak hujan hari ini. Nikmati harimu!" << endl;
    }
    else {
        cout << "Bawa payung atau jas hujan!" << endl;
    }


    return 0;
}

// PENJELASAN PENTING VOCABULARY TSB SERING DIGUNAKAN DALAM PEMROGRAMAN
// && (AND) operator: digunakan untuk menggabungkan dua kondisi, true jika kedua kondisi benar
// || (OR) operator: digunakan untuk menggabungkan dua kondisi, true jika salah satu kondisi benar
// ! (NOT) operator: digunakan untuk membalik nilai boolean, true menjadi false dan sebaliknya
// Untuk mengetahui System otomatis menyesuaikan dengan kondisi tertentu yang diberikan

// if(temperature < 0) { ... }: kondisi pertama, jika suhu di bawah 0 derajat
// else if(temperature >= 0 && temperature <15) { ... }: kondisi kedua, jika suhu antara 0 dan 15 derajat
// else if(temperature >= 15 && temperature < 25) { ... }: kondisi ketiga, jika suhu antara 15 dan 25 derajat
// else if(temperature >= 25 && temperature < 35) { ... }: kondisi keempat, jika suhu antara 25 dan 35 derajat
// if(!isRaining) { ... }: kondisi tambahan, jika tidak hujan (isRaining false)
// else { ... }: kondisi tambahan, jika hujan (isRaining true)
// cout << "Pesan ...": menampilkan pesan sesuai kondisi suhu dan cuaca
// return 0;: mengakhiri program dengan kode sukses
// int main() { ... }: fungsi utama tempat program dimulai