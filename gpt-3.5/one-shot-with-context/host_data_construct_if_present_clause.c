#ifndef T1
//T1:hostdata,if_present,V:1.0-2.7
int test1(){
    int err = 0;
    int * a = (int *)malloc(n * sizeof(int));
    int * b = (int *)malloc(n * sizeof(int));

    if(a == NULL || b == NULL){
        err = 1;
        return err;
    }

    for (int x = 0; x < n; ++x){
        a[x] = x + 1;
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc data present(a[0:n]) host_data if_present(b[0:n]) // Only replace the address of b if it is present
    {
        // Do something with a
        #pragma acc parallel loop present(a[0:n]) // Just to show the usage of present
        for (int x = 0; x < n; ++x){
            a[x] += 1;
        }

        // Now copy the updated a back to b
        #pragma acc parallel loop present(a[0:n]) host_data if_present(b[0:n]) // Only replace the address of b if it is present
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }
    
    for(int x = 0; x < n; x++){
        if(b[x] != (x + 1) + 1){ // b should be equal to a+1
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:n]), delete(b[0:n])

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