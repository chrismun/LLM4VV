#ifndef T1
#define TEST 0
#endif

int test(){
    int err = 0;
    #ifndef T1
        //Test for distant data pointers, testing data scope
        int ** a = (int **)malloc(n * sizeof(int *));
        int ** c = (int **)malloc(n * sizeof(int *));
        int * b = (int *)malloc(n * n * sizeof(int *));
        int * d = (int *)malloc(n * n * sizeof(int *));
        for (int x = 0; x < n; ++x){
            a[x] = &(b[x * n]);
            c[x] = &(d[x * n]);
        }
    #else
        //Test for accessible data pointers, testing if the routine directives are being applied
        int ** a = (int **)malloc(n * sizeof(int *));
        int ** c = (int **)malloc(n * sizeof(int *));
        int * b = (int *)malloc(n * n * sizeof(int *));
        int * d = (int *)malloc(n * n * sizeof(int *));
        for (int x = 0; x < n; ++x){
            a[x] = &(b[x * n]);
            c[x] = &(d[x * n]);
            a[x][x] = 1;
            c[x][x] = 1;
        }
    #endif

    int specialization_counter = 0;
    int current_call = 0;
    int current_specialization = 0;
    struct special_data present[256];
    #pragma acc data copyin(present[0:256])
    {
        #pragma acc kernels copy(current_call)
        {
            current_call = 0;
            current_specialization = 0;
            //Create data using present
            while (current_specialization <= specialization_counter){
                present[current_specialization].data = (int *)malloc(n * n * sizeof(int));
                present[current_specialization].special = current_specialization;
                for (int x = 0; x < n; ++x){
                    for (int y = 0; y < n; ++y){
                        present[current_specialization].data[x * n + y] = 1;
                    }
                }
                current_specialization++;
            }
            #pragma acc loop //This is not a compute construct, it is a parallel directive
            for (int x = 0; x < 256; ++x){
                memcpy(a[0], present[x % 256].data, n * n * sizeof(int));
                for (int y = 0; y < 2; ++y){
                    memset(c[y], 0, n * n * sizeof(int));
                    for (int z = 0; z < n; ++z){
                        for (int w = 0; w < n; ++w){
                            c[y][w * n + z] += a[y][z * n + w];
                        }
                    }
                }
                for (int y = 0; y < n; ++y){
                    for (int z = 0; z < n; ++z){
                        if (fabs(c[y][z] - (y + 1) * n) > (y + 1) * n * 0.1){
                            current_call = 1;
                        }
                    }
                }
                if (current_call){
                    break;
                }
            }
        }
    }
    if (current_call != 0){
        err += 1;
    }
    for (int x = 0; x <= specialization_counter; ++x){
        free(present[x].data);
    }

    return !err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + !test();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#else
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + !test_stride();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}