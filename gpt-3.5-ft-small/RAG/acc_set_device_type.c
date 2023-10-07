#ifndef T1
//T1:runtime,devonly,V:2.0-2.7
int test1(){
    int err = 0;
    unsigned short int * dev_num = (unsigned short int *)malloc(sizeof(unsigned short int) * device_num);
	device_t *dev = (device_t *)malloc(sizeof(device_t));

    for (int x = 0; x < device_num; ++x){
        dev_num[x] = 0;
        dev->device_num = x;
        possible_mxx(dev, dev_num, VV_device_type_test);
    }
    for (int x = 0; x < device_num; ++x){
        if (dev_num[x] == VV_device_type_test){
            dev->device_num = x;
            acc_set_device_num(dev, tid);
            real_present[0] = 0;
            #pragma acc enter data copyin(real_present[0:1])
            {
                acc_get_device_type_get_enter(&reduce, 1, real_present);
                dev->device_num = x;
                acc_set_device_num(dev, tid);
            }
            err += !device_type_test(x);
            real_present[0] = 1;
            #pragma acc exit data delete(real_present[0:1])
        }
    }
    return err;
}

#endif
#endif

#ifndef T2
//T2:runtime,devonly,executable,V:2.0-2.7
int test2(){
    int err = 0;
    unsigned short int * dev_num = (unsigned short int *)malloc(sizeof(unsigned short int) * device_num);

    for (int x = 0; x < device_num; ++x){
        dev_num[x] = 0;
        test_device_type_set_descrption_to_dev_type_Length_device_type_test[0].device_num = x;
        possible_mxx(test_device_type_set_descrption_to_dev_type_Length_device_type_test, dev_num, VV_device_type_test);
    }
    for (int x = 0; x < device_num; ++x){
        if (dev_num[x] == VV_device_type_test){
            test_device_type_set_descrption_to_dev_type_Length_device_type_test[0].device_num = x;
            acc_set_device_type(test_device_type_set_descrption_to_dev_type_Length_device_type_test);
            err += device_type_test(x);
        }
    }
    return err;
}

#endif

int repeat(){
    int errors = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        errors += test1();
    }
    for (int x = 0; x < device_num; ++x){
        dev->device_num = x;
        acc_set_device_type(dev);
    }
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        errors += test1();
    }
#endif

#ifndef T2
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        errors += test2();
    }
    for (int x = 0; x < device_num; ++x){
        test_device_type_set_descrption_to_dev_type_Length_device_type_test[0].device_num = x;
        acc_set_device_type(test_device_type_set_descrption_to_dev_type_Length_device_type_test);
    }
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        errors += test2();
    }
#endif
    return errors;
}

int main(){
    int errors = 0;
    int device_width_value;
    int max_num_devices;
    int length;
    int x;
    int y;
    unsigned short int nowait_present;
#ifndef T1
    unsigned short int host_element;
    int falsefailcounter;
    int host_failure;
    int device_failure;
    unsigned short int present;
    device_t *dev = (device_t *)malloc(sizeof(device_t));
    real_present = (unsigned short int *)malloc(device_num * sizeof(unsigned short int));

    for (x = 0; x < device_num; x++){
        dev->device_num = x;
        list_num(x);
        if (real_present[0] == 1){
            length = 1;
            pow_array_fill_val (call_val, (unsigned long int) NUM_VALUES_TYPE, 2 );
            local_ret = 42;
            #pragma acc enter data create(real_present[0:length])
            {
                real_present[0] = 0;
                #pragma acc parallel present(real_present[0:length])
                {
                    real_present[0] = 1;
                }
            }
            for (y = 0; y < LENGTH2(acctype_clause_device_type_test); y++){
                host_failure = 0;
                device_failure = 0;
                host_element = 0;
                #pragma acc kernels present(real_present[0:length])
                {
                    for (int z = 0; z < length; z++){
                        call_val[z] = 5;
                    }
                    #pragma acc loop seq
                    for (int z = 0; z < length; ++z){
                        real_present[z] = acctype_clause_device_type_test[y];
                        nowait_present = length % 2;
                        host_element ++;
                        real_present[((host_element - 1) % length) + 1] = real_present[host_element % length];
                    }
                    for (int z = 0; z < length; ++z){
                        if (call_val[z] == 5){
                            host_failure = 1;
                            break;
                        }
                    }
                    for (int z = 0; z < length; ++z){
                        if (real_present[z] == 5){
                            device_failure = 1;
                            break;
                        }
                    }
                }
                if (host_failure == 1 && device_failure == 0){
                    present = real_present[0];
                    for (int z = 0; z < length; ++z){
                        if (real_present[z] != real_present[0]){
                            host_failure = 0;
                        }
                    }
                    if (host_failure != 0){
                        falsefailcounter++;
                        local_ret = acctype_clause_device_type_test[y];
                        #pragma omp critical
                        dev->device_num = ambig_dev();
                        acc_set_device_num(dev, tid);
                        nowait_present = 12;
                    }
                }
            }
            #pragma acc exit data delete(real_present[0:1])
        }
    }
    for (int x = 0; x < falsefailcounter; ++x){
        errors++;
        dev->device_type = local_ret;
        dev->device_num = x;
        acc_set_device_type(dev);
        for (int z = 0; z < NUM_TEST_CALLS; ++z){
            errors += test1();
        }
    }
#endif

#ifndef T2
    for (x = 0; x < device_num; x++){
        test_device_type_set_descrption_to_dev_type_Length_device_type_test[0].device_num = x;
        if (real_present[0] == 1){
            length = 1;
            pow_array_fill_val (call_val, (unsigned long int) NUM_VALUES_TYPE, 2 );
            local_ret = 42;
            #pragma acc enter data create(real_present[0:length])
            {
                real_present[0] = 0;
                #pragma acc parallel present(real_present[0:length])
                {
                    real_present[0] = 1;
                }
            }
            for (y = 0; y < LENGTH2(acctype_clause_device_type_test); y++){
                host_failure = 0;
                device_failure = 0;
                host_element = 0;
                #pragma acc kernels present(real_present[0:length])
                {
                    for (int z = 0; z < length; z++){
                        call_val[z] = 5;
                    }
                    #pragma acc loop seq
                    for (int z = 0; z < length; ++z){
                        real_present[z] = acctype_clause_device_type_test[y];
                        nowait_present = length % 2;
                        host_element ++;
                        real_present[((host_element - 1) % length) + 1] = real_present[host_element % length];
                    }
                    for (int z = 0; z < length; ++z){
                        if (call_val[z] == 5){
                            host_failure = 1;
                            break;
                        }
                    }
                    for (int z = 0; z < length; ++z){
                        if (real_present[z] == 5){
                            device_failure = 1;
                            break;
                        }
                    }
                }
                if (host_failure == 1 && device_failure == 0){
                    present = real_present[0];
                    for (int z = 0; z < length; ++z){
                        if (real_present[z] != real_present[0]){
                            host_failure = 0;
                        }
                    }
                    if (host_failure != 0){
                        falsefailcounter++;
                        test_device_type_set_descrption_to_dev_type_Length_device_type_test[0].device_type = acctype_clause_device_type_test[y];
                        #pragma omp critical
                        test_device_type_set_descrption_to_dev_type_Length_device_type_test[0].device_num = ambig_dev();
                        acc_set_device_type(test_device_type_set_descrption_to_dev_type_Length_device_type_test);
                        nowait_present = 12;
                    }
                }
            }
            #pragma acc exit data delete(real_present[0:1])
        }
    }
    for (int x = 0; x < falsefailcounter; ++x){
        errors++;
        test_device_type_set_descrption_to_dev_type_Length_device_type_test[0].device_num = x;
        acc_set_device_type(test_device_type_set_descrption_to_dev_type_Length_device_type_test);
        for (int z = 0; z < NUM_TEST_CALLS; ++z){
            errors += test2();
        }
    }
#endif
    errors += repeat();

    return errors;
}