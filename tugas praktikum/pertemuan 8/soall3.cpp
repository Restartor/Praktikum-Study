#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isOpeningBracket(char c) {
    return (c == '(' || c == '{' || c == '[');
}

bool isClosingBracket(char c) {
    return (c == ')' || c == '}' || c == ']');
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

void checkBracketValidity() {
    string ekspresi;
    cout << "Masukkan ekspresi matematika: ";
    getline(cin, ekspresi);

    stack<char> st;
    bool valid = true;

    for (char c : ekspresi) {
        if (isOpeningBracket(c)) {
            st.push(c);
        } else if (isClosingBracket(c)) {
            if (st.empty()) {
                valid = false; // ada kurung tutup tapi tidak ada pasangannya
                break;
            }
            char topChar = st.top();
            st.pop();
            if (!isMatchingPair(topChar, c)) {
                valid = false; // jenis kurung tidak cocok
                break;
            }
        }
        // karakter lain (angka, +, -, dsb) diabaikan
    }

    // jika masih ada kurung buka tersisa, maka tidak valid
    if (!st.empty()) {
        valid = false;
    }

    if (valid) {
        cout << "Valid\n";
    } else {
        cout << "Tidak Valid\n";
    }
}

int main() {
    checkBracketValidity();
    return 0;
}
