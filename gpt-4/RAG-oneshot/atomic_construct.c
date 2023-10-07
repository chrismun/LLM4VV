#include <stdio.h>
#include <openacc.h>

int main() {
    int n = 10000;
    int counter = 0;

    #pragma acc parallel num_gangs(100) vector_length(32) copy(counter)
    {
        #pragma acc loop gang vector reduction(+:counter)
        for (int i = 0; i < n; i++) {
            #pragma acc atomic
            counter += 1;
        }
    }

    if (counter != n) {
        printf("Test failed! Counter = %d, expected %d\n", counter, n);
        return 1;
    } else {
        printf("Test passed! Counter = %d\n", counter);
        return 0;
    }
}