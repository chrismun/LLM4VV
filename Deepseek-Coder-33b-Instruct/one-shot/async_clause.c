#include <omp.h>
#include <stdio.h>

int main() {
    int var = 0;

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task shared(var)
            {
                var = 1;
            }

            #pragma omp taskwait

            #pragma omp task shared(var)
            {
                var = 2;
            }

            #pragma omp taskwait

            #pragma omp task shared(var)
            {
                var = 3;
            }

            #pragma omp taskwait
        }
    }

    printf("var = %d\n", var);

    return 0;
}