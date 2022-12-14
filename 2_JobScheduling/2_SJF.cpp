#include <bits/stdc++.h>
using namespace std;

// Structure to model process
struct Process
{
     string PId; // Process ID
     int AT; // Arrival Time
     int BT; // Burst Time
     int CT; // Completion Time
     int TAT; // Turn around Time
     int WT; // Waiting Time
} p[1000];

void SJF(int n)
{
     int index = -1; // Index of process to schedule
     int complete = 0; // Count of completed processes
     int curr_time = 0; // Current time
     int min = INT_MAX;
     while(complete < n) // Iterate while all n processes are completed
     {
          // Find process with minimum burst time among processes that are in ready queue at current time
          for(int i=0; i<n; i++)
          {
               if(p[i].AT <= curr_time)
               {
                    if(p[i].BT < min && p[i].CT == 0)
                    {
                         index = i; // Set index
                         min = p[i].BT; // Update min
                    }
               }
          }
          // If such process is found
          if(index >= 0)
          {
               // Calculate CT, TAT, WT
               // TAT=CT-AT, WT=TAT-BT
               curr_time += p[index].BT;
               p[index].CT = curr_time;
               p[index].TAT = p[index].CT - p[index].AT;
               p[index].WT = p[index].TAT - p[index].BT;
               complete++; // Update completed count
               min = INT_MAX; // Reset min
               index = -1; // Reset index
          }
          else
          {
               curr_time++;
          }
     }
}

void displayOutput(int n)
{
     int sumTAT=0, sumWT=0;
     cout << "PID\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" <<"WT\n";
     for(int i=0; i<n; i++)
     {
          sumTAT += p[i].TAT; // Total TAT
          sumWT += p[i].WT; // Total WT
          cout << p[i].PId << "\t" << p[i].AT << "\t" << p[i].BT << "\t"<< p[i].CT << "\t" << p[i].TAT << "\t" << p[i].WT << endl;
     }
     float avgTAT = (float)sumTAT/(float)n; // Average TAT
     float avgWT = (float)sumWT/(float)n; // Average WT
     cout << fixed << setprecision(2);
     cout << "Average waiting time = " << avgWT <<" ??s"<<endl;
     cout << "Average turn around time = " << avgTAT <<" ??s"<<endl;
}

int main()
{
     cout << "Enter number of Processes:" << endl;
     int n;
     cin >> n;
     cout << "Enter Process IDs:" << endl;
     for(int i=0; i<n; i++)
     {
          cin >> p[i].PId;
     }
     cout << "Enter Arrival Times(in ??s):" << endl;
     for(int i=0; i<n; i++)
     {
          cin >> p[i].AT;
     }
     cout << "Enter Burst Times(in ??s):" << endl;
     for(int i=0; i<n; i++)
     {
          cin >> p[i].BT;
     }
     SJF(n);
     cout << endl << "Output:" << endl;
     displayOutput(n);
     return 0;
}