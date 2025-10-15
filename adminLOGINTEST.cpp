#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    double value = 123.456;
    cout << "The value is: " << value << endl;
    cout << "Masukkin Nama kamu : ";
    string halo, password;
    cin >> halo;
    cout << "Masukin Password kamu : ";
    cin >> password;

    cout << "Halo: " << halo << endl;
    if (halo == "rafi" && password == "admin123") {
        cout << "Kamu adalah admin" << endl;
    } else {
        cout << "Kamu bukan admin" << endl;
    }

    return 0;
}

