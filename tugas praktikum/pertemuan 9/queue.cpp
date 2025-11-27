#include <iostream>
#include <string> // buat pakai std::string
using namespace std;

//////////////////////////////
// SOAL 1 - QUEUE INTEGER  //
//////////////////////////////

const int MAX_INT = 10;

struct IntQueue {
    int data[MAX_INT];
    int front;
    int rear;
    int count;
};

void initIntQueue(IntQueue &q) {
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool isEmptyInt(const IntQueue &q) {
    return q.count == 0;
}

bool isFullInt(const IntQueue &q) {
    return q.count == MAX_INT;
}

void enqueueInt(IntQueue &q, int value) {
    if (isFullInt(q)) {
        cout << "Queue penuh! Tidak bisa enqueue.\n";
        return;
    }
    q.rear++;
    q.data[q.rear] = value;
    q.count++;
    cout << "Enqueue: " << value << endl;
}

int dequeueInt(IntQueue &q) {
    if (isEmptyInt(q)) {
        cout << "Queue kosong! Tidak bisa dequeue.\n";
        return -1;
    }
    int value = q.data[q.front];
    q.front++;
    q.count--;
    cout << "Dequeue: " << value << endl;
    return value;
}

void displayIntQueue(const IntQueue &q) {
    if (isEmptyInt(q)) {
        cout << "Queue kosong.\n";
        return;
    }
    cout << "Isi queue: ";
    for (int i = 0; i < q.count; i++) {
        cout << q.data[q.front + i] << " ";
    }
    cout << endl;
}

void runSoal1() {
    IntQueue q;
    initIntQueue(q);

    int pilihan, nilai;

    do {
        cout << "\n=== SOAL 1 - QUEUE INTEGER ===\n";
        cout << "1. Enqueue (tambah data)\n";
        cout << "2. Dequeue (hapus data)\n";
        cout << "3. Tampilkan isi queue\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            cout << "Masukkan nilai integer: ";
            cin >> nilai;
            enqueueInt(q, nilai);
            break;
        case 2:
            dequeueInt(q);
            break;
        case 3:
            displayIntQueue(q);
            break;
        case 4:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 4);
}

//////////////////////////////
// SOAL 2 - QUEUE CHAR     //
//////////////////////////////

const int MAX_CHAR = 10;

struct CharQueue {
    char data[MAX_CHAR];
    int front;
    int rear;
};

void initCharQueue(CharQueue &q) {
    q.front = -1;
    q.rear = -1;
}

bool is_empty_char(const CharQueue &q) {
    return q.front == -1;
}

bool is_full_char(const CharQueue &q) {
    return q.rear == MAX_CHAR - 1;
}

void insert_char(CharQueue &q, char c) {
    if (is_full_char(q)) {
        cout << "Queue penuh! Tidak bisa insert.\n";
        return;
    }
    if (is_empty_char(q)) {
        q.front = 0;
    }
    q.rear++;
    q.data[q.rear] = c;
}

char remove_char(CharQueue &q) {
    if (is_empty_char(q)) {
        cout << "Queue kosong! Tidak bisa remove.\n";
        return '\0';
    }
    char c = q.data[q.front];
    if (q.front == q.rear) {
        q.front = q.rear = -1;
    } else {
        q.front++;
    }
    return c;
}

void displayCharQueue(const CharQueue &q) {
    if (is_empty_char(q)) {
        cout << "Queue kosong.\n";
        return;
    }
    cout << "Isi queue: ";
    for (int i = q.front; i <= q.rear; i++) {
        cout << q.data[i] << " ";
    }
    cout << endl;
}

// >>> Soal 2 sekarang interaktif pakai string sendiri <<<
void runSoal2() {
    CharQueue q;
    initCharQueue(q);

    int pilihan;
    do {
        cout << "\n=== SOAL 2 - QUEUE CHARACTER ===\n";
        cout << "1. Isi queue dengan string\n";
        cout << "2. Remove 1 karakter dari queue\n";
        cout << "3. Tampilkan isi queue\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            string kata;
            cout << "Masukkan string (contoh: ARIF): ";
            cin >> kata; // tanpa spasi
            for (size_t i = 0; i < kata.size(); i++) {
                insert_char(q, kata[i]);
            }
            cout << "String dimasukkan ke queue (per karakter).\n";
            break;
        }
        case 2: {
            char c = remove_char(q);
            if (c != '\0') {
                cout << "Remove: " << c << endl;
            }
            break;
        }
        case 3:
            displayCharQueue(q);
            break;
        case 4:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 4);
}

//////////////////////////////
// SOAL 3 - CIRCULAR QUEUE //
//////////////////////////////

const int MAX_CIRC = 5; // contoh kapasitas 5

struct CQueue {
    int data[MAX_CIRC];
    int front;
    int rear;
    int count;
};

void initCQueue(CQueue &q) {
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool isEmptyC(const CQueue &q) {
    return q.count == 0;
}

bool isFullC(const CQueue &q) {
    return q.count == MAX_CIRC;
}

void enqueueC(CQueue &q, int value) {
    if (isFullC(q)) {
        cout << "Circular queue penuh!\n";
        return;
    }
    q.rear = (q.rear + 1) % MAX_CIRC;
    q.data[q.rear] = value;
    q.count++;
}

int dequeueC(CQueue &q) {
    if (isEmptyC(q)) {
        cout << "Circular queue kosong!\n";
        return -1;
    }
    int value = q.data[q.front];
    q.front = (q.front + 1) % MAX_CIRC;
    q.count--;
    return value;
}

void displayCQueue(const CQueue &q) {
    if (isEmptyC(q)) {
        cout << "Circular queue kosong.\n";
        return;
    }
    cout << "Isi circular queue: ";
    for (int i = 0; i < q.count; i++) {
        int idx = (q.front + i) % MAX_CIRC;
        cout << q.data[idx] << " ";
    }
    cout << endl;
}

// >>> Soal 3 sekarang interaktif, user isi nilai sendiri <<<
void runSoal3() {
    CQueue q;
    initCQueue(q);

    int pilihan;
    do {
        cout << "\n=== SOAL 3 - CIRCULAR QUEUE ===\n";
        cout << "1. Enqueue (tambah data)\n";
        cout << "2. Dequeue (hapus data)\n";
        cout << "3. Tampilkan isi queue\n";
        cout << "4. Tampilkan posisi front & rear\n";
        cout << "5. Kembali ke menu utama\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            int nilai;
            cout << "Masukkan nilai integer: ";
            cin >> nilai;
            enqueueC(q, nilai);
            break;
        }
        case 2: {
            int x = dequeueC(q);
            if (x != -1) {
                cout << "Dequeue: " << x << endl;
            }
            break;
        }
        case 3:
            displayCQueue(q);
            break;
        case 4:
            cout << "front = " << q.front
                 << ", rear = " << q.rear
                 << ", count = " << q.count << endl;
            break;
        case 5:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 5);
}

/////////////////////////////////////////
// SOAL 4 - SIMULASI ANTRIAN KASIR    //
/////////////////////////////////////////

const int MAX_KASIR = 10;

struct Pelanggan {
    int nomor;
    int lamaPelayanan; // detik
};

struct QueuePelanggan {
    Pelanggan data[MAX_KASIR];
    int front;
    int rear;
    int count;
};

void initKasirQueue(QueuePelanggan &q) {
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool isEmptyKasir(const QueuePelanggan &q) {
    return q.count == 0;
}

bool isFullKasir(const QueuePelanggan &q) {
    return q.count == MAX_KASIR;
}

void enqueueKasir(QueuePelanggan &q, Pelanggan p) {
    if (isFullKasir(q)) {
        cout << "Antrian kasir penuh! Tidak bisa menambah pelanggan.\n";
        return;
    }
    q.rear = (q.rear + 1) % MAX_KASIR;
    q.data[q.rear] = p;
    q.count++;
    cout << "Pelanggan nomor " << p.nomor << " masuk antrian.\n";
}

Pelanggan dequeueKasir(QueuePelanggan &q) {
    Pelanggan kosong;
    kosong.nomor = -1;
    kosong.lamaPelayanan = 0;

    if (isEmptyKasir(q)) {
        cout << "Antrian kosong! Tidak ada pelanggan untuk dilayani.\n";
        return kosong;
    }
    Pelanggan p = q.data[q.front];
    q.front = (q.front + 1) % MAX_KASIR;
    q.count--;
    return p;
}

void tampilkanAntrianKasir(const QueuePelanggan &q) {
    if (isEmptyKasir(q)) {
        cout << "Tidak ada pelanggan yang menunggu.\n";
        return;
    }
    cout << "Pelanggan yang sedang menunggu:\n";
    for (int i = 0; i < q.count; i++) {
        int idx = (q.front + i) % MAX_KASIR;
        cout << "Nomor: " << q.data[idx].nomor
             << " | Lama pelayanan: " << q.data[idx].lamaPelayanan << " detik\n";
    }
}

void runSoal4() {
    QueuePelanggan q;
    initKasirQueue(q);

    int pilihan;
    int nextNomor = 1;

    do {
        cout << "\n=== SOAL 4 - SIMULASI ANTRIAN KASIR ===\n";
        cout << "1. Tambah pelanggan (enqueue)\n";
        cout << "2. Layani pelanggan (dequeue)\n";
        cout << "3. Tampilkan pelanggan yang menunggu\n";
        cout << "4. Tampilkan jumlah pelanggan dalam antrian\n";
        cout << "5. Kembali ke menu utama\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            Pelanggan p;
            p.nomor = nextNomor++;
            cout << "Masukkan lama pelayanan (detik) untuk pelanggan nomor "
                 << p.nomor << ": ";
            cin >> p.lamaPelayanan;
            enqueueKasir(q, p);
            break;
        }
        case 2: {
            Pelanggan dilayani = dequeueKasir(q);
            if (dilayani.nomor != -1) {
                cout << "Sedang melayani pelanggan nomor " << dilayani.nomor
                     << " selama " << dilayani.lamaPelayanan << " detik.\n";
            }
            break;
        }
        case 3:
            tampilkanAntrianKasir(q);
            break;
        case 4:
            cout << "Jumlah pelanggan dalam antrian: " << q.count << endl;
            break;
        case 5:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);
}

//////////////////////
// MAIN PROGRAM     //
//////////////////////

int main() {
    int pilihan;

    do {
        cout << "\n=========== MENU UTAMA QUEUE ===========\n";
        cout << "1. Soal 1 - Queue Integer Dasar\n";
        cout << "2. Soal 2 - Queue Character (input string)\n";
        cout << "3. Soal 3 - Circular Queue (input nilai)\n";
        cout << "4. Soal 4 - Simulasi Antrian Kasir\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            runSoal1();
            break;
        case 2:
            runSoal2();
            break;
        case 3:
            runSoal3();
            break;
        case 4:
            runSoal4();
            break;
        case 5:
            cout << "Terima kasih, program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 5);

    return 0;
}
