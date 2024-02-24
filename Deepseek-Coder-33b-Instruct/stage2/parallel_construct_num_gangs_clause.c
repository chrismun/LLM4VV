#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:parallel construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;

    #pragma acc parallel num_gangs(2)
    {
        int gang_id = acc_get_gang_num();
        printf("Hello from gang %d\n", gang_id);
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}