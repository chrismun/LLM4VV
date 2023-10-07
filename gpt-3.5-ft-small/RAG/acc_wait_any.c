#ifndef T1
//T1:wait,wait,devonly-1,pragma,V:2.5-2.7
int test1(){
    int err = 0;
    int device_num = 1, i;
    int *reduction_host = (int *)malloc(LOOP_SIZE * sizeof(int));
    int *reduction_array = (int *)malloc(LOOP_SIZE * sizeof(int));

    for (i = 0; i < LOOP_SIZE; i++){
        reduction_host[i] = 1;
        reduction_array[i] = 1;
    }


    #pragma acc data copyin(reduction_array[0:LOOP_SIZE])
    {
        #pragma acc parallel num_gangs(LOOPS) num_workers(4) vector_length(32) present(device_num)
        {
            /* Non-Determinancy introduced here */
            unsigned int seed = device_num + 1;
            int distribution = 0;
            /* Generate random number sequence */
            for (int j = 0; j < 1024; j++)
                rand();

            /* Random walk from a seed */
            for (int j = 0; j < 100000; ++j){
                int n = rand_r(&seed) % 3;
                /* x[n < 1] = 1 - x[n] */
                distribution = (n < 1)*(1 - distribution) + (n >= 1)*distribution;
            }
            reduction_array[0] = distribution;
        }
        #pragma acc parallel num_gangs(LOOPS) num_workers(4) vector_length(32) present(reduction_array, device_num)
        {
            int my_id = acc_get_device_num();
            unsigned int seed = my_id + 1;
            int mapped = 32*4*acc_get_num_workers()*acc_get_num_gangs()*my_id;
            for (int j = 0; j < 1024; j++)
                rand();
            for (int j = 0; j < 100000; j++){
                int n = rand_r(&seed) % 2;
                int m = rand_r(&seed) % 16;
                int c = rand_r(&seed) % 3;
                if (n){
                    if (c == 0){
                        #pragma acc atomic capture
                            reduction_array[0] = mapped + m;
                    }
                }
                else
                {
                    if (c == 0){
                        int t;
                        t = mapped + m;
                        acc_wait(1,&t);
                    }
                }
            }
        }
    }
    #pragma acc parallel present(reduction_array)
    {
        if (reduction_array[0] != reduction_host[0]){
            #pragma omp atomic
            err += 1;
        }
    }

    return err == 0;
}
#endif

#ifndef T3
//T3:wait,wait,devonly-1,pragma,V:2.5-2.7
int test3(){
    int err = 0;
    int device_num;
    int **reduction_host = (int **)malloc(LOOP_SIZE * sizeof(int *));
    int **reduction_array = (int **)malloc(LOOP_SIZE * sizeof(int *));

    for (int x = 0; x < LOOP_SIZE; ++x){
        reduction_host[x] = (int *)malloc(LOOP_SIZE * sizeof(int));
        reduction_array[x] = (int *)malloc(LOOP_SIZE * sizeof(int));
        for (int y = 0; y < LOOP_SIZE; ++y){
            reduction_host[x][y] = 1;
            reduction_array[x][y] = 1;
        }
    }

    #pragma acc data copyin(reduction_array[0:LOOP_SIZE][0:LOOP_SIZE])
    {
        #pragma acc parallel num_gangs(LOOPS) num_workers(4) vector_length(32) present(device_num)
        {
            unsigned int seed = device_num + 1;
            int distribution = 0;
            for (int j = 0; j < 1067 * 32 * 4 * acc_get_device_num(); j++)
                rand();
            for (int j = 0; j < 200; ++j){
                int n = rand_r(&seed) % 3;
                distribution = (n < 1)*(1 - distribution) + (n >= 1)*distribution;
            }
            reduction_array[0][0] = distribution;
        }
        #pragma acc parallel num_gangs(LOOPS) num_workers(4) vector_length(32) present(reduction_array, device_num)
        {
            int my_id = acc_get_device_num();
            unsigned int seed = my_id + 1;
            int mapped = 32*4*acc_get_num_workers()*acc_get_num_gangs()*my_id;
            for (int j = 0; j < 1067 * 32 * 4 * acc_get_device_num(); ++j)
                rand();
            for (int j = 0; j < 400; j++){
                int n = rand_r(&seed) % 2;
                int m = rand_r(&seed) % 16;
                int c = rand_r(&seed) % 4;
                if (n){
                    if (c == 0){
                        #pragma acc atomic capture
                            reduction_array[0][0] = mapped + m;
                    }
                    if (c == 1){
                        #pragma acc atomic capture
                            reduction_array[1][0] = mapped + m;
                    }
                    if (c == 2){
                        #pragma acc atomic capture
                            reduction_array[0][1] = mapped + m;
                    }
                    if (c == 3){
                        #pragma acc atomic capture
                            reduction_array[1][1] = mapped + m;
                    }
                }
                else
                {
                    if (c == 0){
                        int t;
                        t = mapped + m;
                        acc_wait(1,&t);
                    }
                    if (c == 1){
                        int t[2];
                        t[0] = reduction_array[0][1];
                        t[1] = mapped + m;
                        acc_wait(2,t);
                    }
                    if (c == 2){
                        int t[2];
                        t[0] = reduction_array[1][0];
                        t[1] = mapped + m;
                        acc_wait(2,t);
                    }
                    if (c == 3){
                        int t[3];
                        t[0] = reduction_array[1][0];
                        t[1] = reduction_array[0][1];
                        t[2] = mapped + m;
                        acc_wait(3,t);
                    }
                }
            }
        }
    }
    for (int x = 0; x < LOOP_SIZE; ++x){
        for (int y = 0; y < LOOP_SIZE; ++y){
            #pragma acc parallel present(reduction_array)
            {
                if (x == 0){
                    if (y == 0){
                        if (reduction_array[x][y] != reduction_host[y][x]){
                            #pragma omp atomic
                            err += 1;
                        }
                    }
                    else if (reduction_array[x][y] != reduction_host[y][x - 1]){
                        #pragma omp atomic
                        err += 1;
                    }
                }
                else if (y == 0){
                    if (reduction_array[x][y - 1] != reduction_host[y - 1][x]){
                        #pragma omp atomic
                        err += 1;
                    }
                }
                else if (reduction_array[x][y] != reduction_host[y - 1][x - 1]){
                    #pragma omp atomic
                    err += 1;
                }
            }
        }
    }
    return err == 0;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
       failed = failed + !test1();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
       failed = failed + !test3();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 2);
    }
#endif
    return failcode;
}