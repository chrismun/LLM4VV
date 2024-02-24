#include <stdio.h>
#include <openacc.h>

#define N 1000000

int main() {
    int i, a[N];

    // Initialize array
    for (i = 0; i < N; i++) {
        a[i] = 0;
    }

    // Parallelize loop with OpenACC
    #pragma acc parallel loop
    for (i = 0; i < N; i++) {
        // Use atomic construct to ensure atomic increment
        #pragma acc atomic
        a[i]++;
    }

    // Check if all elements are incremented
    for (i = 0; i < N; i++) {
        if (a[i] != 1) {
            printf("Atomic construct not working properly\n");
            return 1;
        }
    }

    printf("Atomic construct working properly\n");
    return 0;
}