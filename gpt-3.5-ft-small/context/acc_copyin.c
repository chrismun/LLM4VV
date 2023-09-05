#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.5-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(nz * ny * nx * sizeof(real_t));
    real_t *b = (real_t *)malloc(nz * ny * nx * sizeof(real_t));
    real_t deviation;
    real_t *a_copy = acc_copyin(a, nz * ny * nx * sizeof(real_t));
    real_t *dev = (real_t * )malloc(10 * sizeof(real_t));
    dev[0] = 0;
    real_t *data;
    data = (real_t*)malloc(2 * (sizeof(real_t) * 128 + sizeof(real_t *)) + sizeof(real_t *) * 10);
    real_t *data_copy = acc_copyin(data, 2 * (sizeof(real_t) * 128 + sizeof(real_t *)) + sizeof(real_t *) * 10);
    data_copy[1] = (real_t) data_copy + 2 * sizeof(real_t *);
    real_t *dev_a = (real_t*) data_copy[1];
    real_t *dev_b = (real_t*) (dev_a + sizeof(real_t) * 128);
    real_t *dev_dev = (real_t*) (dev_b + sizeof(real_t) * 128);
    dev[0] = (real_t) dev_a;
    dev[1] = (real_t) dev_b;
    dev[2] = (real_t) dev_dev;
    real_t *dev_copy = acc_copyin(dev, 10 * sizeof(real_t));
    dev_a = (real_t*) dev_copy[0];
    dev_b = (real_t*) dev_copy[1];
    dev_dev = (real_t*) dev_copy[2];
    real_t *a_internal;
    real_t *a_internal_copy = acc_copy(a_internal, AN);

    for (int x = 0; x < 128; ++x){
        dev_a[x] = 0;
        for (int y = 0; y < 128; ++y){
            for (int z = 0; z < 10; ++z){
                dev_a[x] += a_internal_copy[x];
            }
        }
    }

    for (int x = 0; x < 128; ++x){
        dev_b[x] = 0;
    }
    for (int x = 0; x < 128; ++x){
        for (int y = 0; y < 128; ++y){
            for (int z = 0; z < 10; ++z){
                dev_b[y] += a_internal_copy[x] + dev_dev[0];
            }
        }
    }
    // Cache on device, copyin from host a copy, check
    for (int x = 0; x < nx; ++x){
        for (int y = 0; y < ny; ++y){
            for (int z = 0; z < nz; ++z){
                a[z + y * nz + x * nz * ny] = rand() / (real_t)(RAND_MAX / 10);
            }
        }
    }
    for (int x = 0; x < 128; ++x){
        dev_a[x] = 0;
        for (int y = 0; y < 128; ++y){
            for (int z = 0; z < 10; ++z){
                dev_a[x] += a[z + y * nz + x * nz * ny];
            }
        }
    }
    for (int x = 0; x < 128; ++x){
        dev_b[x] = 0;
    }
    for (int x = 0; x < nx; ++x){
        for (int y = 0; y < ny; ++y){
            for (int z = 0; z < 10; ++z){
                dev_b[y] += a[z + y * nz + x * nz * ny] + dev_dev[0];
            }
        }
    }
    acc_copyin_async(a, nz * ny * nx * sizeof(real_t), 0);
    for (int x = 0; x < 128; ++x){
        dev_a[x] = 0;
        for (int y = 0; y < 128; ++y){
            for (int z = 0; z < 10; ++z){
                dev_a[x] += a[z + y * nz + x * nz * ny];
            }
        }
    }
    for (int x = 0; x < 128; ++x){
        dev_b[x] = 0;
    }
    for (int x = 0; x < 128; ++x){
        for (int y = 0; y < 128; ++y){
            for (int z = 0; z < 10; ++z){
                dev_b[y] += a[z + x * nz * ny + y * nz];
            }
        }
    }
    acc_copyin_async(a, nz * ny * nx * sizeof(real_t), 0);
    for (int x = 0; x < 128; ++x){
        for (int y = 0; y < 128; ++y){
            b[y + x * ny] = 0;
        }
    }
    for (int x = 0; x < nz; ++x){
        for (int y = 0; y < ny; ++y){
            for (int z = 0; z < nx; ++z){
                b[y + z * ny] += a[y + z * ny + x * nz * ny];
            }
        }
    }
    acc_copyin_async(a, nz * ny * nx * sizeof(real_t), 0);
    for (int x = 0; x < 128; ++x){
        for (int y = 0; y < 128; ++y){
            for (int z = 0; z < 10; ++z){
                dev_dev[z] = rand() / (real_t)(RAND_MAX / 10);
            }
        }
    }
    for (int x = 0; x < nx; ++x){
        for (int y = 0; y < ny; ++y){
            for (int z = 0; z < 10; ++z){
                b[y + x * ny] += a[y + x * ny + z * nz * ny];
            }
        }
    }
    #pragma acc exit data copyout(a[0:nz * ny * nx], b[0:ny * nx])
    for (int x = 0; x < nx; ++x){
        for (int y = 0; y < ny; ++y){
            for (int z = 0; z < nz; ++z){
                if (fabs(b[z + y * nz + x * nz * ny] - a[z + y * nz + x * nz * ny] * 111 + dev_a[x]) > PRECISION){
                    err = 1;
                }
            }
        }
    }
    #pragma acc data delete(a, dev) copyout(dev_b[0:128])
    {
        real_t* b_b = (real_t*)data_copy[2];
        for (int x = 0; x < 128; ++x){
            for (int y = 0; y < 128; ++y){
                b_b[x] += dev_b[y];
            }
        }
    }
    for (int x = 0; x < 128; ++x){
        if (fabs(dev_b[x] - (y + 1) * 128 * 10 + (x + 1) * 128 * y * 10) > PRECISION){
            err = 1;
        }
    }
    if (err != 0){
        err = 0;
        for (int x = 0; x < 128; ++x){
            for (int y = 0; y < 128; ++y){
                for (int z = 0; z < 10; ++z){
                    dev_a[x] += a_internal_copy[x];
                }
            }
        }
        for (int x = 0; x < 128; ++x){
            dev_b[x] = 0;
            for (int y = 0; y < 128; ++y){
                for (int z = 0; z < 10; ++z){
                    dev_b[y] += a_internal_copy[x] + dev_dev[0];
                }
            }
        }
        for (int x = 0; x < nx; ++x){
            for (int y = 0; y < ny; ++y){
                for (int z = 0; z < nz; ++z){
                    a[z + y * nz + x * nz * ny] = rand() / (real_t)(RAND_MAX / 10);
                }
            }
        }
        for (int x = 0; x < 128; ++x){
            dev_a[x] = 0;
            for (int y = 0; y < 128; ++y){
                for (int z = 0; z < 10; ++z){
                    dev_a[x] += a[z + y * nz + x * nz * ny];
                }
            }
        }
        for (int x = 0; x < 128; ++x){
            dev_b[x] = 0;
        }
        for (int x = 0; x < 128; ++x){
            for (int y = 0; y < 128; ++y){
                for (int z = 0; z < 10; ++z){
                    dev_b[y] += a[z + x * nz * ny + y * nz];
                }
            }
        }
        acc_copyin_async(a, nz * ny * nx * sizeof(real_t), 0);
        for (int x = 0; x < 128; ++x){
            dev_a[x] = 0;
            for (int y = 0; y < 128; ++y){
                for (int z = 0; z < 10; ++z){
                    dev_a[x] += a[z + y * nz + x * nz * ny];
                }
            }
        }
        for (int x = 0; x < 128; ++x){
            dev_b[x] = 0;
        }
        for (int x = 0; x < 128; ++x){
            for (int y = 0; y < 128; ++y){
                for (int z = 0; z < 10; ++z){
                    dev_b[y] += a[z + x * nz * ny + y * nz];
                }
            }
        }
        acc_copyin_async(a, nz * ny * nx * sizeof(real_t), 0);
        for (int x = 0; x < 128; ++x){
            for (int y = 0; y < 128; ++y){
                b[y + x * ny] = 0;
            }
        }
        for (int x = 0; x < nz; ++x){
            for (int y = 0; y < ny; ++y){
                for (int z = 0; z < nx; ++z){
                    b[y + z * ny] += a[y + z * ny + x * nz * ny];
                }
            }
        }
        acc_copyin_async(a, nz * ny * nx * sizeof(real_t), 0);
        for (int x = 0; x < 128; ++x){
            for (int y = 0; y < 128; ++y){
                for (int z = 0; z < 10; ++z){
                    dev_dev[z] = rand() / (real_t)(RAND_MAX / 10);
                }
            }
        }
        for (int x = 0; x < nx; ++x){
            for (int y = 0; y < ny; ++y){
                for (int z = 0; z < 10; ++z){
                    b[y + x * ny] += a[y + x * ny + z * nz * ny];
                }
            }
        }
        #pragma acc exit data copyout(a[0:nz * ny * nx], b[0:ny * nx])
        for (int x = 0; x < nx; ++x){
            for (int y = 0; y < ny; ++y){
                for (int z = 0; z < nz; ++z){
                    if (fabs(b[z + y * nz + x * nz * ny] - a[z + y * nz + x * nz * ny] * 111 + dev_a[x]) > PRECISION){
                        err += 1;
                    }
                }
            }
        }
        #pragma acc data delete(a, dev) copyout(dev_b[0:128])
        {
            real_t* b_b = (real_t*)data_copy[2];
            for (int x = 0; x < 128; ++x){
                for (int y = 0; y < 128; ++y){
                    b_b[x] += dev_b[y];
                }
            }
        }

        for (int x = 0; x < 128; ++x){
            if (fabs(dev_b[x] - (y + 1) * 128 * 10 + (x + 1) * 128 * y * 10) > PRECISION){
                err += 1;
            }
        }
    }

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