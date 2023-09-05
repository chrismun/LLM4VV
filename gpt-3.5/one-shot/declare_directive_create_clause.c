#ifndef T1
//T1:declare,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;

    int * a = (int *)malloc(sizeof(int));
    *a = 0;

    #pragma acc data copyout(a[0:1])
    {
        #pragma acc parallel num_gangs(1) num_workers(1) present(a)
        {
            #pragma acc declare create(b)
            int b = 1;

            *a = *a + b;
        }
    }

    if (*a != 1){
        err += 1;
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