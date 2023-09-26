#ifndef T1
!T1:data construct no_create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(KIND=8),DIMENSION(10):: a, b, c
        INTEGER:: device_index
        INTEGER:: x
        device_index = acc_get_device_num(acc_get_device_type())
        a = 1
        b = 2
        c = 0

        !$acc data copyin(a(1:10))
          !$acc parallel present(malo) copyout(c(1:10))
            { 
            {!$acc target loop independent}
            for (x = 0; x < 10; ++x){
              c[x] = (a[x] + b[x]);
            }
          }
          !$acc end parallel
        !$acc end data
        DO x = 0, 9
          IF (abs(c(x + 1) - (a(x + 1) + b(x + 1))) .gt. PRECISION) THEN
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