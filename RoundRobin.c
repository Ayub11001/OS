#include<stdio.h>

int main() {
    int n = 0, elapsedTime = 0, timeSlice, count = 0;
    int remainingTime[10], waitTime[10], burstTime[10], turnAroundTime[10];
    int totalWaitTime = 0, totalTurnAroundTime = 0;
    float avgWaitTime = 0.0, avgTurnAroundTime = 0.0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
   
    printf("Enter the time slice: ");
    scanf("%d", &timeSlice);

    for(int i=0; i<n; i++) {
        printf("Enter burst-time for process-%d: ", i+1);
        scanf("%d", &burstTime[i]);
        remainingTime[i] = burstTime[i];
    }

    while(1) {
        for(int i=0; i<n; i++) {
            if(remainingTime[i] > 0) {
                if(remainingTime[i] > timeSlice) {
                    elapsedTime += timeSlice;
                    remainingTime[i] -= timeSlice;
                } else {
                    elapsedTime += remainingTime[i];
                    remainingTime[i] = 0;
                    turnAroundTime[i] = elapsedTime;
                    count++;
                }
            }
        }
        if(count == n) {
            break;
        }
    }

    for(int i=0; i<n; i++) {
        waitTime[i] = turnAroundTime[i] - burstTime[i];
        totalWaitTime += waitTime[i];

        totalTurnAroundTime += turnAroundTime[i];
    }

    avgTurnAroundTime = (float)totalTurnAroundTime/n;
    avgWaitTime = (float)totalWaitTime/n;

    printf("\n FCFS Scheduling Results:\n");
    printf("----------------------------------------------\n");
                
    printf("| Process | Burst Time | Waiting | Turnaround |\n");
    printf("|         |   (ms)     |  Time   |   Time     |\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("|   P%-4d |     %-7d|   %-6d|   %-8d|\n",
            i + 1, burstTime[i], waitTime[i], turnAroundTime[i]);
    }

    printf("----------------------------------------------\n");
    printf("| Totals  |             |   %-6d|   %-8d|\n",
        totalWaitTime, totalTurnAroundTime);
    printf("| Averages|             |   %.2f  |   %.2f   |\n",
        avgWaitTime, avgTurnAroundTime);
    printf("----------------------------------------------\n");
}