#include "acc_testsuite.h"

int test1(){
    int err = 0;
    int testArrayA[10];
    int testArrayB[10];

    #pragma acc serial copy(testArrayA, testArrayB)
    for(int i = 0; i < 10; i++) {
        int tmp = i;
        #pragma acc loop private(tmp)
        for(int j = 0; j < 10; j++) {
            testArrayB[j] = tmp;
            testArrayA[j]++;
            if(j != 0 && testArrayB[j] != testArrayB[j-1]) {
                err = 1;
            }
            if(testArrayA[j] != j + 1) {
                err = 1;
            }
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < 5; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}