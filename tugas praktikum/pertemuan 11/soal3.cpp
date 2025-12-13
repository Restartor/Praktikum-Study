#include <iostream>
/*
Soal 3 : Deret Faktorial
Buatlah program C++ yang menampilkan deret faktorial dari 1 sampai n menggunakan fungsi rekursif.
Contoh Input:
Masukkan n: 5
Contoh Output:
1! = 1
2! = 2
3! = 6
4! = 24

*/

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    system("cls");
    int n;
    std::cout << "Masukkan n: ";
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        int result = factorial(i);
        std::cout << i << "! = " << result << std::endl;
    }

    return 0;
}