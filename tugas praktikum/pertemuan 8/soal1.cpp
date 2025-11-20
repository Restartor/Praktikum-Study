#include <iostream>
using namespace std;

struct Stack {
    int *data;
    int top;
    int capacity;
};

void initStack(Stack &s, int cap) {
    s.capacity = cap;
    s.data = new int[cap];
    s.top = -1;
}

bool isEmpty(const Stack &s) {
    return s.top == -1;
}

bool isFull(const Stack &s) {
    return s.top == s.capacity - 1;
}

void push(Stack &s) {
    if (isFull(s)) {
        cout << "Stack penuh! Tidak bisa menambahkan data.\n";
        return;
    }
    int value;
    cout << "Masukkan nilai yang akan di-push: ";
    cin >> value;

    s.top++;
    s.data[s.top] = value;
    cout << "Data " << value << " berhasil di-push ke stack.\n";
}

void pop(Stack &s) {
    if (isEmpty(s)) {
        cout << "Stack kosong! Tidak ada data yang bisa di-pop.\n";
        return;
    }
    int value = s.data[s.top];
    s.top--;
    cout << "Data " << value << " berhasil di-pop dari stack.\n";
}

void peek(const Stack &s) {
    if (isEmpty(s)) {
        cout << "Stack kosong! Tidak ada elemen di puncak.\n";
        return;
    }
    cout << "Elemen paling atas (peek): " << s.data[s.top] << endl;
}

void printIsEmpty(const Stack &s) {
    if (isEmpty(s)) {
        cout << "Stack kosong.\n";
    } else {
        cout << "Stack TIDAK kosong.\n";
    }
}

void printSize(const Stack &s) {
    cout << "Jumlah elemen dalam stack: " << (s.top + 1) << endl;
}

// TOTAL semua elemen stack
void printTotal(const Stack &s) {
    if (isEmpty(s)) {
        cout << "Stack kosong, total = 0.\n";
        return;
    }

    int total = 0;
    for (int i = 0; i <= s.top; i++) {
        total += s.data[i];
    }

    cout << "Total semua elemen di dalam stack: " << total << endl;
}

void showMenu() {
    cout << "\n=== PROGRAM STACK DENGAN ARRAY ===\n";
    cout << "1. Push\n";
    cout << "2. Pop\n";
    cout << "3. Peek\n";
    cout << "4. IsEmpty\n";
    cout << "5. Size\n";
    cout << "6. Total semua elemen stack\n";
    cout << "7. Exit\n";
}

void runStackProgram() {
    int cap;
    cout << "Masukkan kapasitas maksimum stack: ";
    cin >> cap;

    Stack s;
    initStack(s, cap);

    while (true) {
        showMenu();
        cout << "Pilih menu [1-7]: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: 
                push(s); 
                break;
            case 2: 
                pop(s); 
                break;
            case 3: 
                peek(s); 
                break;
            case 4: 
                printIsEmpty(s); 
                break;
            case 5: 
                printSize(s); 
                break;
            case 6: 
                printTotal(s); 
                break;
            case 7: 
                cout << "Keluar dari program.\n";
                delete[] s.data;      // bersihin semua data stack
                return;              
            default:
                cout << "Pilihan tidak valid!\n";
                break;
        }
    }
}

int main() {
    runStackProgram();
    return 0;
}
