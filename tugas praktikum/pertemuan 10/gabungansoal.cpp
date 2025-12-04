#include <iostream>
#include <vector>
using namespace std;

/* ============================================================
   SOAL 1 — SRTF
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

    struct Gantt {
        int start_time;
        int end_time;
        int proc_index;
    };

    int n;
    cout << "\n===== SOAL 1 — SRTF =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++){
        cout << "\nNama proses: "; cin >> p[i].name;
        cout << "Arrival time: "; cin >> p[i].arrival_time;
        cout << "Burst time: "; cin >> p[i].burst_time;
        p[i].remaining_time = p[i].burst_time;
        p[i].response_time = -1;
    }

    int time = 1e9;
    for(int i = 0; i < n; i++)
        if(p[i].arrival_time < time) time = p[i].arrival_time;

    int done = 0;
    vector<Gantt> gantt;
    int active_index = -1, segment_start = time;
    int preempt_count = 0;

    while(done < n){
        int select_index = -1, min_rem = 1e9;

        for(int i = 0; i < n; i++)
            if(p[i].arrival_time <= time && p[i].remaining_time > 0 &&
               p[i].remaining_time < min_rem){
                min_rem = p[i].remaining_time;
                select_index = i;
            }

        if(select_index == -1){
            int next_time = 1e9;
            for(int i = 0; i < n; i++)
                if(p[i].remaining_time > 0 &&
                   p[i].arrival_time > time &&
                   p[i].arrival_time < next_time)
                    next_time = p[i].arrival_time;

            if(active_index != -1)
                gantt.push_back({segment_start, time, active_index});

            gantt.push_back({time, next_time, -1});
            time = next_time;
            segment_start = time;
            active_index = -1;
            continue;
        }

        if(select_index != active_index){
            if(active_index != -1) {
                gantt.push_back({segment_start, time, active_index});
                if(p[active_index].remaining_time > 0)
                    preempt_count++;
            }
            active_index = select_index;
            segment_start = time;
            if(p[active_index].response_time == -1)
                p[active_index].response_time = time - p[active_index].arrival_time;
        }

        p[select_index].remaining_time--;
        time++;

        if(p[select_index].remaining_time == 0){
            p[select_index].completion_time = time;
            done++;
        }
    }

    if(active_index != -1)
        gantt.push_back({segment_start, time, active_index});

    double avg_tat = 0, avg_wt = 0, avg_rt = 0;
    for(int i = 0; i < n; i++){
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        avg_tat += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
        avg_rt += p[i].response_time;
    }

    cout << "\n-- GANTT CHART --\n";
    for(auto &g : gantt){
        cout << "[" << g.start_time << "-" << g.end_time << "] ";
        if(g.proc_index == -1) cout << "IDLE";
        else cout << p[g.proc_index].name;
        cout << "  ";
    }

    cout << "\n\nNama\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(int i = 0; i < n; i++)
        cout << p[i].name << "\t"
             << p[i].arrival_time << "\t"
             << p[i].burst_time << "\t"
             << p[i].completion_time << "\t"
             << p[i].turnaround_time << "\t"
             << p[i].waiting_time << "\t"
             << p[i].response_time << "\n";

    cout << "\nPreemption: " << preempt_count << "\n";
}


/* ============================================================
   SOAL 2 — PRIORITY PREEMPTIVE + AGING
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

    struct Gantt { int start, end, proc_index; };

    int n;
    cout << "\n===== SOAL 2 — PRIORITY PREEMPTIVE + AGING =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);
    for(int i = 0; i < n; i++){
        cout << "\nNama proses: "; cin >> p[i].name;
        cout << "Arrival time: "; cin >> p[i].arrival_time;
        cout << "Burst time: "; cin >> p[i].burst_time;
        cout << "Priority (lebih kecil = lebih tinggi): ";
        cin >> p[i].priority_value;
        p[i].current_priority = p[i].priority_value;
        p[i].remaining_time = p[i].burst_time;
        p[i].response_time = -1;
        p[i].aging_counter = 0;
    }

    int time = 1e9;
    for(int i = 0; i < n; i++)
        if(p[i].arrival_time < time) time = p[i].arrival_time;

    int done = 0;
    vector<Gantt> gantt;
    int active = -1, seg_start = time;
    int preempt = 0, priority_changes = 0;

    while(done < n){
        int select = -1, best = 1e9;

        for(int i = 0; i < n; i++)
            if(p[i].arrival_time <= time &&
               p[i].remaining_time > 0 &&
               p[i].current_priority < best){
                best = p[i].current_priority;
                select = i;
            }

        if(select == -1){
            int next = 1e9;
            for(int i = 0; i < n; i++)
                if(p[i].remaining_time > 0 &&
                   p[i].arrival_time > time &&
                   p[i].arrival_time < next)
                    next = p[i].arrival_time;

            if(active != -1) gantt.push_back({seg_start, time, active});
            gantt.push_back({time, next, -1});
            time = next;
            seg_start = time;
            active = -1;
            continue;
        }

        if(select != active){
            if(active != -1){
                gantt.push_back({seg_start, time, active});
                if(p[active].remaining_time > 0) preempt++;
            }
            active = select;
            seg_start = time;
            if(p[select].response_time == -1)
                p[select].response_time = time - p[select].arrival_time;
        }

        for(int i = 0; i < n; i++)
            if(p[i].remaining_time > 0 && p[i].arrival_time <= time){
                if(i == select) p[i].aging_counter = 0;
                else{
                    p[i].aging_counter++;
                    if(p[i].aging_counter > 5){
                        int old = p[i].current_priority;
                        p[i].current_priority--;
                        if(p[i].current_priority < 0) p[i].current_priority = 0;
                        if(old != p[i].current_priority) priority_changes++;
                        p[i].aging_counter = 0;
                    }
                }
            }

        p[select].remaining_time--;
        time++;

        if(p[select].remaining_time == 0){
            p[select].completion_time = time;
            done++;
        }
    }

    if(active != -1) gantt.push_back({seg_start, time, active});

    double avg_tat = 0, avg_wt = 0, avg_rt = 0;
    for(int i = 0; i < n; i++){
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        avg_tat += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
        avg_rt += p[i].response_time;
    }

    cout << "\n-- GANTT CHART --\n";
    for(auto &g : gantt){
        cout << "[" << g.start << "-" << g.end << "] ";
        if(g.proc_index == -1) cout << "IDLE";
        else cout << p[g.proc_index].name;
        cout << "  ";
    }

    cout << "\n\nNama\tAT\tBT\tPrAwal\tPrAkhir\tCT\tTAT\tWT\tRT\n";
    for(int i = 0; i < n; i++)
        cout << p[i].name << "\t"
             << p[i].arrival_time << "\t"
             << p[i].burst_time << "\t"
             << p[i].priority_value << "\t"
             << p[i].current_priority << "\t"
             << p[i].completion_time << "\t"
             << p[i].turnaround_time << "\t"
             << p[i].waiting_time << "\t"
             << p[i].response_time << "\n";

    cout << "\nPreemption: " << preempt;
    cout << "\nPriority changes (aging): " << priority_changes << "\n";
}


/* ============================================================
   SOAL 3 — MULTI LEVEL QUEUE (RR + FCFS)
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

    struct Gantt { int start, end, proc, q; };

    int n;
    cout << "\n===== SOAL 3 MLQ =====\n";
    cout << "Masukkan jumlah proses: ";
    cin >> n;

    vector<Process> p(n);
    for(int i = 0; i < n; i++){
        cout << "\nNama proses: "; cin >> p[i].name;
        cout << "Arrival time: "; cin >> p[i].arrival_time;
        cout << "Burst time: "; cin >> p[i].burst_time;
        cout << "Queue (1=RR, 2=FCFS): "; cin >> p[i].queue_level;
        p[i].remaining_time = p[i].burst_time;
        p[i].response_time = -1;
    }

    vector<int> q_rr, q_fcfs;
    vector<Gantt> gantt;

    int time = 0, done = 0;
    int current = -1, qlvl = -1;
    int quantum_left = 0, segment_start = 0;
    const int quantum = 2;

    while(done < n){

        for(int i = 0; i < n; i++)
            if(p[i].arrival_time == time)
                (p[i].queue_level == 1) ? q_rr.push_back(i) : q_fcfs.push_back(i);

        int next = -1;
        if(!q_rr.empty()){
            if(current == -1 || qlvl == 2){
                next = q_rr.front(); q_rr.erase(q_rr.begin());
                quantum_left = quantum;
                qlvl = 1;
            } else next = current;
        }
        else if(!q_fcfs.empty()){
            if(current == -1 || qlvl == 1){
                next = q_fcfs.front(); q_fcfs.erase(q_fcfs.begin());
                qlvl = 2;
            } else next = current;
        }

    // ================= CPU IDLE HANDLING (ANTI CRASH 100%) =================
    if (next == -1) {

        // Tutup segmen proses sebelumnya
        if(current != -1){
            gantt.push_back({segment_start, time, current, qlvl});
            current = -1;
        }

        // Cari waktu arrival berikutnya
        int next_arrival = -1;
        for(int i = 0; i < n; i++)
            if(p[i].remaining_time > 0 && p[i].arrival_time > time)
                if(next_arrival == -1 || p[i].arrival_time < next_arrival)
                    next_arrival = p[i].arrival_time;

        // Jika tidak ada proses tersisa, keluar dari loop
        if(next_arrival == -1) break;

        // Tambahkan idle ke gantt
        gantt.push_back({time, next_arrival, -1, -1});

        time = next_arrival;
        segment_start = time;
        continue;
    }
    // =======================================================================



        if(next != current){
            if(current != -1) gantt.push_back({segment_start, time, current, qlvl});
            current = next;
            segment_start = time;
        }

        if(p[current].response_time == -1)
            p[current].response_time = time - p[current].arrival_time;

        p[current].remaining_time--;
        time++;
        if(qlvl == 1) quantum_left--;

        if(p[current].remaining_time == 0){
            p[current].completion_time = time;
            gantt.push_back({segment_start, time, current, qlvl});
            done++;
            current = -1;
        }
        else if(qlvl == 1 && quantum_left == 0){
            q_rr.push_back(current);
            gantt.push_back({segment_start, time, current, qlvl});
            current = -1;
        }
    }

    double avg_tat = 0, avg_wt = 0;
    for(int i = 0; i < n; i++){
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        avg_tat += p[i].turnaround_time;
        avg_wt += p[i].waiting_time;
    }

    cout << "\n-- GANTT CHART --\n";
    for(auto &g : gantt)
        cout << "[" << g.start << "-" << g.end << "] "
             << p[g.proc].name << "(Q" << g.q << ")  ";

    cout << "\n\nNama\tAT\tBT\tQ\tCT\tTAT\tWT\tRT\n";
    for(int i = 0; i < n; i++)
        cout << p[i].name << "\t"
             << p[i].arrival_time << "\t"
             << p[i].burst_time << "\t"
             << p[i].queue_level << "\t"
             << p[i].completion_time << "\t"
             << p[i].turnaround_time << "\t"
             << p[i].waiting_time << "\t"
             << p[i].response_time << "\n";

    cout << "\nAvg TAT = " << avg_tat / n;
    cout << "\nAvg WT  = " << avg_wt / n << "\n";
}


/* ============================================================
   MAIN MENU
   ============================================================ */
int main(){
    int menu;
    do{
        cout << "\n\n===== MENU SOAL =====\n";
        cout << "1. SRTF\n";
        cout << "2. Priority Preemptive + Aging\n";
        cout << "3. MLQ (RR + FCFS)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> menu;

        if(menu == 1) solve_srtf();
        else if(menu == 2) solve_priority_aging();
        else if(menu == 3) solve_mlq();

    } while(menu != 0);

    return 0;
}
