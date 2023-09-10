#ifndef T1
!T1:acc wait any,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_num, device_type
        REAL(8), DIMENSION: b(99), b(99)

        device_num = acc_get_device_num(device_type)
        IF (device_type .eq. acc_device_nvidia) THEN
          device_num = acc_get_device_num(acc_device_host)
        END IF
        !$acc enter data create(a(1:99), b(1:99))
        DO i = 1, 99
          a(i) = 0
          b(i) = i
        END DO
        !$acc update device(a(1:99))
        
        !$acc kernels loop independent async(1)
        DO i = 1, 99
          a(i) = a(i) + 1
        END DO
        
        call acc_attach(a(1:99))
        wait_1 = acc_async_test(a(1), i)
        DO i = 2, 99
            wait_1 = acc_async_test(a(i), i) .or. wait_1
        done
        call acc_detach(a(1))
        DO i = 1, 99
            IF (a(i) .ne. 2) THEN
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