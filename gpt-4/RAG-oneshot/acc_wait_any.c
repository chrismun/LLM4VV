#include "stdlib.h"
#include "openacc.h"
#include "assert.h"

int main() {
    const int n = 100000;
    double *x = (double*)malloc( n * sizeof(double));
    assert(x != NULL);

    // initialize in the host
    for( int i = 0; i < n; i++ ) {
        x[i] =  1.0/n*i;
    }

    int asyncs[2];

    // copy to the device asynchronously
    asyncs[0] = acc_async_test_all();

    #pragma acc enter data create(x[0:n]) async(asyncs[0])

    // start computation on the device asynchronously
    asyncs[1] = acc_async_test_all();

    #pragma acc parallel loop async(asyncs[1])
    for( int i = 1; i < n; i++ ) {
        x[i] += x[i-1];
    }

    // wait for any of the operations to complete
    int index = acc_wait_any(2, asyncs);

    // indices start with 0 in C
    assert(index >= 0 && index < 2);

    #pragma acc exit data delete(x[0:n]) async(asyncs[0])

    free(x);
    return 0;
}