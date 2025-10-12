#include <iostream>
using namespace std;

int main () {
    char kalkulator;
    double num1;
    double num2;
    double hasil;

    cout << "************ KALKULATOR ************\n";

    cout << "Masukkan Bilangan (+, -, *, /): ";
    cin >> kalkulator;

    cout << "Masukkan Bilangan Pertama: ";
    cin >> num1;

    cout << "Masukkan Bilangan Kedua: ";
    cin >> num2;

    cout << "Hasil: \n";

    switch (kalkulator) {
        case '+':
            hasil = num1 + num2;
            cout << num1 << " + " << num2 << " = " << hasil << endl;
            break;
        case '-':
            hasil = num1 - num2;
            cout << num1 << " - " << num2 << " = " << hasil << endl;
            break;
        case '*':
            hasil = num1 * num2;
            cout << num1 << " * " << num2 << " = " << hasil << endl;
            break;
        case '/':
            hasil = num1 / num2;
            cout << num1 << " / " << num2 << " = " << hasil << endl;
            break;
        default:
            cout << "Bilangan yang kamu masukkan salah (+, -, *, /)" << endl;
            break;
    }



        cout << "******************************";

    return 0;
}