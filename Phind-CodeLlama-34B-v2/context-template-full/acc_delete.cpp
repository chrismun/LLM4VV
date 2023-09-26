#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

using namespace std;

#ifndef T1
/*T1:acc delete,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *devPtr = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() % n;
        devPtr[x] = 0;
    }

    acc_memcpy_to_device(devPtr, a, n * sizeof(int));

    acc_delete(devPtr, n * sizeof(int));

    if (devPtr != nullptr) {
        cout << "acc_delete failed to deallocate device memory." << endl;
        err = 1;
    }

    free(a);

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