#include <bits/stdc++.h>
using namespace std;

// Structure to model process
struct Process
{
     string PId; // Process ID
     int order; // order of PIDs
     int AT; // Arrival Time
     int BT; // Burst Time
     int remBT; // Remaining burst time
     int CT; // Completion Time
     int TAT; // Turn around Time
     int WT; // Waiting Time
     int isInQ; // Mark presence in Ready queue 
};

bool comparison(Process a, Process b)
{
     return (a.AT < b.AT); // Compare by Arrival Time
}
bool comparison1(Process a, Process b)
{
     return (a.order < b.order); // Compare by order
}

// Round Robin Scheduling
void RRS(Process p[], int n, int TQ)
{
     sort(p, p+n, comparison); // Sort by Arrival Time 
     queue<int> readyQ; // Ready Queue
     readyQ.push(0);
     p[0].isInQ = 1;
     int curr_time = 0; // Current time
     int complete = 0; // Count of completed processes
     
     while(complete < n) // Iterate while all n processes are completed
     {
          // Pick process from ready queue
          int index = readyQ.front();
          readyQ.pop();
          if(p[index].remBT == p[index].BT)
          {
               curr_time = max(curr_time, p[index].AT);
          }
          if(p[index].remBT-TQ > 0) 
          {
               p[index].remBT -= TQ;
               curr_time += TQ;
          }
          else 
          {
               curr_time += p[index].remBT;
               p[index].remBT = 0;
               complete++;
               // Calculate CT, TAT, WT
               // TAT=CT-AT, WT=TAT-BT
               p[index].CT = curr_time;
               p[index].TAT = p[index].CT - p[index].AT;
               p[index].WT= p[index].TAT - p[index].BT;
          }
          // Putting processes in ready queue
          for(int i = 1; i < n; i++) 
          {
               if(p[i].remBT > 0 && p[i].AT <= curr_time && p[i].isInQ== 0) 
               {
                    readyQ.push(i);
                    p[i].isInQ = 1;
               }
          }
          if(p[index].remBT > 0) 
          {
               readyQ.push(index);
          }
          if(readyQ.empty()) 
          {
               for(int i = 1; i < n; i++) 
               {
                    if(p[i].remBT > 0) 
                    {
                         readyQ.push(i);
                         p[i].isInQ = 1;
                         break;
                    }
               }
          }
     }
     sort(p, p+n, comparison1); // Sort by order
}

void displayOutput(Process p[], int n)
{
     int sumTAT=0, sumWT=0;
     cout << "PID\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" <<
     "WT\n";
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
          p[i].isInQ = 0;
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
          p[i].remBT = p[i].BT;
     }
     cout << "Enter Time Quantum(in µs):" << endl;
     int TQ;
     cin >> TQ;
     RRS(p, n, TQ);
     cout << endl << "Output:" << endl;
     displayOutput(p, n);
     return 0;
}