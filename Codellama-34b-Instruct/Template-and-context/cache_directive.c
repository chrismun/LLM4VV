#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int arr[100];
    int i;

    #pragma acc cache(arr[0:10])
    for (i = 0; i < 10; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[10:20])
    for (i = 10; i < 20; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[20:30])
    for (i = 20; i < 30; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[30:40])
    for (i = 30; i < 40; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[40:50])
    for (i = 40; i < 50; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[50:60])
    for (i = 50; i < 60; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[60:70])
    for (i = 60; i < 70; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[70:80])
    for (i = 70; i < 80; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[80:90])
    for (i = 80; i < 90; i++) {
        arr[i] = i;
    }

    #pragma acc cache(arr[90:100])
    for (i = 90; i < 100; i++) {
        arr[i] = i;
    }

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