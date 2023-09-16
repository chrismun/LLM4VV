#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_POINTERS 10
#define INITIAL_VALUE 10

int main(){
    int *pointers[NUM_POINTERS];
    int attachment_counters[NUM_POINTERS];
    int i;

    // Allocate memory and initialize attachment counters
    for(i = 0; i < NUM_POINTERS; i++){
        pointers[i] = (int*)acc_malloc(sizeof(int));
        *pointers[i] = INITIAL_VALUE;
        attachment_counters[i] = 0;
    }

    // Attach pointers and update attachment counters
    for(i = 0; i < NUM_POINTERS; i++){
        #pragma acc enter data copyin(pointers[i][0:1])
        attachment_counters[i]++;
    }

    // Detach pointers and update attachment counters
    for(i = 0; i < NUM_POINTERS; i++){
        #pragma acc exit data delete(pointers[i][0:1])
        attachment_counters[i]--;
    }

    // Check if attachment counters are updated correctly
    for(i = 0; i < NUM_POINTERS; i++){
        if(attachment_counters[i] != 0){
            printf("Test failed: attachment counter for pointer %d is %d, expected 0\n", i, attachment_counters[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}