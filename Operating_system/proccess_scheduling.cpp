#include <iostream>
#include <vector>
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

// Priority Scheduling non Preemptive is similar to first come first served only difference is we have to sort based on priority instead of arrival time
void Priority_Scheduling_preemptive(vector<vector<int>> & p ){
    // p = {arrival_time, burst_time, priority}
    

}
int main(){
    vector<vector<int>> processes = {
       {4, 2},
       {6, 6},
       {3, 4},
       {7, 6},
       {2, 7} 
    };
    sortest_Job_first_non_preemptive(processes);
    

}