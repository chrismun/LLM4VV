#include "acc_testsuite.h"

//T1:routine,data,reference-counting,attach-detach,construct-independent,V:2.7-2.7
int test1(){
    int err;
    int *host;

    srand(10);
    int size = 100;
    host = (int*) malloc(size * sizeof(int));

    #pragma acc enter data create(host[0:size])

    for(int i = 0; i < size; ++i){
        host[i] = i;
        #pragma acc attach(host[i])
    }

    int a = 5;
    #pragma acc parallel loop present(host[0:size])
    for(int i = 0; i < size; ++i){
        host[i] += a;
    }

    #pragma acc exit data copyout(host[0:size])

    for(int i = 0; i < size; ++i){
        if (host[i] != i+a){
            err += 1;
            break;
        }
    }

    free(host);

    return err;
}

int main(){
    int failcode = 0;
    int failed = test1();
    if (failed != 0){
        failcode = failcode + 1;
    }
    return failcode;
}