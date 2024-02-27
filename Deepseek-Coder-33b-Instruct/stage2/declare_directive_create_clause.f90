!T1:declare directive create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=8), DIMENSION(:), ALLOCATABLE :: a
        INTEGER :: i

        ALLOCATE(a(N))

        !$acc data create(a)
        !$acc parallel loop
        DO i = 1, N
          a(i) = i
        END DO
        !$acc end parallel loop
        !$acc end data

        ! Check if the array is allocated correctly
        DO i = 1, N
          IF (a(i) .ne. i) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a)

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