#ifndef T1
//T1:delete,data,data-region,V:1.0-2.7
int test1(){

    
    srand(SEED);

    float * a = (float *) malloc(n * sizeof(float));
    float * d_a;

    for (int x = 0; x < n; ++x){
        a[x] = ((float) rand() / (float)(RAND_MAX)) * 30;
    }

    // Copy input a[] to device memory
    #pragma acc data copyin(a[0:n])
    {
        #pragma acc enter data create(a[0:n])     //Creates variable a[] in the device memory

        d_a = a;

        // Compute execution on device
        #pragma acc parallel
        {
            #pragma acc loop
            for(int x=0; x<n; x++)
                d_a[x]+=10;
        }


    } // exit data region

    // Explicitly delete
    #pragma acc exit data delete(a)

    int error = 0;
    for(int x=0; x<n; x++) {
        if(a[x] != a[x]+10)
            error=1;
    }

    // Clean up
    free(a);

    return error;
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