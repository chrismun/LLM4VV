#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    int i;
    int count = 0;
    int *host_data = (int *)malloc(n * sizeof(int));
    int *device_data = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; ++i){
        host_data[i] = 0;
        device_data[i] = 0;
    }

    #pragma acc data copyin(host_data[0:n])
    {
        #pragma acc parallel compute num_gangs(1)
        {
            #pragma acc loop gang
            for(i=0; i<n; i++)
            {
                device_data[i] = 1;
            }
        }
    }

    for(i=0; i<n; i++)
    {
        count += device_data[i];
    }

    if (count == n){
        err = 0;
    }
    else{
        err = 1;
    }

    free(host_data);
    free(device_data);

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