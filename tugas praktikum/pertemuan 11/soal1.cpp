#include <iostream>

/*
Soal 1 : Faktorial Iteratif
Buatlah program C++ menggunakan looping (for/while) untuk menghitung faktorial dari sebuah bilangan n yang dimasukkan oleh user.
Contoh Input:
Masukkan n: 5
Contoh Output:
5! = 120

*/

int main() {
    int n;
    std::cout << "Masukkan n: ";
    std::cin >> n;

    int factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }

    std::cout << n << "! = " << factorial << std::endl;

    return 0;
}