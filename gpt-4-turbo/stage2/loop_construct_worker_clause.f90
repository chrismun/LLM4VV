!T1:loop construct worker clause, V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.fh"
        
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: array(N), sum, expected_sum, i
        INTEGER :: errors = 0

        ! Initialization
        DO i = 1, N
          array(i) = 1
        END DO
        sum = 0
        expected_sum = N
        
        ! Parallel region with worker clause
        !$ACC PARALLEL LOOP REDUCTION(+:sum) WORKER
        DO i = 1, N
          sum = sum + array(i)
        END DO

        IF (sum .NE. expected_sum) THEN
          errors = errors + 1
        END IF

        ! Determine if the test passed or failed
        IF (errors .EQ. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.fh"
        EXTERNAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        CALL EXIT(failcode)
      END PROGRAM