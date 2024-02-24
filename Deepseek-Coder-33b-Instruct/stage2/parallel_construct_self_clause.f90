#ifndef T1
!T1:parallel construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i, sum_expected, sum_actual
        INTEGER, DIMENSION(N) :: array

        ! Initialize array
        DO i = 1, N
          array(i) = i
        END DO

        ! Compute expected sum
        sum_expected = N * (N + 1) / 2

        ! Compute sum using parallel construct self clause
        sum_actual = 0
        !$acc parallel loop self
        DO i = 1, N
          sum_actual = sum_actual + array(i)
        END DO
        !$acc end parallel loop

        ! Check if sum is correct
        IF (sum_actual .ne. sum_expected) THEN
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