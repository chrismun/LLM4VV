#ifndef T261
//T261:parallel,loop-variable-context,V:2.5-3.0
int test261(){
    int err = 0;
    srand(SEED);

    int x = 0;

    #pragma acc parallel num_gangs(2)
    {
        int x_private = x;

        #pragma acc loop gang worker
        for (x = 0; x < 2; ++x){
            x_private = x;
        }

        if (x_private != 1){
            err += 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T261
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test261();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}