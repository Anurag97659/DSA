#include<iostream>
#include<vector>
using namespace std;


void Priority_Scheduling(vector<vector<int>> & p ){
    // p = {proccess no, arrival_time, burst_time, priority}
    for(int i=0;i<p.size();i++){
        for(int j=i+1;j<p.size();j++){
            if(p[i][1]>p[j][1]){
                swap(p[i],p[j]);
            }
        }
    }

    vector<int> rwt;
    for(int i=0;i<p.size();i++){
        rwt.push_back(p[i][2]);
    }

    int n = p.size();
    vector<int> wt(n,0);
    vector<int> tat(n,0);
    vector<int> ct(n,0);
    int avg_wt = 0;
    int avg_tat = 0;
    int c = 0;
    int current = 0;

    while(c<n){
        int priority_j = INT32_MAX;
        int j = -1;

        for(int i=0;i<n;i++){
            if(p[i][1]<=current && rwt[i]>0){
                if(p[i][3]<priority_j){
                    priority_j = p[i][3];
                   j = i;
                }
            } 
        }
        if(j==-1){
            current++;
        }
        else{
            rwt[j]--;
            current++;
            if(rwt[j]==0){
               c++;
                ct[j] = current;
                tat[j] = ct[j] - p[j][1];
                wt[j] = tat[j] - p[j][2];
                avg_wt += wt[j];
                avg_tat += tat[j];
            }
        }

    }

   
    cout<<"Average Turn Around Time: "<<(float)avg_tat/n<<"\n";
    cout<<"Average Waiting Time: "<<(float)avg_wt/n<<"\n";
}

int main(){
    vector<vector<int>> processes = {{1, 4, 4, 2}, {2, 2, 6, 4}, {3, 16, 3, 3}, {4, 3, 9, 1}, {5, 4, 2, 5}};
    Priority_Scheduling(processes);
}