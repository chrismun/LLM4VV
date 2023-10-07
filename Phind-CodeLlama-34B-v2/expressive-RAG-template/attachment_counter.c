#include "acc_testsuite.h"
#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b, *c;
    int device_num = acc_get_device_num(acc_device_nvidia);
    acc_set_device_num(device_num, acc_device_nvidia);

    a = (int *)acc_malloc(sizeof(int));
    b = (int *)acc_malloc(sizeof(int));
    c = (int *)acc_malloc(sizeof(int));

    *a = 1;
    *b = 2;
    *c = 3;

    #pragma acc enter data copyin(a[0:1], b[0:1], c[0:1])

    #pragma acc data present(a, b, c)
    {
        #pragma acc update device(a[0:1], b[0:1], c[0:1])

        #pragma acc parallel present(a, b, c)
        {
            a[0] += b[0] + c[0];
        }

        #pragma acc update self(a[0:1])
    }

    if (*a != 6) {
        err = 1;
    }

    acc_free(a);
    acc_free(b);
    acc_free(c);

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