#ifndef T1
!T1:data deviceptr clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(10):: b
        REAL(8),DIMENSION(10):: c
        REAL(8),DIMENSION(10), DEVICE :: a
        INTEGER,DEVICE::dev
        REAL(8):: temp
        INTEGER:: random_seed
        LOGICAL,DIMENSION(1)::devtest
        REAL(8),DIMENSION(10):: host_a
        REAL(8),DIMENSION(10):: host_c
        INTEGER:: x

        !Initilization on host
        devtest(1) = .TRUE.
        !$acc enter data copyin(devtest(1:1))
        !$acc parallel present(devtest(1:1))
          dev = 0
          dev = omp_get_initial_device()
          IF (dev .eq. acc_get_device_num(acc_get_device_type())) then
            devtest(1) = .FALSE.
          END IF
        !$acc end parallel
        !$acc exit data delete(devtest(1:1))

        SEED('data') 
        CALL RANDOM_SEED()
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0
        host_a = a
        host_c = c

        !Calculation on device
        !$acc data deviceptr(a)
          !$acc parallel loop
          DO i = 1, 10
            a(i) = a(i) + b(i)
          END DO
        !$acc end data
        
        !Calculation on host
        DO i = 1, 10
          host_a(i) = host_a(i) + b(i)
        END DO

        !Copy back to host from device.
        c = host_c
        a = host_a

        !Verification
        DO i = 1, 10
          IF (ABS(a(i) - c(i)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO


        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM