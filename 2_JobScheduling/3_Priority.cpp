#include <bits/stdc++.h>
using namespace std;
// Structure to model process

struct Process
{
     string PId; // Process ID
     int AT; // Arrival Time
     int BT; // Burst Time
     int remBT; // Remaining burst time
     int PR; // Priority
     int CT; // Completion Time
     int TAT; // Turn around Time
     int WT; // Waiting Time
     int isComplete;
};

// Priority Scheduling(Preemptive)
void PRS(Process p[], int n)
{
     int curr_time = 0; // Current time
     int complete = 0; // Count of completed processes
     while(complete < n) // Iterate while all n processes are completed
     {
          int index = -1;
          int max = -1;
          // Find process with maximum priority among processes that are in ready queue at current time
          for(int i = 0; i < n; i++) 
          {
               if(p[i].AT <= curr_time && p[i].isComplete == 0) 
               {
                    if(p[i].PR > max) 
                    {
                         max = p[i].PR;
                         index = i;
                    }
                    // Resolve priority conflict with arrival time
                    if(p[i].PR == max) 
                    {
                         if(p[i].AT < p[index].AT) 
                         { 
                              max = p[i].PR;
                              index = i;
                         }
                    }
               }
          }
          // If such process is found
          if(index >= 0) 
          {
               // With increase in current time decrease remaining burst
               time
               p[index].remBT--;
               curr_time++;
               
               if(p[index].remBT == 0) 
               {
                    // Calculate CT, TAT, WT
                    // TAT=CT-AT, WT=TAT-BT
                    p[index].CT = curr_time;
                    p[index].TAT = p[index].CT - p[index].AT;
                    p[index].WT = p[index].TAT- p[index].BT;
                    p[index].isComplete = 1; // Mark process as
                    completed 
                    complete++; // Update completed count
               }
          }
          else 
          {
               curr_time++;
          } 
     }
}

void displayOutput(Process p[], int n)
{
     int sumTAT=0, sumWT=0;
     cout << "PID\t" << "AT\t" << "BT\t" << "PR\t" <<"CT\t" << "TAT\t" << "WT\n";
     for(int i=0; i<n; i++)
     {
          sumTAT += p[i].TAT; // Total TAT
          sumWT += p[i].WT; // Total WT
          cout << p[i].PId << "\t" << p[i].AT << "\t" << p[i].BT << "\t"<< p[i].PR << "\t" << p[i].CT << "\t" << p[i].TAT << "\t" << p[i].WT<< endl;
     }
     float avgTAT = (float)sumTAT/(float)n; // Average TAT
     float avgWT = (float)sumWT/(float)n; // Average WT
     cout << fixed << setprecision(2);
     cout << "Average waiting time = " << avgWT <<" µs"<<endl;
     cout << "Average turn around time = " << avgTAT <<" µs"<<endl;
}

int main()
{
     cout << "Enter number of Processes:" << endl;
     int n;
     cin >> n;
     Process p[n];
     cout << "Enter Process IDs:" << endl;
     for(int i=0; i<n; i++)
     {
          cin >> p[i].PId;
          p[i].CT = 0;
          p[i].isComplete = 0;
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
          p[i].remBT = p[i].BT;
     }
     cout << "Enter Priorities:" << endl;
     for(int i=0; i<n; i++)
     {
          cin >> p[i].PR;
     }
     PRS(p, n);
     cout << endl << "Output:" << endl;
     displayOutput(p, n);
     return 0;
}