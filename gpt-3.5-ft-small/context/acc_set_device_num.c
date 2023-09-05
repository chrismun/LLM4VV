#ifndef T1
//T1:runtime,devonly-programming-mode,V:2.0-2.7
int test1(){
    int err = 0;
    int devnum = 0, t = 0;

    #pragma acc enter data copyin(devnum)

    for (t = 0; t < 10; t++) {
        #pragma acc parallel present(devnum)
        {
            int private_err = 0, private_devnum;
            #ifdef OPENARC_ARCH
                #pragma openarc private(private_devnum)
            #endif
            {
                private_devnum = t;
                #pragma acc set device_num(private_devnum, acc_get_device_type())
            }
            if (private_devnum != devnum) {
                private_err = 1;
            }
            #pragma acc atomic
                devnum = devnum + private_err;
        }
    }
    #pragma acc exit data copyout(devnum)

    if (devnum != 10){
        err += 1;
        printf("%d\n", devnum);
    }

    return err;
}
#endif

#ifndef T2
//T2:runtime,devonly-programming-mode,V:2.0-2.7
int test2(){
    int err = 0;
    int devnum = 0, t = 0;

    #pragma acc enter data copyin(devnum)

    for (t = 0; t < 9; t += 2) {
        #pragma acc parallel present(devnum)
        {
            int private_err = 0, private_devnum;
            #ifdef OPENARC_ARCH
                #pragma openarc private(private_devnum)
            #endif
            {
                private_devnum = t;
                #pragma acc set device_num(private_devnum, acc_get_device_type())
            }
            if (private_devnum != devnum) {
                private_err = 1;
            }
            #pragma acc atomic
                devnum = devnum + private_err;
        }
    }
    #pragma acc exit data copyout(devnum)

    if (devnum != 5){
        err += 1;
        printf("%d\n", devnum);
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}