#include <iostream>
#include <limits.h> // For INT_MAX
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findSJF(Process proc[], int n) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = proc[i].burstTime;
    }
    
    int currentTime = 0;
    int complete = 0;

    while (complete < n) {
        int minBurst = INT_MAX;
        int shortest = -1;
        bool foundProcess = false;

        // Find the shortest job that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && remainingTime[i] > 0) {
                foundProcess = true; // At least one process is available
                if (remainingTime[i] < minBurst) {
                    minBurst = remainingTime[i];
                    shortest = i;
                }
            }
        }

        // If no process is found, move the current time to the next arriving process
        if (!foundProcess) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (proc[i].arrivalTime > currentTime) {
                    nextArrival = min(nextArrival, proc[i].arrivalTime);
                }
            }
            currentTime = nextArrival; // Jump to the next arriving process time
            continue; // Re-check the processes after the time update
        }

        // Execute the shortest job
        remainingTime[shortest]--;
        currentTime++;

        // Check if the process is completed
        if (remainingTime[shortest] == 0) {
            complete++;
            proc[shortest].completionTime = currentTime;
            proc[shortest].turnaroundTime = proc[shortest].completionTime - proc[shortest].arrivalTime;
            proc[shortest].waitingTime = proc[shortest].turnaroundTime - proc[shortest].burstTime;
        }
    }
}

// Function to calculate average Turnaround Time
double findAvgTurnaroundTime(Process proc[], int n) {
    int total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_tat += proc[i].turnaroundTime;
    }
    return (double)total_tat / n;
}

// Function to calculate average Waiting Time
double findAvgWaitingTime(Process proc[], int n) {
    int total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].waitingTime;
    }
    return (double)total_wt / n;
}

void printTable(Process proc[], int n) {
    cout << "------------------------------------------------------------------------------------------\n";
    cout << "| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n";
    cout << "------------------------------------------------------------------------------------------\n";


    for (int i = 0; i < n; i++) {
        cout << "|    " << proc[i].pid << "   |      "
             << proc[i].arrivalTime << "      |     "
             << proc[i].burstTime << "        |      "
             << proc[i].completionTime << "      |   "
             << proc[i].turnaroundTime << "        |  "
             << proc[i].waitingTime << "     |\n";
    }

    cout << "-----------------------------------------------------------------------------------------\n";

    // Print average turnaround time and waiting time
    cout << "\nAverage Turnaround Time: " << findAvgTurnaroundTime(proc, n) << endl;
    cout << "Average Waiting Time: " << findAvgWaitingTime(proc, n) << endl;
}


int main() {
    int n;
  cout << "Enter The Number of Process ";
  cin >> n;


    Process proc[n];
    cout << "Enter Process Details(ID, Arrival, Burst)" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Enter Process " << i + 1 << endl;
        cin >> proc[i].pid >> proc[i].arrivalTime >> proc[i].burstTime;
    }
    findSJF(proc, n);
    printTable(proc, n); // Pass the correct array here
    return 0;
}


