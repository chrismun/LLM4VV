#ifndef T1
//T1:enter data,data-region,V:2.5-2.9
int test1(){

    // Create an array of integers
    int n = 10;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    
    // Initialize the array
    for(int i = 0; i < n; i++){
        a[i] = i;
        b[i] = 0;
    }

    // Copy data to device
    #pragma acc enter data copyin(a[0:n]) create(b[0:n])

    // Perform computation on device
    #pragma acc parallel loop
    for(int i = 0; i < n; i++){
        b[i] = a[i] * 2;
    }

    // Copy data back to host
    #pragma acc exit data copyout(b[0:n])

    // Verify the results
    int success = 1;
    for(int i = 0; i < n; i++){
        if(b[i] != (a[i]*2)){
            success = 0;
            break;
        }
    }

    free(a);
    free(b);

    return !success;
}
#endif

int main(){

    int fail = 0;

    // Test the implementation
    #ifndef T1
    fail = fail || test1();
    #endif

    // Print the result
    if(fail){
        printf("Test failed\n");
    }
    else{
        printf("Test passed\n");
    }

    return fail;
}