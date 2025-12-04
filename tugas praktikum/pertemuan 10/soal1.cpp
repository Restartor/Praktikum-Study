#include <iostream>
#include <vector>
using namespace std;

struct Process {
    char name[20];   // nama proses (tanpa spasi)
    int at;          // Arrival Time
    int bt;          // Burst Time
    int remaining;   // sisa waktu
    int ct;          // Completion Time
    int tat;         // Turnaround Time
    int wt;          // Waiting Time
    int rt;          // Response Time (waktu pertama kali jalan - AT)
};

struct Segment {
    int start;
    int end;
    int pid;   // index proses, -1 = IDLE
};

int main() {
    int n;
    cout << "===== SRTF (Shortest Remaining Time First) =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);

    // Input proses
    for (int i = 0; i < n; ++i) {
        cout << "\nProses ke-" << i + 1 << ":\n";
        cout << "Nama proses      : ";
        cin >> p[i].name;        // tanpa spasi
        cout << "Arrival Time (AT): ";
        cin >> p[i].at;
        cout << "Burst Time (BT)  : ";
        cin >> p[i].bt;

        p[i].remaining = p[i].bt;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
        p[i].rt = -1;   // belum pernah jalan
    }

    // cari arrival paling kecil sebagai waktu mulai
    int firstArrival = 1000000000;
    for (int i = 0; i < n; ++i) {
        if (p[i].at < firstArrival) {
            firstArrival = p[i].at;
        }
    }

    int time = firstArrival;
    int completed = 0;

    vector<Segment> gantt;
    int currentIdx = -1;   // index proses yang sedang jalan, -1 = tidak ada
    int currentStart = time;
    int preemptions = 0;

    while (completed < n) {
        // pilih proses dengan remaining time terkecil yang sudah datang
        int idx = -1;
        int minRemaining = 1000000000;

        for (int i = 0; i < n; ++i) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (p[i].remaining < minRemaining) {
                    minRemaining = p[i].remaining;
                    idx = i;
                } else if (p[i].remaining == minRemaining) {
                    // tie-breaker: yang datang lebih dulu
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        // tidak ada proses ready -> CPU idle sampai proses berikutnya datang
        if (idx == -1) {
            // tutup segmen proses sebelumnya kalau ada
            if (currentIdx != -1) {
                Segment s;
                s.start = currentStart;
                s.end = time;
                s.pid = currentIdx;
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
                break; // tidak ada proses lagi
            }

            // segmen IDLE
            Segment idleSeg;
            idleSeg.start = time;
            idleSeg.end = nextArrival;
            idleSeg.pid = -1;   // IDLE
            gantt.push_back(idleSeg);

            time = nextArrival;
            currentStart = time;
            continue;
        }

        // cek preemption (perpindahan proses)
        if (idx != currentIdx) {
            if (currentIdx != -1) {
                Segment s;
                s.start = currentStart;
                s.end = time;
                s.pid = currentIdx;
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

        // eksekusi 1 satuan waktu
        p[idx].remaining--;
        time++;

        // kalau selesai
        if (p[idx].remaining == 0) {
            p[idx].ct = time;
            completed++;
        }
    }

    // tutup segmen terakhir jika masih ada proses berjalan
    if (currentIdx != -1) {
        Segment s;
        s.start = currentStart;
        s.end = time;
        s.pid = currentIdx;
        gantt.push_back(s);
    }

    // hitung TAT dan WT
    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    for (int i = 0; i < n; ++i) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        totalRT += p[i].rt;
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
    cout << "Proses\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; ++i) {
        cout << p[i].name << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\t"
             << p[i].rt << "\n";
    }

    cout << "\nRata-rata TAT : " << (totalTAT / n) << "\n";
    cout << "Rata-rata WT  : " << (totalWT  / n) << "\n";
    cout << "Rata-rata RT  : " << (totalRT  / n) << "\n";

    cout << "\nJumlah preemption: " << preemptions << "\n";

    return 0;
}
