#include <stdio.h>
#include <omp.h>

int main() {
    int counter = 0;

    #pragma omp parallel
    {
        #pragma omp atomic
        counter++;
    }

    printf("Counter value: %d\n", counter);

    return 0;
}