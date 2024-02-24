#include <stdio.h>
#include <openacc.h>

int main() {
    int shared_var = 0;

    #pragma acc parallel num_gangs(1) copyin(shared_var)
    {
        #pragma acc loop worker
        for (int i = 0; i < 1000; i++) {
            #pragma acc atomic update
            shared_var++;
        }
    }

    printf("Shared variable value: %d\n", shared_var);

    return 0;
}