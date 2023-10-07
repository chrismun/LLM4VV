#ifndef T1
!T1:acc memcpy d2d,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1024
        REAL(8), DIMENSION(N) :: a, b, c
        INTEGER :: i

        ! Initialize arrays a and b
        DO i = 1, N
          a(i) = i
          b(i) = 0
        END DO

        ! Copy array a to array b using acc_memcpy_d2d
        CALL acc_memcpy_d2d(c(1), a(1), N * 8, 1, 1)

        ! Check if arrays a and b have the same values
        DO i = 1, N
          IF (a(i) .NE. c(i)) THEN
            errors = errors + 1
          END IF
        END DO

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
==============================