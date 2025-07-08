#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int numberOfPages, numberOfFrames, k = 0, pageFaultCount = 0;
int referenceString[50], frames[10];
bool available;
float hitRatio, missRatio;

int main() {
    printf("Enter number of pages in reference string: ");
    scanf("%d", &numberOfPages);

    printf("Enter number of frames: ");
    scanf("%d", &numberOfFrames);

    printf("Enter the reference string: ");
    for(int i=0; i<numberOfPages; i++) {
        scanf("%d", &referenceString[i]);
    }

    for(int i=0; i<numberOfFrames; i++) 
        frames[i] = -1;

    printf("Page Frames\n");
    
    for(int i=0; i<numberOfPages; i++) {
        available = false;

        for(int j=0; j<numberOfFrames; j++) {
            if(referenceString[i] == frames[j]) {
                available = true; break;
            }    
        }
        if(!available) {
            frames[k] = referenceString[i];
            k = (k+1) % numberOfFrames;
            pageFaultCount++;

            printf("Page falut occured, Updated frames are:\n");
            for(int j=0; j<numberOfFrames; j++) 
                printf("%d ", frames[j]);
            printf("Number of page faults occured are: %d\n", pageFaultCount);    
        }
        printf("\n");
    }
    printf("Total page faults are: %d\n", pageFaultCount);

    missRatio = (float)pageFaultCount / numberOfPages;
    hitRatio = (float)(1-missRatio);
    printf("Miss Ratio is: %.2f\nHit Ratio is: %.2f", missRatio, hitRatio);
}