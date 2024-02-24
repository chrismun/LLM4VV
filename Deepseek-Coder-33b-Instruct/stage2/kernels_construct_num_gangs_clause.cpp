#include <stdlib.h>
#include <openacc.h>

#define NUM_GANG 10

int main() {
    int num_gangs = 0;
    int num_workers = 0;
    int vector_length = 0;

    // Create a parallel region
    #pragma acc parallel num_gangs(NUM_GANG)
    {
        // Get the number of gangs, workers and vector length
        num_gangs = acc_get_num_gangs();
        num_workers = acc_get_num_workers();
        vector_length = acc_get_vector_length();
    }

    // Check if the number of gangs is as expected
    if (num_gangs != NUM_GANG) {
        printf("Error: expected %d gangs, but got %d\n", NUM_GANG, num_gangs);
        return 1;
    }

    printf("Success: num_gangs clause is working properly\n");
    return 0;
}