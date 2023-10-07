#ifndef T1
//T1:routine,executable-data,loop,V:2.0-2.7
int test1(){
    int device_num = acc_get_device_num(acc_get_device_type());
    int host_memory = 0;
    int error = 0;

    #pragma acc enter data copyin(host_memory)
    #pragma acc parallel num_gangs(1)
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x){
            #pragma host_data use_device(host_memory)
            {
                host_memory += 1;
            }
        }

        #pragma host_data use_device(host_memory)
        {
            if (host_memory != 10){
                error = 1;
            }
        }
    }
    #pragma acc exit data delete(host_memory)

    return error;
}
#endif

#ifndef T2
//T2:routine,executable-data,construct-independent,V:2.0-2.7
int test2(){
    int host_memory = 0;
    int error = 0;

    #pragma acc enter data create(host_memory)
    #pragma acc parallel num_gangs(1)
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x){
            #pragma host_data use_device(host_memory)
            {
                host_memory += 1;
            }
        }
    }

    unsigned int * is_present = (unsigned int *)malloc(sizeof(unsigned int));
    *is_present = acc_hostptr(&host_memory) != (void *)host_memory;

    const unsigned int present = 0;
    const unsigned int not_present = 1;

    if (host_memory != 10){
        error = 1;
    }

    #pragma acc exit data present(is_present[:1])
    #pragma acc parallel num_gangs(1)
    {
        if (is_present[0] != present){
            error = 1;
        }
    }
    #pragma acc exit data delete(host_memory, is_present[:1])

    return error;
}
#endif

#ifndef T3
//T3:routine,construct-independent,executable-data,V:2.0-2.7
int test3(){
    int *host_memory;
    int error = 0;

    #pragma acc enter data create(host_memory[10])
    #pragma acc parallel num_gangs(10)
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x){
            #pragma host_data use_device(host_memory)
            {
                host_memory[x] = x;
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        if (host_memory[x] != x){
            error = 1;
        }
    }

    unsigned int * is_present = (unsigned int *)malloc(sizeof(unsigned int));
    *is_present = acc_hostptr(host_memory) != (void *)host_memory;

    const unsigned int present = 0;
    const unsigned int not_present = 1;

    #pragma acc exit data present(is_present[0:1])
    #pragma acc parallel num_gangs(1)
    {
        if (is_present[0] != present){
            error = 1;
        }
    }
    #pragma acc exit data delete(is_present[0:1], host_memory[10])

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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
    return failcode;
}