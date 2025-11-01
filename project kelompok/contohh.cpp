#include <iostream>
#include <iomanip> // saya menggunakan iomanip untuk mengatur jarak spasi antara hasil dan membuat tabelnya
using namespace std;
// oiya jika kalian melihat idx/i itu adalah untuk menentukan 1,2,3,4 dst

const int MAXP = 20; // untuk maximal kapasitas proses

struct Proc {
    int id;
    int AT; // Arrival Time
    int BT; // Burst Time
    int CT; // Completion Time
    int TAT; // Turnaround Time
    int WT;  // Waiting Time
    int RT;  // Response Time
    bool done; // untuk menandai proses sudah selesai atau belum
    bool started; // untuk menandai proses sudah mulai atau belum
};

void reset(Proc p[], int n) { // Untuk mereset atribut proses sebelum simulasi
    for (int i = 0; i < n; i++) {
        p[i].CT = p[i].TAT = p[i].WT = p[i].RT = 0;
        p[i].done = false;
        p[i].started = false;
    }
}

void printResult(const char* title, Proc p[], int n) {// Menampilkan hasil tabel dan rata-rata
    double avgWT = 0, avgTAT = 0, avgRT = 0;
    cout << "\n== " << title << " ==\n";
    cout << left << setw(6) << "ID"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(6) << "CT"
         << setw(6) << "TAT"
         << setw(6) << "WT"
         << setw(6) << "RT" << "\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(6) << ("P"+to_string(p[i].id)) // to_string adalah untuk mengubah numeric value menjadi string
             << setw(6) << p[i].AT
             << setw(6) << p[i].BT
             << setw(6) << p[i].CT
             << setw(6) << p[i].TAT
             << setw(6) << p[i].WT
             << setw(6) << p[i].RT << "\n";
        avgWT  += p[i].WT;
        avgTAT += p[i].TAT;
        avgRT  += p[i].RT;
    }
    cout << fixed << setprecision(2); // agar persisi
    cout << "Avg WT  = " << (avgWT/n)  << "\n";
    cout << "Avg TAT = " << (avgTAT/n) << "\n";
    cout << "Avg RT  = " << (avgRT/n)  << "\n";
}


void printGantt(int starts[], int ends[], int who[], int m) {// Menampilkan diagram Gantt
    cout << "Gantt: ";
    for (int i = 0; i < m; i++) {
        cout << "|" << starts[i] << "-" << ends[i] << ":P" << who[i];
    }
    cout << "|\n";
}

// FCFS: First-Come, First-Served (non-preemptive)
void FCFS(Proc p[], int n) {
    // buat urutan indeks berdasar AT (bubble sederhana)
    int idx[MAXP];
    for (int i = 0; i < n; i++) idx[i] = i;
    for (int a = 0; a < n-1; a++) {
        for (int b = 0; b < n-1-a; b++) {
            if (p[idx[b]].AT > p[idx[b+1]].AT ||
               (p[idx[b]].AT == p[idx[b+1]].AT && p[idx[b]].id > p[idx[b+1]].id)) {
                int t = idx[b]; idx[b] = idx[b+1]; idx[b+1] = t;
            }
        }
    }

    int time = 0; 
    int starts[MAXP], ends[MAXP], who[MAXP], m = 0;

    for (int k = 0; k < n; k++) {
        int i = idx[k];
        if (time < p[i].AT) time = p[i].AT;      // idle sampai proses tiba
        // response time: pertama kali dapat CPU
        p[i].RT = time - p[i].AT;
        // jalan penuh (non-preemptive)
        starts[m] = time;
        time += p[i].BT;
        ends[m] = time;
        who[m] = p[i].id; m++;

        p[i].CT  = time;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT  = p[i].TAT - p[i].BT;
    }

    printGantt(starts, ends, who, m);
    printResult("FCFS (non-preemptive)", p, n);
}

// SJF: Shortest Job First (non-preemptive) yang terkecil dulu
void SJF(Proc p[], int n) {
    reset(p, n);
    int time = 0, finished = 0;
    int starts[MAXP], ends[MAXP], who[MAXP], m = 0;

    while (finished < n) {
        // cari kandidat: sudah datang & belum selesai, pilih BT terkecil (tie: AT, lalu ID)
        int pick = -1; // indeks proses terpilih
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].AT <= time) {
                if (pick == -1) pick = i;
                else {
                    if (p[i].BT < p[pick].BT ||
                       (p[i].BT == p[pick].BT && (p[i].AT < p[pick].AT ||
                        (p[i].AT == p[pick].AT && p[i].id < p[pick].id)))) {
                        pick = i;
                    }
                }
            }
        }
        // jika belum ada yg datang, lompatkan waktu ke AT terdekat
        if (pick == -1) {
            int minAT = 1e9, j = -1;
            for (int i = 0; i < n; i++) {
                if (!p[i].done && p[i].AT < minAT) { minAT = p[i].AT; j = i; }
            }
            time = p[j].AT;
            pick = j;
        }

        // response time: jika belum pernah mulai
        p[pick].RT = time - p[pick].AT;

        // jalankan penuh
        starts[m] = time;
        time += p[pick].BT;
        ends[m] = time;
        who[m] = p[pick].id; m++;

        p[pick].CT  = time;
        p[pick].TAT = p[pick].CT - p[pick].AT;
        p[pick].WT  = p[pick].TAT - p[pick].BT;
        p[pick].done = true;
        finished++;
    }

    printGantt(starts, ends, who, m);
    printResult("SJF (non-preemptive)", p, n);
}

int main() {
    int n;
    Proc p[MAXP];

    cout << "Jumlah proses (<=20): ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        p[i].id = i+1;
        cout << "P" << p[i].id << " AT BT: ";
        cin >> p[i].AT >> p[i].BT;
        p[i].done = false;
        p[i].started = false;
    }

    cout << "\nPilih algoritma:\n1) FCFS (non-preemptive)\n2) SJF (non-preemptive)\nPilihan: ";
    int opt; cin >> opt;

    if (opt == 1) {
        reset(p, n);
        FCFS(p, n);
    } else {
        SJF(p, n);
    }
    return 0;
}

// Setiap proses memiliki atribut:
// - id: ID proses
// - AT: Arrival Time
// - BT: Burst Time
// - CT: Completion Time
// - TAT: Turnaround Time
// - WT: Waiting Time
// - RT: Response Time
// - done: menandai apakah proses sudah selesai
// - started: menandai apakah proses sudah mulai dijalankan
// Fungsi reset: mereset atribut proses sebelum simulasi
// Fungsi printResult: menampilkan tabel hasil dan rata-rata WT, TAT, RT
// Fungsi printGantt: menampilkan diagram Gantt sederhana
// Fungsi FCFS: mengimplementasikan algoritma First-Come, First-Served (non-preemptive)
// Fungsi SJF: mengimplementasikan algoritma Shortest Job First (non-preemptive)
// Fungsi main: input proses, memilih algoritma, menjalankan simulasi, menampilkan hasil
