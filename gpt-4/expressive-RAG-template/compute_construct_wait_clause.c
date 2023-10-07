#include "acc_testsuite.h"

//T1:compute construct wait clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int gang_num = rand() % 10;
    int *compute = (int*)malloc(gang_num * sizeof(int));
    int *host = (int*)malloc(gang_num * sizeof(int));

    for(int i = 0; i < gang_num; i++) {
        host[i] = i;
    }

    #pragma acc parallel loop gang(num: gang_num) copy(host[:gang_num])
    for(int i = 0; i < gang_num; i++){
        compute[i] = host[i];
        #pragma acc wait
    }

    #pragma acc update host(compute[:gang_num])

    for(int i = 0; i < gang_num; i++) {
        if(compute[i] != host[i]){
            err = 1;
        }
    }

    free(compute);
    free(host);
    return err;
}

int main(){
    int errcode = 0;
    int failed = 0;

    failed = test1();
    
    if (failed != 0){
        errcode = errcode + (1 << 0);
    }

    return errcode;
}