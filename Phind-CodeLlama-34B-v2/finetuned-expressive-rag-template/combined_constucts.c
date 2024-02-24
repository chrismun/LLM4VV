#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM 100

int test_combined_constructs() {
    int err = 0;
    int *a = (int *)malloc(NUM * sizeof(int));
    int *b = (int *)malloc(NUM * sizeof(int));

    for (int x = 0; x < NUM; ++x) {
        a[x] = rand() % NUM;
        b[x] = 0;
    }

    #pragma acc parallel loop present(a[0:NUM], b[0:NUM])
    for (int x = 0; x < NUM; ++x) {
        b[x] = a[x] * 2;
    }

    for (int x = 0; x < NUM; ++x) {
        if (b[x] != a[x] * 2) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;

    failcode = test_combined_constructs();

    if (failcode != 0) {
        printf("Test failed with code %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}