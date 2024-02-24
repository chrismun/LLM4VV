#include <stdio.h>
#include <openacc.h>

#define N 1000000

int main() {
    int i, a[N];
    int sum = 0;

    // Initialize array
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Parallelize loop with OpenACC
    #pragma acc parallel loop copy(a[0:N]) reduction(+:sum)
    for (i = 0; i < N; i++) {
        // Use atomic construct to ensure atomic increment
        #pragma acc atomic
        sum += a[i];
    }

    // Check result
    int expected_sum = N * (N - 1) / 2;
    if (sum == expected_sum) {
        printf("Atomic construct test passed!\n");
        return 0;
    } else {
        printf("Atomic construct test failed!\n");
        return 1;
    }
}