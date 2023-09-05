#ifndef T1
//T1:runtime,ini,devonly-acc:racc_init,devonly-acc:racc_shutdown,devonly-acc:async-1
int test1(){
    
    real_t* a = (real_t *)malloc(n * sizeof(real_t));
    real_t* b = (real_t *)malloc(n * sizeof(real_t));
    int errors = 0;
    int dev;

    for (dev = 0; dev < acc_get_num_devices(acc_get_device_type()); ++dev){
        acc_init_device(dev, acc_get_device_type());
        #pragma acc enter data copyin(a [0:n], b [0:n])
    }

    #pragma acc parallel present(a[0:n], b[0:n])
    {
        int id = acc_get_device_num(acc_get_device_type());
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 1;
            b[x] = 0;
        }
        if (id == acc_get_device_num(acc_get_device_type())){
          for (int x = 0; x < n; ++x){
              b[x] = a[x];
          }
        }
    }

    for (dev = 0; dev < acc_get_num_devices(acc_get_device_type()); ++dev){
      if (dev == acc_get_device_num(acc_get_device_type())){
        #pragma acc exit data copyout(b [0:n])
      }
      acc_init(acc_get_device_type());
      acc_set_device_num(dev, acc_get_device_type());
      #pragma acc enter data create(a [0:n])
      acc_async_enter(acc_async_device_sync, dev, acc_get_device_type());
      #pragma acc parallel present(a[0:n])
      {
          #pragma acc loop
          for (int x = 0; x < n; ++x){
              a[x] = 0;
          }
      }
      acc_async_exit(acc_async_device_sync, dev, acc_get_device_type());
      #pragma acc exit data delete(a [0:n])
      acc_shutdown(acc_get_device_type());
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - 1) > PRECISION){
            errors += 1;
        }
    }

    return errors;
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