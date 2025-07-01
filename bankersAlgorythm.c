#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int maxResources[10][10], neededResources[10][10], allocatedResources[10][10], availableResources[10], executedProcesses[10], safeProcesses[10];
int safeProcessCount = 0, processCount = 0, resourceCount = 0;

void calculateNeededResources();
int bankerAlgorithm();

int main() {

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &processCount, &resourceCount);

    for(int i=0; i<processCount; i++) {
        executedProcesses[i] = 0;
    }

    printf("Enter maximun resources and allocated resources\n");
    for(int processes=0; processes<processCount; processes++) {
        for(int resource=0; resource<resourceCount; resource++) {
            printf("Maximum resource required for Process - %d, Resource - %d: ", processes, resource);
            scanf("%d", &maxResources[processes][resource]);

            printf("Resource already allocated for Process - %d, Resource - %d: ", processes, resource);
            scanf("%d", &allocatedResources[processes][resource]);
            printf("\n");
        }        
    }

    printf("Enter available resources: \n");
    for(int i=0; i<resourceCount; i++) {
        printf("Resource - %d: ", i);
        scanf("%d", &availableResources[i]);
    }

    calculateNeededResources();

    int processesId;
    while((processesId = bankerAlgorithm()) != -1) {
        if(processesId != -1) {
            safeProcesses[safeProcessCount++] = processesId;
            for(int j=0; j<resourceCount; j++) {
                availableResources[j] += allocatedResources[processesId][j];
                allocatedResources[processesId][j] = 0;
                maxResources[processesId][j] = 0;
            }
            executedProcesses[processesId] = 1;
        }
    }    
    if(processCount == safeProcessCount) {
        printf("The system is in safe state, the Safe Sequence is: \n");
        for(int i=0; i<processCount; i++) printf("%2d", safeProcesses[i]);
    } else {
        printf("The system is not in safe state!!");
    }
}


void calculateNeededResources() {
    for(int i=0; i<processCount; i++){
        for(int j=0; j<resourceCount; j++){
            neededResources[i][j] = maxResources[i][j] - allocatedResources[i][j];
        }
    }
}

int bankerAlgorithm() {
    int processesId = -1;

    printf("Availabel resources are: ");
    for(int i=0; i<resourceCount; i++)
        printf("%2d", availableResources[i]);

    printf("\n%-15s", "Process");
    for (int j = 0; j < resourceCount; j++) {
        printf("Max[%d] ", j);
    }
    for (int j = 0; j < resourceCount; j++) {
        printf("Alloc[%d] ", j);
    }
    printf("\n");

    for (int i = 0; i < processCount; i++) {
        printf("P%-14d", i);
        for (int j = 0; j < resourceCount; j++) {
            printf("%-8d", maxResources[i][j]);
        }
        for (int j = 0; j < resourceCount; j++) {
            printf("%-10d", allocatedResources[i][j]);
        }
        printf("\n");
    }  

    for(int processes=0; processes<processCount; processes++) {
        if(!executedProcesses[processes]) {
            processesId = processes;

            for(int resource=0; resource<resourceCount; resource++) {
                if(availableResources[resource] < neededResources[processes][resource]) {
                    processesId = -1;
                    break;
                }
            }
        }
        if(processesId != -1) break;
    }
         
    return processesId;
}
