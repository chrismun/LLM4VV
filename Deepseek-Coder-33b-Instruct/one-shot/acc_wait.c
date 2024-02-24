#include <omp.h>
#include <stdio.h>

int main() {
    int var = 0;

    #pragma omp parallel num_threads(2)
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d is starting\n", thread_id);

        #pragma omp barrier

        if (thread_id == 0) {
            var = 5;
            printf("Thread %d has set var to %d\n", thread_id, var);
        }

        #pragma omp barrier

        printf("Thread %d has var as %d\n", thread_id, var);
    }

    return 0;
}