!T1:reference counters,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        REAL, DIMENSION(N) :: a, b
        INTEGER :: i

        ! Initialize arrays
        DO i = 1, N
          a(i) = 1.0 * i
          b(i) = 0.0
        END DO

        ! Copy data to device
        !$acc data copyin(a) copyout(b)

        ! Perform computation
        !$acc parallel loop
        DO i = 1, N
          b(i) = a(i) * 2.0
        END DO

        !$acc end data

        ! Check results
        DO i = 1, N
          IF (b(i) .NE. a(i) * 2.0) THEN
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