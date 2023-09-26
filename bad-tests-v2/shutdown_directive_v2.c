#include <stdio.h>
#include <stdlib.h>

// Check whether x is prime: our example "complicated function"
int is_prime(int x) {
    if (x < 2) return 0;
    for (int i = 2; i*i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    int *n_primes_cpu = malloc(n * sizeof(int));
    int *n_primes_gpu = malloc(n * sizeof(int));

    // Compute prime count using the CPU
    for (int i = 0; i < n; i++) {
        n_primes_cpu[i] = is_prime(i);
    }

    // Compute prime count using the GPU
    #pragma acc data copyout(n_primes_gpu[0:n])
    #pragma acc kernels
    for (int i = 0; i < n; i++) {
        n_primes_gpu[i] = is_prime(i);
    }

    // Check that the two computations yield the same result
    for (int i = 0; i < n; i++) {
        if (n_primes_cpu[i] != n_primes_gpu[i]) {
            fprintf(stderr, "Mismatch on n_primes[%d]: CPU=%d GPU=%d\n", i, n_primes_cpu[i], n_primes_gpu[i]);
            return 1;
        }
    }

    printf("Correct result!\n");
    return 0;
}