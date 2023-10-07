#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int num_workers;
    
    srand(SEED);
    
    #pragma acc parallel num_workers(2511)
    {
        // Code that will be executed by the parallel region
        // ...
        // ...
        // ...
    }
    
    // Check if the number of workers used by the parallel region is 2511
    if (num_workers != 2511){
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}