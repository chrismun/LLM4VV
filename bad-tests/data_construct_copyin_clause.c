#ifndef T1
/*T1:data construct copyin clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    
    int* host_array = (int*)malloc(100*sizeof(int));
    for (int i = 0; i < 100; i++) host_array[i] = i;

    int* device_array;
    #pragma acc enter data copyin(host_array[0:100])
    #pragma acc parallel present(host_array)
    {
        device_array = (int*)acc_deviceptr(host_array);
    }

    for(int i = 0; i < 100; i++) {
        if (host_array[i] != device_array[i]) {
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(host_array[0:100])

    free(host_array);

    return err;
}
#endif