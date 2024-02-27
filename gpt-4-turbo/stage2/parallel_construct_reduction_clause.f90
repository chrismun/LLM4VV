! Fortran code to test OpenACC's parallel construct reduction clause.
! It calculates the sum of an array's elements in parallel and checks if the result is as expected.

!T1:parallel construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, PARAMETER :: N=100
        INTEGER :: errors = 0
        INTEGER :: sum, expected_sum, i
        INTEGER, DIMENSION(N) :: a

        ! Initialize array
        DO i = 1, N
          a(i) = 1
        END DO

        sum = 0
        expected_sum = N

        ! use OpenACC parallel loop with reduction
        !$ACC PARALLEL LOOP REDUCTION(+:sum)
        DO i = 1, N
          sum = sum + a(i)
        END DO
        !$ACC END PARALLEL LOOP

        IF (sum .ne. expected_sum) THEN
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