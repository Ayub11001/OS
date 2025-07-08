#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int numberOfPages, numberOfFrames, pageFaultCount = 0;
int referenceString[50], frames[10], lastUsed[10];
bool pageHitStatus[50], available = false;

int main() {
    printf("Enter number of pages in reference string: ");
    scanf("%d", &numberOfPages);

    printf("Enter number of frames: ");
    scanf("%d", &numberOfFrames);

    printf("Enter the reference string: ");
    for(int i=0; i<numberOfPages; i++) {
        scanf("%d", &referenceString[i]);
    }

    for(int i=0; i<numberOfFrames; i++) {
        frames[i] = -1;
        lastUsed[i] = 0;
    } 

    for(int i = 0; i < numberOfPages; i++) {
        pageHitStatus[i] = false;
    }

    printf("Page Frames: \n");

    for(int i=0; i<numberOfPages; i++) {
        for(int j=0; j<numberOfFrames; j++) {
            if(frames[j] == referenceString[i]) {
                lastUsed[j] = i;
                pageHitStatus[i] = true; break;
            }
        }

        if(!pageHitStatus[i]) {
            bool isReplaced = false;
            
            for(int j=0; j<numberOfFrames; j++) {
                if(frames[j] == -1) {
                    frames[j] = referenceString[i];
                    lastUsed[j] = i;
                    isReplaced = true;
                    pageFaultCount++; break;
                }
            }

            if(!isReplaced) {
                int min = 0;
                for(int j=0; j<numberOfFrames; j++) {
                    if(lastUsed[min] > lastUsed[j]) {
                        min = j;
                    }
                }
                frames[min] = referenceString[i];
                lastUsed[min] = i;
                pageFaultCount++;
            }
        }

        for(int j=0; j<numberOfFrames; j++) {
            if(frames[j] != -1) {
                printf("%d ", frames[j]);
            } else printf("- ");
        }

        if(!pageHitStatus[i]) {printf("Number of page faults: %d", pageFaultCount);} else {printf("There is no page fault");}
        printf("\n");
    }

    printf("Total page faults are: %d\n", pageFaultCount);
    float missRatio = (float)pageFaultCount / numberOfPages;
    float hitRatio = (float)(1 - missRatio);

    printf("The Miss Ratio is: %.2f\nThe Hit Ratio is: %.2f", missRatio, hitRatio);
        
}