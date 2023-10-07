#ifndef T1
!T1:data construct copyout clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: a, b, c
        INTEGER :: i, n = 10000

        ALLOCATE(a(n), b(n), c(n))

        a = 1
        b = 2
        c = 0

!$ACC PARALLEL LOOP COPYOUT(c(1:n)) COPYIN(a(1:n), b(1:n))
        DO i = 1, n
           c(i) = a(i) + b(i)
        END DO
!$ACC END PARALLEL LOOP

        DO i = 1, n
           IF (c(i) /= 3) THEN
              errors = errors + 1
           END IF
        END DO

        DEALLOCATE(a, b, c)

        IF (errors .eq. 0) THEN
           test1 = .TRUE.
        ELSE
           test1 = .FALSE.
        END IF
      END FUNCTION test1
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
          failcode = failcode + 1
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main