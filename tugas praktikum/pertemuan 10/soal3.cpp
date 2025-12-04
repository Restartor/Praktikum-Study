#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

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
        p[i].name = "P" + to_string(i + 1);  // <- AUTO NAME
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
                    p[current_index].response_time = time - p[current_index].arrival_time;
            }
            else if (!q_fcfs.empty()) {
                current_index = q_fcfs.front(); q_fcfs.erase(q_fcfs.begin());
                current_queue = 2;
                segment_start = time;
                if (p[current_index].response_time == -1)
                    p[current_index].response_time = time - p[current_index].arrival_time;
            }
            else {
                int next_arrival = -1;
                for (int i = 0; i < n; i++)
                    if (p[i].remaining_time > 0 && p[i].arrival_time > time)
                        if (next_arrival == -1 || p[i].arrival_time < next_arrival)
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

    cout << "\n===== GANTT CHART =====\n";
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
            int left = (width - label.size()) / 2;
            int right = width - label.size() - left;
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

    cout << "\n===== TABEL HASIL =====\n";
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
    cout << "\nAvg WT  = " << total_wt / n << "\n";
}


int main() {
    solve_mlq();
    return 0;
}
