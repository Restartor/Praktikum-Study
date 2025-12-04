#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

/* ============================================================
   SOAL 1 SRTF
   ============================================================ */
void solve_srtf() {

    struct Process {
        string name;
        int arrival_time;
        int burst_time;
        int remaining_time;
        int completion_time;
        int turnaround_time;
        int waiting_time;
        int response_time;
    };

    struct GanttSegment {
        int start_time;
        int end_time;
        int proc_index;   // -1 = IDLE
    };

    int n;
    cout << "\n===== SOAL 1 SRTF =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);

    for (int i = 0; i < n; i++) {
        p[i].name = "P" + to_string(i + 1);
        cout << "\nProses ke-" << i + 1 << " :\n";
        cout << "Arrival time : ";
        cin >> p[i].arrival_time;
        cout << "Burst time   : ";
        cin >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
        p[i].response_time  = -1;
    }

    int time = 1e9;
    for (int i = 0; i < n; i++)
        if (p[i].arrival_time < time) time = p[i].arrival_time;

    int done = 0;
    vector<GanttSegment> gantt;
    int active_index = -1, segment_start = time;
    int preempt_count = 0;

    while (done < n) {
        int select_index = -1, min_rem = 1e9;

        for (int i = 0; i < n; i++)
            if (p[i].arrival_time <= time && p[i].remaining_time > 0 &&
                p[i].remaining_time < min_rem) {
                min_rem = p[i].remaining_time;
                select_index = i;
            }

        if (select_index == -1) {
            int next_time = 1e9;
            for (int i = 0; i < n; i++)
                if (p[i].remaining_time > 0 &&
                    p[i].arrival_time > time &&
                    p[i].arrival_time < next_time)
                    next_time = p[i].arrival_time;

            if (active_index != -1)
                gantt.push_back({segment_start, time, active_index});

            gantt.push_back({time, next_time, -1});
            time = next_time;
            segment_start = time;
            active_index = -1;
            continue;
        }

        if (select_index != active_index) {
            if (active_index != -1) {
                gantt.push_back({segment_start, time, active_index});
                if (p[active_index].remaining_time > 0)
                    preempt_count++;
            }
            active_index = select_index;
            segment_start = time;
            if (p[active_index].response_time == -1)
                p[active_index].response_time =
                    time - p[active_index].arrival_time;
        }

        p[select_index].remaining_time--;
        time++;

        if (p[select_index].remaining_time == 0) {
            p[select_index].completion_time = time;
            done++;
        }
    }

    if (active_index != -1)
        gantt.push_back({segment_start, time, active_index});

    double sum_tat = 0, sum_wt = 0, sum_rt = 0;
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time    = p[i].turnaround_time - p[i].burst_time;
        sum_tat += p[i].turnaround_time;
        sum_wt  += p[i].waiting_time;
        sum_rt  += p[i].response_time;
    }

    // ===== GANTT CHART kotak =====
    cout << "\n===== GANTT CHART (SRTF) =====\n";
    if (!gantt.empty()) {
        // garis atas
        cout << " ";
        for (auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2;
            for (int i = 0; i < width; ++i) cout << "-";
            cout << " ";
        }
        cout << "\n|";
        // baris nama proses
        for (auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2 - 1;
            string label = (g.proc_index == -1) ? "IDLE" : p[g.proc_index].name;
            if ((int)label.size() > width) label = label.substr(0, width);
            int left  = (width - (int)label.size()) / 2;
            int right = width - (int)label.size() - left;
            for (int i = 0; i < left; ++i) cout << " ";
            cout << label;
            for (int i = 0; i < right; ++i) cout << " ";
            cout << "|";
        }
        cout << "\n ";
        // garis bawah
        for (auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2;
            for (int i = 0; i < width; ++i) cout << "-";
            cout << " ";
        }
        cout << "\n";
        // baris waktu
        int current_time = gantt[0].start_time;
        cout << current_time;
        for (auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2;
            for (int i = 0; i < width; ++i) cout << " ";
            cout << g.end_time;
        }
        cout << "\n";
    }

    // ===== Tabel hasil =====
    cout << "\n===== TABEL HASIL SRTF =====\n";
    cout << left
         << setw(8) << "Nama"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(6) << "CT"
         << setw(6) << "TAT"
         << setw(6) << "WT"
         << setw(6) << "RT"
         << "\n";

    for (int i = 0; i < n; i++) {
        cout << left
             << setw(8) << p[i].name
             << setw(6) << p[i].arrival_time
             << setw(6) << p[i].burst_time
             << setw(6) << p[i].completion_time
             << setw(6) << p[i].turnaround_time
             << setw(6) << p[i].waiting_time
             << setw(6) << p[i].response_time
             << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAvg TAT = " << sum_tat / n;
    cout << "\nAvg WT  = " << sum_wt / n;
    cout << "\nAvg RT  = " << sum_rt / n;
    cout << "\nPreemption = " << preempt_count << "\n";
}

/* ============================================================
   SOAL 2 PRIORITY PREEMPTIVE + AGING
   ============================================================ */
void solve_priority_aging() {

    struct Process {
        string name;
        int arrival_time;
        int burst_time;
        int priority_value;
        int current_priority;
        int remaining_time;
        int completion_time;
        int turnaround_time;
        int waiting_time;
        int response_time;
        int aging_counter;
    };

    struct GanttSegment { int start, end, proc_index; };

    int n;
    cout << "\n===== SOAL 2 PRIORITY PREEMPTIVE + AGING =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].name = "P" + to_string(i + 1);
        cout << "\nProses ke-" << i + 1 << " :\n";
        cout << "Arrival time : ";
        cin >> p[i].arrival_time;
        cout << "Burst time   : ";
        cin >> p[i].burst_time;
        cout << "Priority (lebih kecil = lebih tinggi): ";
        cin >> p[i].priority_value;
        p[i].current_priority = p[i].priority_value;
        p[i].remaining_time   = p[i].burst_time;
        p[i].response_time    = -1;
        p[i].aging_counter    = 0;
    }

    int time = 1e9;
    for (int i = 0; i < n; i++)
        if (p[i].arrival_time < time) time = p[i].arrival_time;

    int done = 0;
    vector<GanttSegment> gantt;
    int active = -1, seg_start = time;
    int preempt = 0, priority_changes = 0;

    while (done < n) {
        int select = -1, best = 1e9;

        for (int i = 0; i < n; i++)
            if (p[i].arrival_time <= time &&
                p[i].remaining_time > 0 &&
                p[i].current_priority < best) {
                best = p[i].current_priority;
                select = i;
            }

        if (select == -1) {
            int next = 1e9;
            for (int i = 0; i < n; i++)
                if (p[i].remaining_time > 0 &&
                    p[i].arrival_time > time &&
                    p[i].arrival_time < next)
                    next = p[i].arrival_time;

            if (active != -1) gantt.push_back({seg_start, time, active});
            gantt.push_back({time, next, -1});
            time = next;
            seg_start = time;
            active = -1;
            continue;
        }

        if (select != active) {
            if (active != -1) {
                gantt.push_back({seg_start, time, active});
                if (p[active].remaining_time > 0) preempt++;
            }
            active = select;
            seg_start = time;
            if (p[select].response_time == -1)
                p[select].response_time =
                    time - p[select].arrival_time;
        }

        // aging
        for (int i = 0; i < n; i++)
            if (p[i].remaining_time > 0 && p[i].arrival_time <= time) {
                if (i == select) p[i].aging_counter = 0;
                else {
                    p[i].aging_counter++;
                    if (p[i].aging_counter > 5) {
                        int old = p[i].current_priority;
                        p[i].current_priority--;
                        if (p[i].current_priority < 0)
                            p[i].current_priority = 0;
                        if (old != p[i].current_priority)
                            priority_changes++;
                        p[i].aging_counter = 0;
                    }
                }
            }

        p[select].remaining_time--;
        time++;

        if (p[select].remaining_time == 0) {
            p[select].completion_time = time;
            done++;
        }
    }

    if (active != -1) gantt.push_back({seg_start, time, active});

    double sum_tat = 0, sum_wt = 0, sum_rt = 0;
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time    = p[i].turnaround_time - p[i].burst_time;
        sum_tat += p[i].turnaround_time;
        sum_wt  += p[i].waiting_time;
        sum_rt  += p[i].response_time;
    }

    // ===== GANTT CHART kotak =====
    cout << "\n===== GANTT CHART (PRIORITY + AGING) =====\n";
    if (!gantt.empty()) {
        cout << " ";
        for (auto &g : gantt) {
            int width = (g.end - g.start) * 2;
            for (int i = 0; i < width; ++i) cout << "-";
            cout << " ";
        }
        cout << "\n|";
        for (auto &g : gantt) {
            int width = (g.end - g.start) * 2 - 1;
            string label = (g.proc_index == -1) ? "IDLE" : p[g.proc_index].name;
            if ((int)label.size() > width) label = label.substr(0, width);
            int left  = (width - (int)label.size()) / 2;
            int right = width - (int)label.size() - left;
            for (int i = 0; i < left; ++i) cout << " ";
            cout << label;
            for (int i = 0; i < right; ++i) cout << " ";
            cout << "|";
        }
        cout << "\n ";
        for (auto &g : gantt) {
            int width = (g.end - g.start) * 2;
            for (int i = 0; i < width; ++i) cout << "-";
            cout << " ";
        }
        cout << "\n";
        int current_time = gantt[0].start;
        cout << current_time;
        for (auto &g : gantt) {
            int width = (g.end - g.start) * 2;
            for (int i = 0; i < width; ++i) cout << " ";
            cout << g.end;
        }
        cout << "\n";
    }

    // ===== Tabel hasil =====
    cout << "\n===== TABEL HASIL PRIORITY + AGING =====\n";
    cout << left
         << setw(8) << "Nama"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(8) << "PrAwal"
         << setw(8) << "PrAkhir"
         << setw(6) << "CT"
         << setw(6) << "TAT"
         << setw(6) << "WT"
         << setw(6) << "RT"
         << "\n";

    for (int i = 0; i < n; i++) {
        cout << left
             << setw(8) << p[i].name
             << setw(6) << p[i].arrival_time
             << setw(6) << p[i].burst_time
             << setw(8) << p[i].priority_value
             << setw(8) << p[i].current_priority
             << setw(6) << p[i].completion_time
             << setw(6) << p[i].turnaround_time
             << setw(6) << p[i].waiting_time
             << setw(6) << p[i].response_time
             << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAvg TAT = " << sum_tat / n;
    cout << "\nAvg WT  = " << sum_wt / n;
    cout << "\nAvg RT  = " << sum_rt / n;
    cout << "\nPreemption          = " << preempt;
    cout << "\nPriority changes(aging) = " << priority_changes << "\n";
}

/* ============================================================
   SOAL 3 MULTI LEVEL QUEUE (RR + FCFS)
   ============================================================ */
void solve_mlq() {

    struct Process {
        string name;
        int arrival_time;
        int burst_time;
        int queue_level;      // 1 = RR, 2 = FCFS
        int remaining_time;
        int completion_time;
        int turnaround_time;
        int waiting_time;
        int response_time;
    };

    struct GanttSegment {
        int start_time;
        int end_time;
        int proc_index;   // -1 = IDLE
        int queue_level;  // 0 = IDLE, 1 / 2 = level
    };

    int n;
    cout << "\n===== SOAL 3 MLQ (RR + FCFS) =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].name = "P" + to_string(i + 1);
        cout << "\nProses ke-" << i + 1 << " :\n";
        cout << "Arrival time       : ";
        cin >> p[i].arrival_time;
        cout << "Burst time         : ";
        cin >> p[i].burst_time;
        cout << "Queue (1=RR, 2=FCFS): ";
        cin >> p[i].queue_level;

        p[i].remaining_time  = p[i].burst_time;
        p[i].completion_time = 0;
        p[i].turnaround_time = 0;
        p[i].waiting_time    = 0;
        p[i].response_time   = -1;
    }

    vector<int> q_rr, q_fcfs;
    vector<GanttSegment> gantt;

    int time = p[0].arrival_time;
    for (int i = 1; i < n; i++)
        if (p[i].arrival_time < time)
            time = p[i].arrival_time;

    int completed     = 0;
    int current_index = -1;
    int current_queue = 0;
    const int quantum = 2;
    int quantum_left  = 0;
    int segment_start = time;

    while (completed < n) {

        for (int i = 0; i < n; i++)
            if (p[i].arrival_time == time)
                (p[i].queue_level == 1) ?
                    q_rr.push_back(i) :
                    q_fcfs.push_back(i);

        if (current_index != -1 && current_queue == 2 && !q_rr.empty()) {
            gantt.push_back({segment_start, time, current_index, current_queue});
            q_fcfs.insert(q_fcfs.begin(), current_index);
            current_index = -1;
        }

        if (current_index != -1 && current_queue == 1 && quantum_left == 0) {
            gantt.push_back({segment_start, time, current_index, current_queue});
            if (p[current_index].remaining_time > 0)
                q_rr.push_back(current_index);
            else {
                p[current_index].completion_time = time;
                completed++;
            }
            current_index = -1;
        }

        if (current_index != -1 && p[current_index].remaining_time == 0) {
            gantt.push_back({segment_start, time, current_index, current_queue});
            p[current_index].completion_time = time;
            completed++;
            current_index = -1;
        }

        if (current_index == -1) {
            if (!q_rr.empty()) {
                current_index = q_rr.front(); q_rr.erase(q_rr.begin());
                current_queue = 1;
                quantum_left  = quantum;
                segment_start = time;
                if (p[current_index].response_time == -1)
                    p[current_index].response_time =
                        time - p[current_index].arrival_time;
            }
            else if (!q_fcfs.empty()) {
                current_index = q_fcfs.front(); q_fcfs.erase(q_fcfs.begin());
                current_queue = 2;
                segment_start = time;
                if (p[current_index].response_time == -1)
                    p[current_index].response_time =
                        time - p[current_index].arrival_time;
            }
            else {
                int next_arrival = -1;
                for (int i = 0; i < n; i++)
                    if (p[i].remaining_time > 0 && p[i].arrival_time > time)
                        if (next_arrival == -1 ||
                            p[i].arrival_time < next_arrival)
                            next_arrival = p[i].arrival_time;

                if (next_arrival == -1) break;
                gantt.push_back({time, next_arrival, -1, 0});
                time = next_arrival;
                segment_start = time;
                continue;
            }
        }

        p[current_index].remaining_time--;
        time++;
        if (current_queue == 1) quantum_left--;
    }

    double total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time    = p[i].turnaround_time - p[i].burst_time;
        total_tat += p[i].turnaround_time;
        total_wt  += p[i].waiting_time;
    }

    cout << "\n===== GANTT CHART (MLQ) =====\n";
    if (!gantt.empty()) {
        cout << " ";
        for (const auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2;
            for (int i = 0; i < width; ++i) cout << "-";
            cout << " ";
        }
        cout << "\n|";
        for (const auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2 - 1;
            string label = (g.proc_index == -1) ? "IDLE" :
                p[g.proc_index].name + "(Q" + to_string(g.queue_level) + ")";
            if ((int)label.size() > width) label = label.substr(0, width);
            int left  = (width - (int)label.size()) / 2;
            int right = width - (int)label.size() - left;
            for (int i = 0; i < left; ++i) cout << " ";
            cout << label;
            for (int i = 0; i < right; ++i) cout << " ";
            cout << "|";
        }
        cout << "\n ";
        for (const auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2;
            for (int i = 0; i < width; ++i) cout << "-";
            cout << " ";
        }
        cout << "\n";
        int ct = gantt[0].start_time;
        cout << ct;
        for (const auto &g : gantt) {
            int width = (g.end_time - g.start_time) * 2;
            for (int i = 0; i < width; ++i) cout << " ";
            cout << g.end_time;
        }
        cout << "\n";
    }

    cout << "\n===== TABEL HASIL MLQ =====\n";
    cout << left
         << setw(8) << "Nama"
         << setw(6) << "AT"
         << setw(6) << "BT"
         << setw(6) << "Q"
         << setw(6) << "CT"
         << setw(6) << "TAT"
         << setw(6) << "WT"
         << setw(6) << "RT"
         << "\n";

    for (int i = 0; i < n; i++) {
        cout << left
             << setw(8) << p[i].name
             << setw(6) << p[i].arrival_time
             << setw(6) << p[i].burst_time
             << setw(6) << p[i].queue_level
             << setw(6) << p[i].completion_time
             << setw(6) << p[i].turnaround_time
             << setw(6) << p[i].waiting_time
             << setw(6) << p[i].response_time
             << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAvg TAT = " << total_tat / n;
    cout << "\nAvg WT  = " << total_wt / n << "\n"; }

/* ============================================================
   MAIN MENU
   ============================================================ */
int main() {
    int menu;
    do {
        cout << "\n\n===== MENU SOAL =====\n";
        cout << "1. SRTF\n";
        cout << "2. Priority Preemptive + Aging\n";
        cout << "3. MLQ (RR + FCFS)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;

        switch (menu) {
            case 1:
                solve_srtf();
                break;
            case 2:
                solve_priority_aging();
                break;
            case 3:
                solve_mlq();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

    } while (menu != 0);

    return 0;
}
