#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

int main() {
    int i, thread_id;
    int num_threads = omp_get_max_threads();

    #pragma omp parallel private(thread_id) num_threads(NUM_THREADS)
    {
        thread_id = omp_get_thread_num();
        printf("Thread %d is starting\n", thread_id);

        #pragma omp barrier

        #pragma omp single
        {
            printf("Thread %d is executing the single construct\n", thread_id);
        }

        #pragma omp barrier

        #pragma omp master
        {
            printf("Thread %d is executing the master construct\n", thread_id);
        }

        #pragma omp barrier

        printf("Thread %d is done\n", thread_id);
    }

    return 0;
}