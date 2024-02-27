!T1:serial construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER :: x

        ! ensure it is not optimized away
        x = 0
        !$acc parallel loop reduction(+:x)
        DO x = 1, 10
          x = x + 1
        END DO
        IF(x /= 10)THEN
          errors = errors + 1
        END IF

        !$acc update device(x) 

        !$acc serial
          !$acc loop private(x)
          DO x = 1, 10
            x = x + 5
          END DO
        !$acc end serial

        !$acc update host(x)
        IF (abs(x - 0) .gt. 1.0e-9) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT (failcode)
      END PROGRAM