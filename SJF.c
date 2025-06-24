#include<stdio.h>

int main() {
    int n = 0, temp;
    int waitTime[10], burstTime[10], turnAroundTime[10], processIds[10];
    int totalWaitTime = 0, totalTurnAroundTime = 0;
    float avgWaitTime = 0.0, avgTurnAroundTime = 0.0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        printf("Enter burst-time for process-%d: ", i+1);
        scanf("%d", &burstTime[i]);
        processIds[i] = i;
    }

    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(burstTime[j] < burstTime[i]) {
                temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;

                temp = processIds[i];
                processIds[i] = processIds[j];
                processIds[j] = temp;
            }
        }
    }

        waitTime[0] = 0;
    for(int i=1; i<n; i++) {
        waitTime[i] = waitTime[i-1] + burstTime[i-1];
        totalWaitTime += waitTime[i];
    }

    for(int i=0; i<n; i++) {
        turnAroundTime[i] = waitTime[i] + burstTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    avgTurnAroundTime = totalTurnAroundTime/n;
    avgWaitTime = totalWaitTime/n;

    // Display the result in a formatted table
    printf("\n FCFS Scheduling Results:\n");
    printf("----------------------------------------------\n");
                
    printf("| Process | Burst Time | Waiting | Turnaround |\n");
    printf("|         |   (ms)     |  Time   |   Time     |\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("|   P%-4d |     %-7d|   %-6d|   %-8d|\n",
            processIds[i] + 1, burstTime[i], waitTime[i], turnAroundTime[i]);
    }

    printf("----------------------------------------------\n");
    printf("| Totals  |             |   %-6d|   %-8d|\n",
        totalWaitTime, totalTurnAroundTime);
    printf("| Averages|             |   %.2f  |   %.2f   |\n",
        avgWaitTime, avgTurnAroundTime);
    printf("----------------------------------------------\n");
    
}  
  