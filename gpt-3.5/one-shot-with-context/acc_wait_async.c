#ifndef T2
//T2:device_type:ALL,multiple concurrent asyncs,V:2.7-2.7.1
int test2(){
    int err = 0;

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        acc_async_present_1 = 0;

        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }

        acc_async_present_1 = 1;

        #pragma acc wait async(1)

#pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }

        #pragma acc wait async(2)
    }
    
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}