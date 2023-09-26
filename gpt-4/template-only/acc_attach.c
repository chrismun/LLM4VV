#include <stdlib.h>
#include <openacc.h>

#define ARRAY_SIZE 1000
#define VALUE 100

int main(int argc, char *argv[]) {
    int a[ARRAY_SIZE];
    int isSuccess = 1;

    // Initialize array on host
    for (int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = i;
    }

    #pragma acc data copyin(a) // This directive moves the data from host to device
    {
        #pragma acc parallel loop // This directive means that loop iteration should be executed in parallel
        for (int i = 0; i < ARRAY_SIZE; i++) {
            a[i] += VALUE;
        }
    } // When the program exits this section, it will copy the data back from device to host

    // Check whether the computations were executed correctly.
   for (int i = 0; i < ARRAY_SIZE; i++) {
        if(a[i] != i + VALUE) {
            isSuccess = 0;
            break;
        }
   }

   if(isSuccess) {
       printf("Test passed\n");
       return 0;
   } else {
       printf("Test failed\n");
       return 1;
   }
}