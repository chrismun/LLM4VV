#include <stdio.h>
#include <openacc.h>

#define NUM_GANG_DIM1 5
#define NUM_GANG_DIM2 3
#define NUM_GANG_DIM3 2

int main() {
    int num_gangs[3] = {NUM_GANG_DIM1, NUM_GANG_DIM2, NUM_GANG_DIM3};
    int expected_num_gangs = NUM_GANG_DIM1 * NUM_GANG_DIM2 * NUM_GANG_DIM3;

    #pragma acc parallel num_gangs(NUM_GANG_DIM1, NUM_GANG_DIM2, NUM_GANG_DIM3)
    {
        int my_gang_id = acc_get_gang_id(3);
        if (my_gang_id >= expected_num_gangs) {
            printf("Error: Gang ID %d is out of range.\n", my_gang_id);
        }
    }

    printf("Verified num_gangs clause with %d gangs in each dimension.\n", expected_num_gangs);

    return 0;
}