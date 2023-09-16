#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        printf("Test 1 failed %d times\n", failed); //change to error logging method of yours
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}