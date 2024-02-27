#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
#define T1
// T1:compute construct num_gangs clause, V:2.7-2.7
int test1() {
    int err = 0;
    int num_gangs = 5; // Example: testing with 5 gangs
    int *gang_counts;
    int host_gang_counts[num_gangs];
    for (int i = 0; i < num_gangs; i++) {
        host_gang_counts[i] = 0;
    }

    gang_counts = acc_malloc(num_gangs * sizeof(int));
    acc_memcpy_to_device(gang_counts, host_gang_counts, num_gangs * sizeof(int));

    #pragma acc parallel num_gangs(num_gangs)
    {
        int gangID = __pgi_gangidx(); // Using PGI compiler specific function to get gang ID
        if (gangID < num_gangs) {
            #pragma acc atomic update
            gang_counts[gangID] += 1;
        }
    }

    acc_memcpy_from_device(host_gang_counts, gang_counts, num_gangs * sizeof(int));
    acc_free(gang_counts);

    for (int i = 0; i < num_gangs; i++) {
        if (host_gang_counts[i] != 1) {
            err += 1; // If any gang didn't update its count, something went wrong
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
    #ifndef T1
    failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    #endif
    return failcode;
}