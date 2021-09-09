#include <bits/stdc++.h>
using namespace std;

// Structure to model process
struct Process
{
     string PId; // Process ID
     int order; // order of PIDs
     int AT; // Arrival Time
     int BT; // Burst Time
     int CT; // Completion Time
     int TAT; // Turn around Time
     int WT; // Waiting Time
} p[1000];

bool comparison(Process a, Process b)
{
     return (a.AT < b.AT); // Compare by Arrival Time
}

bool comparison1(Process a, Process b)
{
     return (a.order < b.order); // Compare by order
}

void FCFS(int n)
{
     sort(p, p+n, comparison); // Sort by Arrival Time 
     // Calculate CT, TAT, WT for all n processes
     // TAT=CT-AT, WT=TAT-BT
     p[0].CT = p[0].AT + p[0].BT;
     p[0].TAT = p[0].BT;
     p[0].WT = 0;
     for(int i=1; i<n; i++)
     {
     p[i].CT = p[i-1].CT + p[i].BT; 
     p[i].TAT = p[i].CT - p[i].AT;
     p[i].WT = p[i].TAT - p[i].BT;
     }
     sort(p, p+n, comparison1); // Sort by order
}

void displayOutput(int n)
{
     int sumTAT=0, sumWT=0;
     cout << "PID\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT"<< endl;
     for(int i=0; i<n; i++)
     {
          sumTAT += p[i].TAT; // Total TAT
          sumWT += p[i].WT; // Total WT
          cout << p[i].PId << "\t" << p[i].AT << "\t" << p[i].BT << "\t"<< p[i].CT << "\t" << p[i].TAT << "\t" << p[i].WT << endl;
     }
     float avgTAT = (float)sumTAT/(float)n; // Average TAT
     float avgWT = (float)sumWT/(float)n; // Average WT
     cout << fixed << setprecision(2);
     cout << "Average waiting time = " << avgWT <<" µs"<<endl;
     cout << "Average turn around time = " << avgTAT<<" µs" <<endl;
}

int main()
{
     cout << "Enter number of Processes:" << endl;
     int n;
     cin >> n;
     cout << "Enter Process IDs:" << endl;
     for(int i=0; i<n; i++)
     {
          cin>>p[i].PId;
          p[i].order = i;
     }
     cout << "Enter Arrival Times(in µs):" << endl;
     for(int i=0; i<n; i++)
     {
          cin >> p[i].AT;
     }
     cout << "Enter Burst Times(in µs):" << endl;
     for(int i=0; i<n; i++)
     {
          cin >> p[i].BT;
     }
     FCFS(n);
     cout << endl << "Output:" << endl;
     displayOutput(n);
     return 0;
}