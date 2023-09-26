#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void test_openacc() {
    float *p, *d_p;
    size_t size = 1000;
    int i;

    /* Allocate host memory */
    p = (float*) malloc(sizeof(float) * size);

    /* Initialize memory */
    for (i=0; i < size; i++) {
        p[i] = i;
    }

    /* Allocate device memory */
#pragma acc enter data create(p[0:size])

    d_p = acc_deviceptr(p);

    /* Using OpenACC API to attach pointer */
    acc_attach((void**) &d_p);

    /* Write to the device memory */
#pragma acc parallel deviceptr(d_p)
    for (i = 0; i < size; i++) {
        d_p[i] += 1.0;
    }

    /* Using OpenACC API to detach pointer */
    acc_detach((void**) &d_p);

#pragma acc exit data copyout(p[0:size])

    /* verify the results */
    for (i = 0; i < size; i++) {
        assert((int) p[i] == i+1);
    }
    printf("The results are correct!\n");

finally:
    free(p);
}

/* Main Function*/
int main() {

    test_openacc();

    return 0;
}