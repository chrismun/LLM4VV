#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 10;
    int num_vectors = 10;

    int *a = (int *)malloc(num_gangs * num_workers * num_vectors * sizeof(int));
    int *b = (int *)malloc(num_gangs * num_workers * num_vectors * sizeof(int));
    int *c = (int *)malloc(num_gangs * num_workers * num_vectors * sizeof(int));

    for (int x = 0; x < num_gangs * num_workers * num_vectors; ++x){
        a[x] = rand() % 100;
        b[x] = rand() % 100;
        c[x] = 0;
    }

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers) num_vectors(num_vectors)
    {
        int gang_id = acc_gang_id();
        int worker_id = acc_worker_id();
        int vector_id = acc_vector_id();

        int index = gang_id * num_workers * num_vectors + worker_id * num_vectors + vector_id;
        c[index] = a[index] + b[index];
    }

    for (int x = 0; x < num_gangs * num_workers * num_vectors; ++x){
        if (c[x] != a[x] + b[x]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}