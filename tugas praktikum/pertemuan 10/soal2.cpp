#include <iostream>
#include <vector>
using namespace std;

struct Process {
    char name[20];    // nama proses (tanpa spasi)
    int at;           // Arrival Time
    int bt;           // Burst Time
    int priority;     // priority awal (semakin kecil = semakin tinggi)
    int currentPrio;  // priority yang bisa berubah karena aging
    int remaining;    // sisa burst time
    int ct;           // Completion Time
    int tat;          // Turnaround Time
    int wt;           // Waiting Time
    int rt;           // Response Time (first start - AT)
    int waiting;      // lama menunggu utk aging
};

struct Segment {
    int start;
    int end;
    int pid;          // index proses, -1 = IDLE
};


int main() {
    int n;
    cout << "===== PRIORITY SCHEDULING (Preemptive) + AGING =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);

    // Input proses
    for (int i = 0; i < n; ++i) {
        cout << "\nProses ke-" << i + 1 << ":\n";
        cout << "Nama proses                 : ";
        cin >> p[i].name;
        cout << "Arrival Time (AT)          : ";
        cin >> p[i].at;
        cout << "Burst Time (BT)            : ";
        cin >> p[i].bt;
        cout << "Priority (lebih kecil=lebih tinggi): ";
        cin >> p[i].priority;

        p[i].currentPrio = p[i].priority;
        p[i].remaining   = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
        p[i].rt = -1;       // belum pernah jalan
        p[i].waiting = 0;   // belum menunggu
    }

    // cari arrival paling kecil
    int firstArrival = 1000000000;
    for (int i = 0; i < n; ++i) {
        if (p[i].at < firstArrival) {
            firstArrival = p[i].at;
        }
    }

    int time = firstArrival;
    int completed = 0;

    vector<Segment> gantt;
    int currentIdx = -1;    // proses yg sedang jalan
    int currentStart = time;
    int preemptions = 0;
    int priorityChanges = 0;

    const int AGING_THRESHOLD = 5; // jika waiting > 5, priority-- (naik)

    while (completed < n) {
        // pilih proses ready dengan currentPrio terkecil
        int idx = -1;
        int bestPrio = 1000000000;

        for (int i = 0; i < n; ++i) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (p[i].currentPrio < bestPrio) {
                    bestPrio = p[i].currentPrio;
                    idx = i;
                } else if (p[i].currentPrio == bestPrio) {
                    // tie-break: yang datang lebih dulu
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        // jika tidak ada proses ready -> idle
        if (idx == -1) {
            // tutup segmen proses sebelumnya
            if (currentIdx != -1) {
                Segment s;
                s.start = currentStart;
                s.end   = time;
                s.pid   = currentIdx;
                gantt.push_back(s);
                currentIdx = -1;
            }

            int nextArrival = 1000000000;
            for (int i = 0; i < n; ++i) {
                if (p[i].remaining > 0 && p[i].at > time) {
                    if (p[i].at < nextArrival) {
                        nextArrival = p[i].at;
                    }
                }
            }
            if (nextArrival == 1000000000) {
                break;
            }

            // segmen IDLE
            Segment idleSeg;
            idleSeg.start = time;
            idleSeg.end   = nextArrival;
            idleSeg.pid   = -1;
            gantt.push_back(idleSeg);

            time = nextArrival;
            currentStart = time;
            continue;
        }

        // cek perpindahan (preemption)
        if (idx != currentIdx) {
            if (currentIdx != -1) {
                Segment s;
                s.start = currentStart;
                s.end   = time;
                s.pid   = currentIdx;
                gantt.push_back(s);

                if (p[currentIdx].remaining > 0) {
                    preemptions++;
                }
            }
            currentIdx = idx;
            currentStart = time;

            // pertama kali jalan -> RT
            if (p[idx].rt == -1) {
                p[idx].rt = time - p[idx].at;
            }
        }

        // ===== AGING: proses ready tapi TIDAK jalan =====
        for (int i = 0; i < n; ++i) {
            if (p[i].remaining > 0 && p[i].at <= time) {
                if (i == idx) {
                    // proses yg sedang jalan tidak menunggu
                    p[i].waiting = 0;
                } else {
                    p[i].waiting++;
                    if (p[i].waiting > AGING_THRESHOLD) {
                        int oldPrio = p[i].currentPrio;
                        p[i].currentPrio--;
                        if (p[i].currentPrio < 0) p[i].currentPrio = 0;
                        if (p[i].currentPrio != oldPrio) {
                            priorityChanges++;
                        }
                        p[i].waiting = 0;
                    }
                }
            }
        }
        // ===============================================

        // eksekusi 1 satuan waktu
        p[idx].remaining--;
        time++;

        // jika selesai
        if (p[idx].remaining == 0) {
            p[idx].ct = time;
            completed++;
        }
    }

    // tutup segmen terakhir
    if (currentIdx != -1) {
        Segment s;
        s.start = currentStart;
        s.end   = time;
        s.pid   = currentIdx;
        gantt.push_back(s);
    }

    // hitung TAT, WT, RT total
    double totalTAT = 0;
    double totalWT  = 0;
    double totalRT  = 0;

    for (int i = 0; i < n; ++i) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        totalTAT += p[i].tat;
        totalWT  += p[i].wt;
        totalRT  += p[i].rt;
    }

    // tampilkan Gantt Chart
    cout << "\n========== GANTT CHART ==========\n";
    for (int i = 0; i < (int)gantt.size(); ++i) {
        cout << "[" << gantt[i].start << "-" << gantt[i].end << "] ";
        if (gantt[i].pid == -1) {
            cout << "IDLE";
        } else {
            cout << p[gantt[i].pid].name;
        }
        cout << "  ";
    }
    cout << "\n";

    // tabel hasil
    cout << "\n========== HASIL AKHIR ==========\n";
    cout << "Proses\tAT\tBT\tPrAwal\tPrAkhir\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; ++i) {
        cout << p[i].name << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].priority << "\t"
             << p[i].currentPrio << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\t"
             << p[i].rt << "\n";
    }

    cout << "\nRata-rata TAT : " << (totalTAT / n) << "\n";
    cout << "Rata-rata WT  : " << (totalWT  / n) << "\n";
    cout << "Rata-rata RT  : " << (totalRT  / n) << "\n";

    cout << "\nJumlah preemption                 : " << preemptions << "\n";
    cout << "Jumlah perubahan prioritas (aging): " << priorityChanges << "\n";

    return 0;
}
