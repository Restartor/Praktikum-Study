#include <iostream>

using namespace std;

int main() {
    char nilai;
    cout << "Masukin Nilai kamu : ";
    cin >> nilai;

    switch (nilai) {
        case 'A':
            cout << "Kamu Lulus dengan Baik" << endl;
            break;
        case 'B':
            cout << "Kamu Lulus dengan Cukup" << endl;
            break;
        case 'C':
            cout << "Kamu Lulus dengan Kurang" << endl;
            break;
        case 'D':
            cout << "Kamu Hampir Tidak Lulus" << endl;
            break;
        case 'E':
            cout << "Kamu Tidak Lulus" << endl;
            break;
        default:
            cout << "Nilai yang kamu masukkan salah (A-E)" << endl;
            break;  
    }



    return 0;
}