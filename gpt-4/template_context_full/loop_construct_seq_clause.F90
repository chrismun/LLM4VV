#ifndef T1
!T1:loop construct seq clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: i
        INTEGER, DIMENSION(100) :: a, b, c
        INTEGER :: errors = 0

        ! Initialize arrays
        a = (/ (i, i = 1, 100) /)
        b = (/ (i, i = 1, 100) /)
        c = (/ (0, i = 1, 100) /)

        ! Perform vector addition on accelerator
        !$ACC PARALLEL LOOP SEQ
        DO i = 1, 100
            c(i) = a(i) + b(i)
        END DO
        !$ACC END PARALLEL

        ! Check for errors
        DO i = 1, 100
            IF (c(i) /= 2*i) THEN
                errors = errors + 1
            END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION
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
      END PROGRAM main