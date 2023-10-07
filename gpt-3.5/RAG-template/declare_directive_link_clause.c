#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare the global variables with link clause
    #pragma acc declare link(a, b, c)

    // Use the global variables in accelerator routines
    #pragma acc parallel
    {
        a += 1;
        b += 2;
        c += 3;
    }

    // Verify the results
    if (a != NUM_TEST_CALLS || b != NUM_TEST_CALLS * 2 || c != NUM_TEST_CALLS * 3){
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