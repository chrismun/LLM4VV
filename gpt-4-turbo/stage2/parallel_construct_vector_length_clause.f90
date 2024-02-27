! This code snippet is meant to be part of a larger testsuite, and it requires
! an OpenACC implementation and external test framework support to run.
! Assume acc_testsuite.Fh handles test framework initialization and shutdown procedures.

!T1:parallel construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, PARAMETER :: N = 1024
        INTEGER :: errors = 0
        REAL, DIMENSION(N) :: a
        INTEGER :: i

        ! Initialize array
        a = 1.0

        ! Use parallel construct with vector_length clause
        !$acc parallel loop vector_length(128)
        DO i = 1, N
          a(i) = a(i) + 1.0
        END DO
        !$acc end parallel

        ! Check results
        DO i = 1, N
          IF (a(i) /= 2.0) THEN
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
        EXTERNAL test1
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