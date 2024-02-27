!T1:serial construct num_workers clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER :: x

        !$acc parallel num_workers(128)
          !$acc loop
          DO x = 1, REAL_LOOP
            y(x) = x
          END DO
        !$acc end parallel

        !$acc parallel num_workers(128)
          !$acc loop
          DO x = 1, REAL_LOOP
            IF (y(x) .NE. x) THEN
              errors = errors + 1
            END IF
          END DO
        !$acc end parallel

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