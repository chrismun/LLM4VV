#include <omp.h>
#include <stdio.h>

int main() {
    int num_workers;

    #pragma omp parallel num_threads(4)
    {
        #pragma omp single
        {
            num_workers = omp_get_num_threads();
        }
    }

    printf("Number of workers: %d\n", num_workers);

    return 0;
}