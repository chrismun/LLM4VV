!T1:routine directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0

        ! Complete the test for the routine directive here
        REAL(8), PARAMETER :: pi = 3.1415926536
        REAL(8), DIMENSION(100) :: a, b
        INTEGER :: x

        ! Calculating the sinc function
        DO x = 1, 100
          a(x) = (x - 50) * (pi / 10)
          b(x) = a(x)
        END DO

        !$acc data copyin(a(1:100)) copyout(b(1:100))
          !$acc routine seq
          DO x = 1, 100
            b(x) = sincos(a(x))
          END DO
        !$acc end data

        DO x = 1, 100
          IF (abs(b(x) - sincos(a(x))) .gt. 10.0 * pi) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc end

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