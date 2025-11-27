# Scheduling Algorithms in Operating Systems
## First-Come, First-Served (FCFS)
The First-Come, First-Served (FCFS) scheduling algorithm is the simplest type
    of CPU scheduling algorithm. In this method, the process that arrives first is executed first. It operates on a queue basis, where processes are lined up in the order they arrive.
### Code
```cpp

void First_Come_First_Served(vector<vector<int>> & p ){
    vector<string> ghantt_chart;
        for(int i=0;i<p.size();i++){
            string a ="P"+to_string(i+1);
            ghantt_chart.push_back(a);
    }
    for(int i=0;i<p.size()-1;i++){
        for(int j=i+1;j<p.size();j++){
            if(p[i][0]>p[j][0]){
                swap(p[i],p[j]);
                swap(ghantt_chart[i], ghantt_chart[j]);
            }
        }
    }
    int n = p.size();
    vector<int> wt(n,0);
    vector<int> tat(n,0);
    vector<int> ct(n,0);
    int avg_wt = 0, avg_tat = 0;
    for(int i=0;i<n;i++){
        if(i==0)ct[i] = p[i][1];
        else ct[i] = ct[i-1] + p[i][1];
        tat[i] = ct[i] - p[i][0];
        wt[i] = tat[i] - p[i][1];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    cout<<"Ghannt Chart: \n";
    for(auto i:ghantt_chart){
        cout<<" | "<<i<<" ";
    }cout<<"| \n";
    cout<<"Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for(int i=0;i<n;i++){
        cout<<i+1<<"\t"<<p[i][0]<<"\t\t"<<p[i][1]<<"\t\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t\t"<<wt[i]<<"\n";
    }
    cout<<"Average Turn Around Time: "<<(float)avg_tat/n<<"\n";
    cout<<"Average Waiting Time: "<<(float)avg_wt/n<<"\n";   
}
int main(){
    vector<vector<int>> processes = {
        {0,2},{0,4},{0,6},{0,1},{0,3}
        // {6, 6}, {2, 2}, {8,8}, {3, 3},{4,4}
        // {1, 4,2}, {2,6,6}, {3,3,4}, {4,7,6},{5,2,7}
        // {1, 4, 4, 2}, {2, 2, 6, 4}, {3, 16, 3, 3}, {4, 3, 9, 1}, {5, 4, 2, 5}
        // {1, 4, 4}, {2, 2, 9}, {3, 0, 6}, {4, 6, 3}
    };
    First_Come_First_Served(processes);
    // sortest_Job_first_non_preemptive(processes);
    // sjf_preemptive(processes);
    // Priority_Scheduling_preemptive(processes);
    // Round_robin_scheduling(processes, 3);
}
```
### OUTPUT
```cpp
Ghannt Chart:
 | P1  | P2  | P3  | P4  | P5 |
Process Arrival Time    Burst Time      Completion Time Turn Around Time        Waiting Time
1       0               2               2               2                       0      
2       0               4               6               6                       2      
3       0               6               12              12                      6      
4       0               1               13              13                      12     
5       0               3               16              16                      13     
Average Turn Around Time: 9.8
Average Waiting Time: 6.6
```
## Shortest Job First (SJF) Non-Preemptive
The Shortest Job First (SJF) Non-Preemptive scheduling algorithm selects the process with the smallest burst time from the set of processes that have arrived and are ready to execute. Once a process starts executing, it runs to completion without being interrupted.
### Code
```cpp

void sortest_Job_first_non_preemptive(vector<vector<int>> & p ){
    // p = {arrival_time, burst_time}
    vector<string> ghantt_chart;
        for(int i=0;i<p.size();i++){
            string a ="P"+to_string(i+1);
            ghantt_chart.push_back(a);
    }

    for(int i=0;i<p.size()-1;i++){
        for(int j=i+1;j<p.size();j++){
            if(p[i][0]>p[j][0]){
                swap(p[i],p[j]);
                swap(ghantt_chart[i], ghantt_chart[j]);
            }
            else if(p[i][0]==p[j][0]){
                if(p[i][1]>p[j][1]){
                    swap(p[i],p[j]);
                    swap(ghantt_chart[i], ghantt_chart[j]);
                }
            }
        }
    }

    int n = p.size();
    vector<int> wt(n,0); 
    vector<int> tat(n,0);
    vector<int> ct(n,0);
    int avg_wt = 0, avg_tat = 0;
    int last_time = 0;
    for(int i=0;i<n;i++){
        if(i==0){
            if( last_time < p[i][0])ct[i] = p[i][1] + p[i][0];
            else ct[i] = last_time + p[i][1];
            last_time = ct[i];
        }
        else{
            if(ct[i-1]<p[i][0])ct[i] = p[i][1] + p[i][0];
            else ct[i] = ct[i-1] + p[i][1];
        }
        tat[i] = ct[i] - p[i][0];
        wt[i] = tat[i] - p[i][1];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    cout<<"Ghannt Chart: \n";
    for(auto i:ghantt_chart){
        cout<<" | "<<i<<" ";
    }cout<<"| \n";
    cout<<"Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for(int i=0;i<n;i++){
        cout<<i+1<<"\t"<<p[i][0]<<"\t\t"<<p[i][1]<<"\t\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t\t"<<wt[i]<<"\n";
    }
    cout<<"Average Turn Around Time: "<<(float)avg_tat/n<<"\n";
    cout<<"Average Waiting Time: "<<(float)avg_wt/n<<"\n";
}
int main(){
    vector<vector<int>> processes = {
        // {0,2},{0,4},{0,6},{0,1},{0,3}
        {6, 6}, {2, 2}, {8,8}, {3, 3},{4,4}
        // {1, 4,2}, {2,6,6}, {3,3,4}, {4,7,6},{5,2,7}
        // {1, 4, 4, 2}, {2, 2, 6, 4}, {3, 16, 3, 3}, {4, 3, 9, 1}, {5, 4, 2, 5}
        // {1, 4, 4}, {2, 2, 9}, {3, 0, 6}, {4, 6, 3}
    };
    // First_Come_First_Served(processes);
    sortest_Job_first_non_preemptive(processes);
    // sjf_preemptive(processes);
    // Priority_Scheduling_preemptive(processes);
    // Round_robin_scheduling(processes, 3);
}
```
### OUTPUT
```cpp
Ghannt Chart: 
 | P2  | P4  | P5  | P1  | P3 | 
Process Arrival Time    Burst Time      Completion Time Turn Around Time        Waiting Time
1       2               2               4               2                       0
2       3               3               7               4                       1
3       4               4               11              7                       3
4       6               6               17              11                      5
5       8               8               25              17                      9
Average Turn Around Time: 8.2
Average Waiting Time: 3.6
```
## Shortest Job First (SJF) Preemptive
The Shortest Job First (SJF) Preemptive scheduling algorithm, also known as Shortest Remaining Time First (SRTF), selects the process with the smallest remaining burst time from the set of processes that have arrived and are ready to execute. If a new process arrives with a burst time less than the remaining time of the currently executing process, the current process is preempted, and the new process is executed.
### Code
```cpp

void sjf_preemptive(vector<vector<int>>&p){
    // p = {process no, arrival_time, burst_time}
    for(int i=0;i<p.size();i++){
        for(int j=i+1;j<p.size();j++){
            if(p[i][1] > p[j][1]){
                swap(p[i], p[j]);
            }
            else if(p[i][1] == p[j][1] && p[i][2] > p[j][2]){
                swap(p[i], p[j]);
            }
        }
    }

    vector<int> remaining_burst_time;
    for(int i=0;i<p.size();i++){
        remaining_burst_time.push_back(p[i][2]);
    }
    vector<string> ghantt_chart;
    int n = p.size();
    vector<int> wt(n,0);
    vector<int> tat(n,0);
    vector<int> ct(n,0);
    int avg_wt = 0, avg_tat = 0;
    int completed = 0, current_time = 0;
    while(completed<n){
        int min_burst_time = INT32_MAX;
        int index = -1;

        for(int i=0;i<n;i++){
             if(p[i][1] <= current_time && remaining_burst_time[i] > 0){

                if(remaining_burst_time[i] < min_burst_time){
                    min_burst_time = remaining_burst_time[i];
                    index = i;
                }

                else if(remaining_burst_time[i] == min_burst_time){
                    if(p[i][1] < p[index][1]){
                        index = i;
                    }
                }
            } 
        }
        if(index==-1){
            current_time++;
        }
        else{
            ghantt_chart.push_back("P"+to_string(p[index][0]));
            remaining_burst_time[index]--;
            current_time++;
            if(remaining_burst_time[index]==0){
                completed++;
                ct[index] = current_time;
                tat[index] = ct[index] - p[index][1];
                wt[index] = tat[index] - p[index][2];
                avg_wt += wt[index];
                avg_tat += tat[index];
            }
        }

    }
    cout<<"Ghannt Chart: \n";
    string last = "";
    for(int i = 0; i < ghantt_chart.size(); i++){
        if(ghantt_chart[i] != last){
            cout << ghantt_chart[i] << " ";
            last = ghantt_chart[i];
        }
    }
    cout << "\n";
    cout<<"Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for(int i=0;i<n;i++){
        cout<<p[i][0]<<"\t"<<p[i][1]<<"\t\t"<<p[i][2]<<"\t\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t\t"<<wt[i]<<"\n";
    }
    cout<<"Average Turn Around Time: "<<(float)avg_tat/n<<"\n";
    cout<<"Average Waiting Time: "<<(float)avg_wt/n<<"\n";

}
int main(){
    vector<vector<int>> processes = {
        // {0,2},{0,4},{0,6},{0,1},{0,3}
        // {6, 6}, {2, 2}, {8,8}, {3, 3},{4,4}
        {1, 4,2}, {2,6,6}, {3,3,4}, {4,7,6},{5,2,7}
        // {1, 4, 4, 2}, {2, 2, 6, 4}, {3, 16, 3, 3}, {4, 3, 9, 1}, {5, 4, 2, 5}
        // {1, 4, 4}, {2, 2, 9}, {3, 0, 6}, {4, 6, 3}
    };
    // First_Come_First_Served(processes);
    // sortest_Job_first_non_preemptive(processes);
    sjf_preemptive(processes);
    // Priority_Scheduling_preemptive(processes);
    // Round_robin_scheduling(processes, 3);
}
```
### OUTPUT
```cpp
Ghannt Chart: 
P5 P3 P1 P3 P5 P2 P4 
Process Arrival Time    Burst Time      Completion Time Turn Around Time        Waiting Time
5       2               7               15              13                      6
3       3               4               9               6                       2
1       4               2               6               2                       0
2       6               6               21              15                      9
4       7               6               27              20                      14
Average Turn Around Time: 11.2
Average Waiting Time: 6.2
```
## Priority Scheduling Preemptive
The Priority Scheduling Preemptive algorithm selects the process with the highest priority (lowest numerical value) from the set of processes that have arrived and are ready to execute. If a new process arrives with a higher priority than the currently executing process, the current process is preempted, and the new process is executed.
### Code
```cpp

void Priority_Scheduling_preemptive(vector<vector<int>> & p ){
    // p = {proccess no, arrival_time, burst_time, priority}
    for(int i=0;i<p.size();i++){
        for(int j=i+1;j<p.size();j++){
            if(p[i][1]>p[j][1]){
                swap(p[i],p[j]);
            }
        }
    }

    vector<int> remaining_burst_time;
    for(int i=0;i<p.size();i++){
        remaining_burst_time.push_back(p[i][2]);
    }

    vector<string> ghantt_chart;
    int n = p.size();
    vector<int> wt(n,0);
    vector<int> tat(n,0);
    vector<int> ct(n,0);
    int avg_wt = 0, avg_tat = 0;
    int completed = 0, current_time = 0;

    while(completed<n){
        int priority_index = INT32_MAX;
        int index = -1;

        for(int i=0;i<n;i++){
            if(p[i][1]<=current_time && remaining_burst_time[i]>0){
                if(p[i][3]<priority_index){
                    priority_index = p[i][3];
                    index = i;
                }
            } 
        }
        if(index==-1){
            current_time++;
        }
        else{
            ghantt_chart.push_back("P"+to_string(p[index][0]));
            remaining_burst_time[index]--;
            current_time++;
            if(remaining_burst_time[index]==0){
                completed++;
                ct[index] = current_time;
                tat[index] = ct[index] - p[index][1];
                wt[index] = tat[index] - p[index][2];
                avg_wt += wt[index];
                avg_tat += tat[index];
            }
        }

    }

    cout<<"Ghannt Chart: \n";
    string last = "";
    for(int i = 0; i < ghantt_chart.size(); i++){
        if(ghantt_chart[i] != last){
            cout << ghantt_chart[i] << " ";
            last = ghantt_chart[i];
        }
    }
    cout << "\n";
    cout<<"Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for(int i=0;i<n;i++){
        cout<<p[i][0]<<"\t"<<p[i][1]<<"\t\t"<<p[i][2]<<"\t\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t\t"<<wt[i]<<"\n";
    }
    cout<<"Average Turn Around Time: "<<(float)avg_tat/n<<"\n";
    cout<<"Average Waiting Time: "<<(float)avg_wt/n<<"\n";
}
int main(){
    vector<vector<int>> processes = {
        // {0,2},{0,4},{0,6},{0,1},{0,3}
        // {6, 6}, {2, 2}, {8,8}, {3, 3},{4,4}
        // {1, 4,2}, {2,6,6}, {3,3,4}, {4,7,6},{5,2,7}
        {1, 4, 4, 2}, {2, 2, 6, 4}, {3, 16, 3, 3}, {4, 3, 9, 1}, {5, 4, 2, 5}
        // {1, 4, 4}, {2, 2, 9}, {3, 0, 6}, {4, 6, 3}
    };
    // First_Come_First_Served(processes);
    // sortest_Job_first_non_preemptive(processes);
    // sjf_preemptive(processes);
    Priority_Scheduling_preemptive(processes);
    // Round_robin_scheduling(processes, 3);
}```
### OUTPUT
```cpp
Ghannt Chart: 
P2 P4 P1 P3 P2 P5
Process Arrival Time    Burst Time      Completion Time Turn Around Time        Waiting Time
2       2               6               24              22                      16     
4       3               9               12              9                       0      
1       4               4               16              12                      8      
5       4               2               26              22                      20     
3       16              3               19              3                       0      
Average Turn Around Time: 13.6
Average Waiting Time: 8.8
```
## Round Robin Scheduling
The Round Robin scheduling algorithm assigns a fixed time quantum to each process in the ready queue. Each process is executed for a time slice equal to the time quantum. If a process does not complete within its time slice, it is preempted and placed at the end of the ready queue, allowing the next process to execute.
### Code
```cpp

void Round_robin_scheduling(vector<vector<int>> & p, int time_quantum ){
    // p = {process no, arrival_time, burst_time}
    for(int i=0;i<p.size();i++){
        for(int j=i+1;j<p.size();j++){
            if(p[i][1]>p[j][1]){
                swap(p[i],p[j]);
            }
        }
    }

    vector<int> remaining_burst_time;
    for(int i=0;i<p.size();i++){
        remaining_burst_time.push_back(p[i][2]);
    }

    vector<string> ghantt_chart;
    int n = p.size();
    vector<int> wt(n,0);
    vector<int> tat(n,0);
    vector<int> ct(n,0);
    int avg_wt = 0, avg_tat = 0;
    
    queue<int> q;
    vector<bool> in_queue(n,false);
    int current_time = 0;
    q.push(0);
    in_queue[0] = true;

    while(!q.empty()){
        int index = q.front();
        q.pop();

        if(remaining_burst_time[index]>time_quantum){
            ghantt_chart.push_back("P"+to_string(p[index][0]));
            current_time += time_quantum;
            remaining_burst_time[index] -= time_quantum;
        }
        else{
            ghantt_chart.push_back("P"+to_string(p[index][0]));
            current_time += remaining_burst_time[index];
            remaining_burst_time[index] = 0;
            ct[index] = current_time;
            tat[index] = ct[index] - p[index][1];
            wt[index] = tat[index] - p[index][2];
            avg_wt += wt[index];
            avg_tat += tat[index];
        }

        for(int i=0;i<n;i++){
            if(p[i][1]<=current_time && !in_queue[i] && remaining_burst_time[i]>0){
                q.push(i);
                in_queue[i] = true;
            }
        }

        if(remaining_burst_time[index]>0){
            q.push(index);
        }
    }

    cout<<"Ghannt Chart: \n";
    string last = "";
    for(int i = 0; i < ghantt_chart.size(); i++){
        if(ghantt_chart[i] != last){
            cout << ghantt_chart[i] << " ";
            last = ghantt_chart[i];
        }
    }
    cout << "\n";
    cout<<"Process\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time\n";
    for(int i=0;i<n;i++){
        cout<<p[i][0]<<"\t"<<p[i][1]<<"\t\t"<<p[i][2]<<"\t\t"<<ct[i]<<"\t\t"<<tat[i]<<"\t\t\t"<<wt[i]<<"\n";
    }
    cout<<"Average Turn Around Time: "<<(float)avg_tat/n<<"\n";
    cout<<"Average Waiting Time: "<<(float)avg_wt/n<<"\n";
}


int main(){
    vector<vector<int>> processes = {
        // {0,2},{0,4},{0,6},{0,1},{0,3}
        // {6, 6}, {2, 2}, {8,8}, {3, 3},{4,4}
        // {1, 4,2}, {2,6,6}, {3,3,4}, {4,7,6},{5,2,7}
        // {1, 4, 4, 2}, {2, 2, 6, 4}, {3, 16, 3, 3}, {4, 3, 9, 1}, {5, 4, 2, 5}
        {1, 4, 4}, {2, 2, 9}, {3, 0, 6}, {4, 6, 3}
    };
    // First_Come_First_Served(processes);
    // sortest_Job_first_non_preemptive(processes);
    // sjf_preemptive(processes);
    // Priority_Scheduling_preemptive(processes);
    Round_robin_scheduling(processes, 3);
}
```
### OUTPUT
```cpp
Ghannt Chart: 
P3 P2 P3 P1 P4 P2 P1 P2
Process Arrival Time    Burst Time      Completion Time Turn Around Time        Waiting Time
3       0               6               9               9                       3      
2       2               9               22              20                      11     
1       4               4               19              15                      11     
4       6               3               15              9                       6      
Average Turn Around Time: 13.25
Average Waiting Time: 7.75
```

