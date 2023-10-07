int key;

void test_wai(unsigned real_n, unsigned n, real_t *a, real_t *b, real_t *c){
    unsigned temp_n;
    virtual_memory_region_desc_t* def_desc;
    real_t* def_a = (real_t*)malloc(real_n * sizeof(real_t));
    real_t* def_b = (real_t*)malloc(real_n * sizeof(real_t));
    real_t* def_c = (real_t*)malloc(real_n * sizeof(real_t));

    for (temp_n = 0; temp_n < real_n; ++temp_n){
        def_a[temp_n] = 0;
        def_b[temp_n] = 0;
        def_c[temp_n] = 0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], c[0:n]) create(def_a[0:real_n], def_b[0:real_n], def_c[0:real_n])

    key++;
    #pragma acc data present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel present(def_a[0:real_n], def_b[0:real_n], def_c[0:real_n]) num_gangs(1) num_workers(1) vector_length(1)
        {
            *((int *) acc_deviceptr(&def_desc)) = test(device_reached);
            acc_memcpy_from_device_async(&def_desc, sizeof(virtual_memory_region_desc_t *), 1);
            def_desc->region_size = real_n * sizeof(real_t);
            unsigned ctr = 0;
            for (ctr = 0; ctr < n; ++ctr){
                def_desc->page_table[(((uintptr_t) &def_a[0]) - def_desc->region_start) >> 12].page = ((uintptr_t) a[ctr]) >> 12;
                def_desc->page_table[(((uintptr_t) &def_a[0]) - def_desc->region_start) >> 12].pointer = (uintptr_t) a[ctr];
                def_desc->page_table[(((uintptr_t) &def_b[0]) - def_desc->region_start) >> 12].page = ((uintptr_t) b[ctr]) >> 12;
                def_desc->page_table[(((uintptr_t) &def_b[0]) - def_desc->region_start) >> 12].pointer = (uintptr_t) b[ctr];
                def_desc->page_table[(((uintptr_t) &def_c[0]) - def_desc->region_start) >> 12].page = ((uintptr_t) c[ctr]) >> 12;
                def_desc->page_table[(((uintptr_t) &def_c[0]) - def_desc->region_start) >> 12].pointer = (uintptr_t) c[ctr];
            }
            key++;
        }
        #pragma acc parallel present(def_a[0:real_n], def_b[0:real_n], def_c[0:real_n]) num_gangs(1) num_workers(1) vector_length(1)
        {
            unsigned ctr = 0;
            unsigned first = 0;
            int condition;
            while (first < n){
                if (first + 4 < n){
                    #pragma acc loop seq
                    for (ctr = first; ctr < first + 4; ++ctr){
                        if (def_a[first] + def_b[first] == def_c[first]){
                            condition = 1;
                        } else {
                            condition = 0;
                        }
                    }
                } else {
                    #pragma acc loop seq
                    for (ctr = first; ctr < n; ++ctr){
                        if (def_a[ctr] + def_b[ctr] == def_c[ctr]){
                            condition = 1;
                        } else {
                            condition = 0;
                        }
                    }
                }
                first += 4;
            }
            key--;
            #pragma acc wait key(key - 1)
            for (ctr = 0; ctr < n; ++ctr){
                if (a[ctr] + b[ctr] == c[ctr]){
                    condition = 1;
                } else {
                    condition = 0;
                }
            }
            key++;
        }
        #pragma acc parallel present(def_a[0:real_n], def_b[0:real_n], def_c[0:real_n]) num_gangs(1) num_workers(1) vector_length(1)
        {
            unsigned ctr = 0;
            #pragma acc loop seq
            for (ctr = 0; ctr < n; ++ctr){
                def_a[ctr] = a[ctr];
                def_b[ctr] = b[ctr];
                def_c[ctr] = c[ctr];
            }
            key++;
        }
        #pragma acc parallel present(def_a[0:real_n], def_b[0:real_n], def_c[0:real_n]) num_gangs(1) num_workers(1) vector_length(1)
        {
            unsigned ctr = 0;
            unsigned first = 0;
            int condition;
            while (first < n){
                if (first + 4 < n){
                    #pragma acc loop seq
                    for (ctr = first; ctr < first + 4; ++ctr){
                        if (def_a[first] + def_b[first] == def_c[first]){
                            condition = 1;
                        } else {
                            condition = 0;
                        }
                    }
                } else {
                    #pragma acc loop seq
                    for (ctr = first; ctr < n; ++ctr){
                        if (def_a[ctr] + def_b[ctr] == def_c[ctr]){
                            condition = 1;
                        } else {
                            condition = 0;
                        }
                    }
                }
                first += 4;
            }
            key--;
            #pragma acc wait key(key + 1)
            for (ctr = 0; ctr < n; ++ctr){
                if (def_a[ctr] + def_b[ctr] == def_c[ctr]){
                    condition = 1;
                } else {
                    condition = 0;
                }
            }
        }
    }

    free(def_a);
    free(def_b);
    free(def_c);
    #pragma acc exit data delete(def_a[0:real_n], def_b[0:real_n], def_c[0:real_n]) copyout(a[0:n], b[0:n], c[0:n])
}

int main(){
    int device = acc_get_device_type();
    int err = 0;
    if (device == acc_device_host){
        for (int x = 0; x < NUM_TEST_IMGS; ++x){
            size_t n = img_descs[x].length;
            size_t bytes = n * sizeof(real_t);
            real_t *a = (real_t *)malloc(bytes);
            real_t *b = (real_t *)malloc(bytes);
            real_t *c = (real_t *)malloc(bytes);

            for (int y = 0; y < n; ++y){
                a[y] = rand() / (real_t)(RAND_MAX / 10);
                b[y] = rand() / (real_t)(RAND_MAX / 10);
                c[y] = a[y] + b[y];
            }

            test_wai(bytes, n, a, b, c);

            for (int y = 0; y < n; ++y){
                if (fabs(a[y] - c[y]) > PRECISION){
                    err = 1;
                }
            }
        }
    }
    else {
        for (int x = 0; x < NUM_TEST_IMGS_ACC; ++x){
            size_t n = img_descs_acc[x].length;
            size_t bytes = n * sizeof(real_t);
            real_t *a = (real_t *)acc_malloc(bytes);
            real_t *b = (real_t *)acc_malloc(bytes);
            real_t *c = (real_t *)acc_malloc(bytes);

            for (int y = 0; y < n; ++y){
                a[y] = rand() / (real_t)(RAND_MAX / 10);
                b[y] = rand() / (real_t)(RAND_MAX / 10);
            }

            for (int y = 0; y < n; ++y){
                c[y] = a[y] + b[y];
            }

            #pragma acc data copyin(a[0:n], b[0:n]) copyout(a[0:n], b[0:n]) async(10)
            {
                #pragma acc parallel present(c[0:n])
                {
                    #pragma acc loop
                    for (unsigned x = 0; x < n; ++x){
                        c[x] = a[x] + b[x];
                    }
                }
            }
            #pragma acc data present(a[0:n], b[0:n], c[0:n])
            {
                #pragma acc host_data use_device(a[0:n], b[0:n])
                {
                    unsigned n3 = n;
                    #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) num_gangs(1) num_workers(1) vector_length(1) async(11)
                    {
                        #pragma acc loop
                        for (unsigned x = 0; x < n; ++x){
                            a[x] = rand() / (real_t)(RAND_MAX / 10);
                            b[x] = rand() / (real_t)(RAND_MAX / 10);
                        }
                        #pragma acc loop
                        for (unsigned x = 0; x < n; ++x){
                            if (c[x] > 0){
                                n3 = n3 - 1;
                            }
                        }
                    }
                    #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) num_gangs(1) num_workers(1) vector_length(1) async(10)
                    {
                        #pragma acc loop
                        for (unsigned x = 0; x < n; ++x){
                            c[x] = a[x] + b[x];
                        }
                    }
                    #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) num_gangs(1) num_workers(1) vector_length(1) wait(11)
                    {
                        unsigned ctr = 0;
                        unsigned first = 0;
                        int condition;
                        while (first < n){
                            if (first + 4 < n){
                                #pragma acc loop seq
                                for (ctr = first; ctr < first + 4; ++ctr){
                                    if (c[first] == 0){
                                        condition = 1;
                                    }
                                    else
                                    {
                                        condition = 0;
                                    }
                                }
                            }
                            else
                            {
                                #pragma acc loop seq
                                for (ctr = first; ctr < n; ++ctr){
                                    if (c[ctr] == 0){
                                        condition = 1;
                                    }
                                    else
                                    {
                                        condition = 0;
                                    }
                                }
                            }
                            first += 4;
                        }
                        key--;
                        #pragma acc wait key(key - 1)
                        for (ctr = 0; ctr < n; ++ctr){
                            if (c[ctr] != 0){
                                condition = 1;
                            }
                            else
                            {
                                condition = 0;
                            }
                        }
                    }
                }
            }

            for (int y = 0; y < n; ++y){
                if (fabs(a[y] + b[y] - c[y]) > PRECISION){
                    err = 1;
                }
            }

            acc_free(a, bytes);
            acc_free(b, bytes);
            acc_free(c, bytes);
        }
    }
    return err;
}