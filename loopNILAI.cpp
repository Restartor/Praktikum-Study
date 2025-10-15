// break loop example
#include <iostream>
using namespace std;

 /*int main() {
    for (char huruf = 'A'; huruf <= 'Z'; huruf++) {
        cout << huruf << " ";
        if (huruf == 'X') {
            cout << "Huruf X ditemukan, keluar dari loop." << endl;
            break; // exit the loop when huruf is 'E'
        }
    }


}*/

 // continue loop example

int main () {
    for (int nilai = 1; nilai <= 100; nilai++) {
        if (nilai == 65) {
            cout << "\nNilai 65 ditemukan, lanjut ke nilai berikutnya." << endl;
            continue; // skip the rest of the loop when nilai is 65
        }
        cout << nilai << " ";


    }
}