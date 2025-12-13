#include <iostream>
/*
Soal 2 : Faktorial Rekursif
Buatlah sebuah fungsi rekursif bernama faktorial() untuk menghitung faktorial. Program harus meminta input dari user dan menampilkan hasilnya.
Contoh fungsi rekursif (seperti pada PPT):
n! = n * (n-1)! , jika n > 1  
n! = 1 , jika n = 0 atau 1
Contoh Output:
Faktorial dari 4 adalah 24

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

    int result = factorial(n);
    std::cout << "Faktorial dari " << n << " adalah " << result << std::endl;

    return 0;
}