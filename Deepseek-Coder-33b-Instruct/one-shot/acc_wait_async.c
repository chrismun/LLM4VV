#include <stdio.h>
#include <openacc.h>

int main() {
    int a[100], b[100];

    // Initialize arrays
    for(int i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Start a data region
    #pragma acc data copyin(a[0:100]) copyout(b[0:100])
    {
        // Start a task that will wait for the other to finish
        #pragma acc wait
        {
            // Start a task that will run asynchronously
            #pragma acc async
            {
                // Copy the values from a to b
                for(int i = 0; i < 100; i++) {
                    b[i] = a[i];
                }
            }
        }
    }

    // Print the results
    for(int i = 0; i < 100; i++) {
        printf("b[%d] = %d\n", i, b[i]);
    }

    return 0;
}