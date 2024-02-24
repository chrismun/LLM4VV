#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:serial construct if clause,V:2.7-3.3
int test1(){
    int err = 0;

    if (acc_get_device_type() == acc_device_host) {
        printf("Serial construct if clause is working properly.\n");
    } else {
        printf("Serial construct if clause is not working properly.\n");
        err = 1;
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