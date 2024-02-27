!T1:loop construct seq clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i, sum, sum_expected
        INTEGER, DIMENSION(N) :: array

        ! Initialize array
        DO i = 1, N
          array(i) = i
        END DO

        ! Compute sum using OpenACC seq clause
        sum = 0
        !$acc parallel loop seq
        DO i = 1, N
          sum = sum + array(i)
        END DO
        !$acc end parallel loop

        ! Compute expected sum
        sum_expected = N * (N + 1) / 2

        ! Check if the sums are equal
        IF (sum .ne. sum_expected) THEN
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