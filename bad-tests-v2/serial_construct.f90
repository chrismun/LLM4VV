#ifndef T1
!T1:serial construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: x = 1

        #pragma acc parallel loop
        DO WHILE(x < 16)
          acc_attach(&x, sizeof(x))
          x = x + 1
        END DO
        DO WHILE(x > 1)
          DO WHILE(x > 1000)
            #pragma acc serial loop
            DO WHILE (x > 1000)
              x = x/2
            END DO
          END DO
          x = x - 1
          IF (x > 1) THEN
            #pragma acc loop vector
            DO WHILE (x > 1)
              x = x - 1
            END DO
          END IF
        END DO
        DO WHILE(x < 8)
          acc_detach(&x)
          x = x * 2
        END DO
        IF (x .ne. 8) THEN
          errors = errors + 1
        END IF


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