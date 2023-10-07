void test_loop_auto()
{
    int err = 0;
    srand(SEED);
    rdata_t * a = (rdata_t *)malloc(n * sizeof(rdata_t));
    rdata_t * b = (rdata_t *)malloc(n * sizeof(rdata_t));
    data_t * c = (data_t *)malloc(n * sizeof(data_t));
    data_t * c_copy = (data_t *)malloc(n * sizeof(data_t));
    real_t prev = 0.0;
    real_t current = 0.0;

    real_t l_check[n];

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < 2; ++y){
            a[x].x[y] = rand() / (real_t)(RAND_MAX / 10);
            b[x].x[y] = rand() / (real_t)(RAND_MAX / 10);
        }
        c[x] = (data_t) ((int) (rand() / (real_t) (RAND_MAX + 1) * 10 + 1));
    }
    #pragma acc enter data copyin(a[0:n], b[0:n]) create(c[0:n])
    #pragma acc parallel present(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = (c[x] * 2) / a[x].x[0];
        }
    }
    for (int x = 0; x < n; ++x){
        current = 0.0;
        for (int y = 0; y < 2; ++y){
            current += a[x].x[y] * b[x].x[y];
        }
        for (int y = 0; y <= x; ++y){
            current += c[y];
        }
        if (prev > current){
            current = prev;
        }
        prev = current;
        l_check[x] = prev;
        prev = current;
    }
    #pragma acc exit data delete(a[0:n], b[0:n]) copyout(c_copy[0:n])
    for (int x = 0; x < n; ++x){
        if (fabs(l_check[x] - c_copy[x]) > PRECISION * l_check[x]){
            err += 1;
        }
    }

    if (err != 0){
        for (int x = 0; x < 1; ++x){
            current = 0.0;
            for (int y = 0; y < 2; ++y){
                current += a[x].x[y] * b[x].x[y];
            }
            for (int y = 0; y <= x; ++y){
                current += c[y];
            }
            prev = current;
            for (int y = 0; y < 2; ++y){
                current = 0.0;
                for (int z = 0; z < 2; ++z){
                    current += a[x].x[z] * b[x].x[z];
                }
                for (int z = 0; z <= y; ++z){
                    current += c[y];
                }
                if (prev > current){
                    current = prev;
                }
                prev = current;
            }
            c_copy[x] = prev;
        }
        for (int x = 0; x < n; ++x){
            if (fabs(c_copy[x] - l_check[x]) > PRECISION * c_copy[x]){
                err += 1;
                break;
            }
        }
        if (err != 0){
            err = 0;
            for (int x = 0; x < n; ++x){
                current = 0.0;
                for (int y = 0; y < 2; ++y){
                    current += a[x].x[y] * b[x].x[y];
                }
                for (int y = 0; y <= x; ++y){
                    current += c[y];
                }
                prev = current;
                for (int y = 0; y < 2; ++y){
                    current = 0.0;
                    for (int z = 0; z < 2; ++z){
                        current += a[x].x[z] * b[x].x[z];
                    }
                    for (int z = 0; z <= y; ++z){
                        current += c[y];
                    }
                    if (prev > current){
                        current = prev;
                    }
                    prev = current;
                }
                l_check[x] = prev;
            }
            for (int x = 0; x < n; ++x){
                if (fabs(c_copy[x] - l_check[x]) > PRECISION * c_copy[x]){
                    err += 1;
                    break;
                }
            }
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = 0;
        failed = test_loop_auto() != 0;
        if (failed != 0){
            failcode = failcode + (1 << x);
        }
    }
    return failcode;
}