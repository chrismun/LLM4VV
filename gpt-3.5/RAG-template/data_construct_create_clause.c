#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int *ptr = NULL;
    int var = 0;

    // Create clause with zero modifier
    #pragma acc data create(var) zero(ptr)
    {
        // Validate create action with zero modifierr
        #pragma acc enter data create(var) zero(ptr)
        if (var != 0){
            err = 1;
        }
        if (ptr != NULL){
            err = 1;
        }

        // Modify variables in the data region
        var = 10;
        ptr = (int*) malloc(sizeof(int));
        *ptr = 20;

        // Validate attach action
        #pragma acc enter data copyin(ptr) create(var)
        if (var != 10){
            err = 1;
        }
        if (*ptr != 20){
            err = 1;
        }

        // Modify variables after exiting the data region
        var = 100;
        *ptr = 200;

        // Validate detach action
        #pragma acc exit data detach(var) delete(ptr)
        if (var != 100){
            err = 1;
        }
        if (*ptr != 200){
            err = 1;
        }

        // Validate delete action
        if (ptr != NULL){
            err = 1;
        }
        free(ptr);
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}