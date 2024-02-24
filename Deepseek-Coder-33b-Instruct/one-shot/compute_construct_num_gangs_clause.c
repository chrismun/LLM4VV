#include <stdio.h>
#include <openacc.h>

int main() {
    int num_gangs = 4; // Specify the number of gangs

    // Create a parallel region with the specified number of gangs
    #pragma acc parallel num_gangs(num_gangs)
    {
        // Each gang prints a message
        printf("Hello from gang %d\n", acc_get_gang_num());
    }

    return 0;
}