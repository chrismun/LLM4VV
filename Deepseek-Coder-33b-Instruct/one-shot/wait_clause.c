#include <omp.h>
#include <stdio.h>

int main() {
    int var = 0;

    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();
        if (thread_id == 0) {
            var = 1;
            #pragma omp barrier
        } else {
            #pragma omp barrier
            printf("Thread 1's var = %d\n", var);
        }
    }

    return 0;
}