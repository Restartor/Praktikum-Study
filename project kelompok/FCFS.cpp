#include <iostream>
#include <iomanip>
using namespace std;

const int MAXP = 2;

int main() {
    int n;
    int id[MAXP], AT[MAXP], BT[MAXP];
    int Start[MAXP], CT[MAXP], TAT[MAXP], WT[MAXP], RT[MAXP];
    int idx[MAXP];                      // index proses setelah diurutkan (berdasarkan AT)

    cout << "Jumlah proses: ";
    cin >> n;
        if (n > MAXP) {
    cout << "Input melebihi kapasitas. Hanya " << MAXP << " proses yang dipakai.\n";
    n = MAXP;
    return 0;
}

    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        cout << "P" << id[i] << " AT BT: ";
        cin >> AT[i] >> BT[i];
    }

    // --- Urutkan indeks berdasarkan AT (tie-break: ID) -> FCFS ---
    for (int i = 0; i < n; i++) idx[i] = i;
    for (int a = 0; a < n - 1; a++) {
        for (int b = 0; b < n - 1 - a; b++) {
            int L = idx[b], R = idx[b + 1];
            if (AT[L] > AT[R] || (AT[L] == AT[R] && id[L] > id[R])) {
                int t = idx[b]; idx[b] = idx[b + 1]; idx[b + 1] = t;
            }
        }
    }
// --- Simulasi FCFS ---
    int t = 0;                          // waktu CPU siap
    // untuk Gantt sederhana
    int gStart[MAXP], gEnd[MAXP], gWho[MAXP], gCnt = 0;

    for (int k = 0; k < n; k++) {
        int i = idx[k];                 // proses ke-i (setelah diurutkan)

        // Jika proses belum datang, CPU idle sampai AT[i]
        if (t < AT[i]) {
            // segmen idle opsional, tidak kita simpan ke Gantt agar sederhana
            t = AT[i];
        }

        Start[i] = t;
        CT[i]    = Start[i] + BT[i];
        TAT[i]   = CT[i] - AT[i];
        WT[i]    = TAT[i] - BT[i];
        RT[i]    = Start[i] - AT[i];

        // simpan segmen Gantt
        gStart[gCnt] = Start[i];
        gEnd[gCnt]   = CT[i];
        gWho[gCnt]   = id[i];
        gCnt++;

        t = CT[i]; // CPU siap di waktu selesai proses ini
    }

    // --- Cetak Gantt ---
    cout << "\nGantt: ";
    for (int s = 0; s < gCnt; s++) {
        cout << "|" << gStart[s] << "-" << gEnd[s] << ":P" << gWho[s];
    }
    cout << "|\n";

    // --- Tabel hasil + rata-rata ---
    double sumWT = 0, sumTAT = 0, sumRT = 0;
    cout << "\n== FCFS ==\n";
    cout << left << setw(6) << "ID"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(6) << "CT"
         << setw(6) << "TAT"
         << setw(6) << "WT"
         << setw(6) << "RT" << "\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(6) << ("P" + to_string(id[i]))
             << setw(6) << AT[i]
             << setw(6) << BT[i]
             << setw(6) << CT[i]
             << setw(6) << TAT[i]
             << setw(6) << WT[i]
             << setw(6) << RT[i] << "\n";
        sumWT  += WT[i];
        sumTAT += TAT[i];
        sumRT  += RT[i];
    }


    cout << fixed << setprecision(2);
    cout << "Avg WT  = " << (sumWT / n)  << "\n";
    cout << "Avg TAT = " << (sumTAT / n) << "\n";
    cout << "Avg RT  = " << (sumRT / n)  << "\n";
    return 0;
}