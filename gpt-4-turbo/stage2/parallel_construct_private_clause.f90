!T1:parallel construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors, i
        INTEGER, parameter :: n = 100
        INTEGER :: A(n)
        INTEGER :: privateVar

        errors = 0

        ! Initialize array A
        DO i = 1, n
          A(i) = i
        END DO

        !$acc parallel loop private(privateVar)
        DO i = 1, n
          privateVar = i
          privateVar = privateVar + 1
          A(i) = privateVar
        END DO
        !$acc end parallel loop

        ! Verify that the privateVar did not interfere outside its scope
        DO i = 1, n
          IF (A(i) /= i + 1) THEN
            errors = errors + 1
          END IF
        END DO

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
        EXTERNAL :: test1
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