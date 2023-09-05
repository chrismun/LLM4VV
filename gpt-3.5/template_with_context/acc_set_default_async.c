#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // test acc_set_default_async here
    acc_set_default_async(1); // set async_arg value

    // perform operations with async clauses
    #pragma acc parallel async // will use async_arg as the async queue
    {
        // compute asynchronously
    }

    #pragma acc parallel async(2) // will not use async_arg as the async queue
    {
        // compute asynchronously
    }

    // check if the operations were performed correctly
    if(/* condition to check the correctness of the operations */){
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