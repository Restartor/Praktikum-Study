#include <iostream>
#include <vector>
using namespace std;

struct Process {
    char name[20]; // nama proses tanpa spasi
    int at;        // Arrival Time
    int bt;        // Burst Time
    int remaining;
    int queue;     // 1 = RR, 2 = FCFS
    int ct;        // Completion Time
    int tat;       // Turnaround Time
    int wt;        // Waiting Time
    int rt;        // Response Time
};

struct Segment {
    int start;
    int end;
    int pid;
    int q; // queue level : 1 or 2
};

int main() {
    int n;
    cout << "===== Multi-Level Queue Scheduling =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "\nProses ke-" << i + 1 << ":\n";
        cout << "Nama proses: ";
        cin >> p[i].name;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time: ";
        cin >> p[i].bt;
        cout << "Queue (1=RR | 2=FCFS): ";
        cin >> p[i].queue;

        p[i].remaining = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
        p[i].rt = -1;
    }

    int time = 0;
    int completed = 0;
    int quantum = 2;
    
    vector<Segment> gantt;
    
    vector<int> q1, q2; // queue RR & queue FCFS
    int current = -1;
    int qtime = 0;
    int currentQueue = -1;
    int segStart = 0;

    // Jalankan sampai semua selesai
    while (completed < n) {
        // Masukkan proses ke queue sesuai AT
        for (int i = 0; i < n; i++) {
            if (p[i].at == time) {
                if (p[i].queue == 1) q1.push_back(i);
                else q2.push_back(i);
            }
        }

        int next = -1;

        // Prioritas Queue 1
        if (!q1.empty()) {
            if (current == -1 || currentQueue == 2) {
                next = q1.front();
                q1.erase(q1.begin());
                qtime = 0;
                currentQueue = 1;
            } else if (currentQueue == 1) {
                next = current;
            }
        }
        // Kalau Q1 kosong, jalankan Q2
        else if (!q2.empty()) {
            if (current == -1 || currentQueue == 1) {
                next = q2.front();
                q2.erase(q2.begin());
                currentQueue = 2;
            } else if (currentQueue == 2) {
                next = current;
            }
        }

        // Jika CPU idle
        if (next == -1) {
            if (current != -1) {
                gantt.push_back({segStart, time, current, currentQueue});
                current = -1;
            }
            time++;
            segStart = time;
            continue;
        }

        // Jika berganti proses → tutup segmen sebelumnya
        if (next != current) {
            if (current != -1) {
                gantt.push_back({segStart, time, current, currentQueue});
            }
            segStart = time;
            current = next;
        }

        // Response time pertama kali jalan
        if (p[current].rt == -1) {
            p[current].rt = time - p[current].at;
        }

        // Eksekusi 1 waktu
        p[current].remaining--;
        time++;
        qtime++;

        // Kalau selesai
        if (p[current].remaining == 0) {
            p[current].ct = time;
            completed++;
            gantt.push_back({segStart, time, current, currentQueue});
            current = -1;
            qtime = 0;
        }
        else if (currentQueue == 1 && qtime == quantum) {
            // Pindah giliran RR
            q1.push_back(current);
            gantt.push_back({segStart, time, current, currentQueue});
            current = -1;
            qtime = 0;
        }
    }

    // Hitung TAT dan WT
    double totalTAT = 0, totalWT = 0;
    double totalTAT1 = 0, totalWT1 = 0, c1 = 0;
    double totalTAT2 = 0, totalWT2 = 0, c2 = 0;

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalTAT += p[i].tat;
        totalWT  += p[i].wt;

        if (p[i].queue == 1) {
            totalTAT1 += p[i].tat;
            totalWT1  += p[i].wt;
            c1++;
        } else {
            totalTAT2 += p[i].tat;
            totalWT2  += p[i].wt;
            c2++;
        }
    }

    // Output
    cout << "\n========== GANTT CHART ==========\n";
    for (int i = 0; i < gantt.size(); i++) {
        cout << "[" << gantt[i].start << "-" << gantt[i].end << "] "
             << p[gantt[i].pid].name << "(Q" << gantt[i].q << ")  ";
    }

    cout << "\n\n========== HASIL PROSES ==========\n";
    cout << "Nama\tAT\tBT\tQ\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << p[i].name << "\t" 
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].queue << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\t"
             << p[i].rt << "\n";
    }

    cout << "\nRata-rata TAT: " << totalTAT / n;
    cout << "\nRata-rata WT : " << totalWT  / n;

    if (c1 > 0) {
        cout << "\n\nQueue 1 (RR) → Avg TAT: " << totalTAT1 / c1
             << " | Avg WT: " << totalWT1 / c1;
    }
    if (c2 > 0) {
        cout << "\nQueue 2 (FCFS) → Avg TAT: " << totalTAT2 / c2
             << " | Avg WT: " << totalWT2 / c2;
    }

    cout << "\n\nSelesai!\n";
    return 0;
}
