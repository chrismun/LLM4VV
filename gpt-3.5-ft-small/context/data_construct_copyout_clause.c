int num_workers, int pen) {
    return worker1[num_workers]->pen[pin] == pen;
}

int test_copyout_device(){
    int err = 0;

    worker **worker_copy = (worker **)malloc((1 + nVIDIA_device_num)*sizeof(worker *));
    worker **worker_device = (worker **)malloc((1 + nVIDIA_device_num)*sizeof(worker *));
    real_t **a_copy = (real_t **)malloc((1 + nVIDIA_device_num)*sizeof(real_t *));
    real_t **a = (real_t **)malloc((1 + nVIDIA_device_num)*sizeof(real_t *));
    real_t *scalar12 = (real_t *)malloc(2*sizeof(real_t));
    real_t *scalar2 = (real_t *)malloc(sizeof(real_t ));

    real_t multiply = 2;

    for (int x = 0; x <= nVIDIA_device_num; ++x){
        worker_copy[x] = (worker *)malloc((n+1)*sizeof(worker));
        a_copy[x] = (real_t *)malloc((n+1)*sizeof(real_t));
        worker_device[x] = (worker *)malloc((n + 1) * sizeof(worker));
        a[x] = (real_t *)malloc((n + 1) * sizeof(real_t));
        for (int y = 0; y < n; ++y){
            a[x][y] = 1;
            a_copy[x][y] = 1;
            for (int z = 0; z < 10; ++z){
                worker_copy[x][y].a[z] = 1;
                worker_copy[x][y].b[z] = 1;
                worker_copy[x][y].c[z] = 1;
                worker_copy[x][y].d[z] = 1;
                worker_device[x][y].a[z] = 1;
                worker_device[x][y].b[z] = 1;
                worker_device[x][y].c[z] = 1;
                worker_device[x][y].d[z] = 1;
            }
            worker_copy[x][y].id = 0;
            worker_device[x][y].id = 0;
            worker_device[x][y].a[0] = 1;
            if (y == 0){
                worker_copy[x][y].a[0] = 2;
                worker_copy[x][y].id = -1;
                worker_device[x][y].id = -1;
            }
        }
    }

    #pragma acc data copyin(a[0:n][0:n], worker_device[0:n][0:n][0:9]) copyout(a[0:n][0:n], worker_device[0:n][0:n][:])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    worker_device[0][y].d[0] = 1;
                    if (worker_device[0][y].id == -1){
                        worker_device[0][y].d[0] = 2;
                    }
                    for (int z = 1; z < 10; ++z){
                        worker_device[0][y].d[0] += worker_device[0][y].a[z-1] + worker_device[0][y].b[z-1]
                                                  + worker_device[0][y].c[z-1];
                        worker_device[0][y].a[z-1] = worker_device[0][y].d[z-1] + worker_device[0][y].c[z-1]
                                                    + worker_device[0][y].b[z-1];
                        worker_device[0][y].b[z-1] = worker_device[0][y].d[z-1] + worker_device[0][y].a[z-1]
                                                    + worker_device[0][y].c[z-1];
                        worker_device[0][y].c[z-1] = worker_device[0][y].d[z-1] + worker_device[0][y].b[z-1]
                                                    + worker_device[0][y].a[z-1];
                    }
                    worker_device[0][y].a[9] = worker_device[0][y].c[0] + worker_device[0][y].b[0] + worker_device[0][y].a[0];
                }
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    for (int z = 1; z < 10; ++z){
                        if (worker_device[0][y].a[z-1] != worker_device[0][y].a[z] - worker_device[0][y].b[z-1]
                            - worker_device[0][y].c[z-1]){
                            worker_device[0][y].id = -1;
                        }
                    }
                }
            }
        }
    }

    worker_copy[0][4].id = 0;
    worker_copy[0][4].a[9] = 10;
    #pragma acc data copyin(a_copy[0:n][0:n], worker_copy[0:n][0:n][0:9], scalar12[0:1], worker_copy[0:n][0:n][:]) copyout(a_copy[0:n][0:n], worker_copy[0:n][0:n][:])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    worker_copy[0][y].d[0] = 1;
                    if (worker_copy[0][y].id == -1){
                        worker_copy[0][y].d[0] = 2;
                    }
                    for (int z = 1; z < 10; ++z){
                        worker_copy[0][y].d[0] += worker_copy[0][y].a[z-1] + worker_copy[0][y].b[z-1] + worker_copy[0][y].c[z-1];
                        worker_copy[0][y].a[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].c[z-1] + worker_copy[0][y].b[z-1];
                        worker_copy[0][y].b[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].a[z-1] + worker_copy[0][y].c[z-1];
                        worker_copy[0][y].c[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].b[z-1] + worker_copy[0][y].a[z-1];
                    }
                }
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    for (int z = 1; z < 10; ++z){
                        if (worker_copy[0][y].a[z-1] != worker_copy[0][y].a[z] - worker_copy[0][y].b[z-1] - worker_copy[0][y].c[z-1]){
                            worker_copy[0][y].id = -1;
                        }
                    }
                    worker_copy[0][y].a[9] = worker_copy[0][y].c[0] + worker_copy[0][y].b[0] + worker_copy[0][y].a[0];
                }
            }
            worker_copy[0][4].id = 0;
            #pragma acc loop
            for (int x = 0; x < 2; ++x){
                scalar12[x] = 1;
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < 10; ++y){
                    worker_copy[0][x].a[y] = x + y;
                }
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    for (int z = 1; z < 10; ++z){
                        worker_copy[0][y].d[0] += worker_copy[0][y].a[z-1] + worker_copy[0][y].b[z-1] + worker_copy[0][y].c[z-1];
                        worker_copy[0][y].a[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].c[z-1] + worker_copy[0][y].b[z-1];
                        worker_copy[0][y].b[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].a[z-1] + worker_copy[0][y].c[z-1];
                        worker_copy[0][y].c[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].b[z-1] + worker_copy[0][y].a[z-1];
                    }
                }
                #pragma acc loop
                for (int y = 0; y < n; ++y){
                    for (int z = 1; z < 10; ++z){
                        if (worker_copy[0][y].a[z-1] != worker_copy[0][y].a[z] - worker_copy[0][y].b[z-1] - worker_copy[0][y].c[z-1]){
                            worker_copy[0][y].id = -1;
                        }
                    }
                }
            }
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < 10; ++y){
                    #pragma acc loop
                    for (int z = 1; z < 10; ++z){
                        worker_copy[0][x].d[0] += worker_copy[0][x].a[z-1] + worker_copy[0][x].b[z-1] + worker_copy[0][x].c[z-1];
                    }
                    worker_copy[0][x].a[9] = worker_copy[0][x].c[0] + worker_copy[0][x].b[0] + worker_copy[0][x].a[0];
                }
            }
            #pragma acc loop
            for (int x = 0; x < 2; ++x){
                scalar2[x] = 1;
            }
        }
    }


    #pragma acc data present(a_copy[0:n][0:n], scalar12[0:2]) copyout(a[0:n][0:n]) copyin(a_copy[0:n][0:n], scalar2[0:1], worker_copy[0:n][0:n][:]) copyout(a_copy[0:n][0:n], worker_copy[0:n][0:n][:])
    {
        #pragma acc parallel present(worker_copy[0:n][0:n][:], scalar2[0:1])
        {
            #pragma acc loop gang
            for (int x = 0; x < n; ++x){
                #pragma acc loop worker
                for (int y = 0; y < n; ++y){
                    for (int z = 1; z < 10; ++z){
                        worker_copy[0][y].d[0] += worker_copy[0][y].a[z-1] + worker_copy[0][y].b[z-1] + worker_copy[0][y].c[z-1];
                        worker_copy[0][y].a[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].c[z-1] + worker_copy[0][y].b[z-1];
                        worker_copy[0][y].b[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].a[z-1] + worker_copy[0][y].c[z-1];
                        worker_copy[0][y].c[z-1] = worker_copy[0][y].d[z-1] + worker_copy[0][y].b[z-1] + worker_copy[0][y].a[z-1];
                    }
                }
            }
        }
        #pragma acc parallel present(a_copy[0:n][0:n],scalar12[0:1]) copyin(worker_copy[0:n][0:n][:])
        {
            int errors = 0;
            #pragma acc loop gang private(errors)
            for (int x = 0; x < n; ++x){
                int worker_errors = 0;
                #pragma acc loop vector private(worker_errors)
                for (int y = 0; y < n; ++y){
                    #pragma acc loop seq
                    for (int z = 1; z < 10; ++z){
                        worker_copy[0][y].a[z] = worker_copy[0][y].a[z-1] - worker_copy[0][y].b[z-1] - worker_copy[0][y].c[z-1];
                    }
                }
                #pragma acc loop seq reduction(+:worker_errors)
                for (int y = 0; y < n; ++y){
                    if (fabs(worker_copy[0][y].a[9] - worker_copy[0][y].c[0] - worker_copy[0][y].b[0] - worker_copy[0][y].a[0]) > (10 * PRECISION)){
                        worker_errors += 1;
                    }
                }
                if (worker_errors != 0){
                    errors += 1;
                }
            }
            #pragma acc loop vector reduction(+:errors)
            for (int x = 0; x < n; ++x){
                for (int z = 1; z < 10; ++z){
                    scalar12[0] += worker_copy[0][x].a[z-1] + worker_copy[0][x].b[z-1] + worker_copy[0][x].c[z-1];
                }
            }
            int seq_errors = 0;
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < n; ++y){
                    for (int z = 1; z < 10; ++z){
                        if (worker_copy[0][y].a[z-1] != worker_copy[0][y].a[z] - worker_copy[0][y].b[z-1] - worker_copy[0][y].c[z-1]){
                            seq_errors = 1;
                        }
                    }
                }
            }
            for (int x = 0; x < 2; ++x){
                scalar2[x] += scalar12[0];
            }
            if (errors != 0 || seq_errors != 0){
                err = 1;
            }
        }
        #pragma acc parallel present(a_copy[0:n][0:n], worker_copy[0:n][0:n][:]) copyout(a_copy[0:n][0:n])
        {
            int errors = 0;
            #pragma acc loop gang private(errors)
            for (int x = 0; x < n; ++x){
                int worker_errors = 0;
                #pragma acc loop vector private(worker_errors)
                for (int y = 0; y < n; ++y){
                    #pragma acc loop seq
                    for (int z = 0; z < 10; ++z){
                        worker_copy[0][y].a[z] = worker_copy[0][y].a[z] - worker_copy[0][y].b[0] - worker_copy[0][y].c[0];
                    }
                }
                #pragma acc loop seq reduction(+:worker_errors)
                for (int y = 0; y < n; ++y){
                    for (int z = 1; z < 10; ++z){
                        if (worker_copy[0][y].a[z-1] != -worker_copy[0][y].b[0] - worker_copy[0][y].c[0]){
                            worker_errors += 1;
                        }
                    }
                }
                if (worker_errors != 0){
                    errors += 1;
                }
            }