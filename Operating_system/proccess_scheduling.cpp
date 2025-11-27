#include <iostream>
#include <vector>
#include <queue>
using namespace std;

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

void sortest_Job_first_non_preemptive(vector<vector<int>> & p ){
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

// Priority Scheduling non Preemptive is similar to first come first served only difference is we have to sort based on priority instead of arrival time

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
        {1, 4, 4},
        {2, 2, 9},
        {3, 0, 6},
        {4, 6, 3}
    };
    Round_robin_scheduling(processes, 3);
    

}