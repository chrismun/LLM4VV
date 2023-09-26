#ifndef T1
!T1:wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER :: i, n = 10000
        REAL, DIMENSION(n) :: a, b, c
        REAL, DIMENSION(:), ALLOCATABLE :: d

        ! Initialize arrays
        DO i = 1, n
          a(i) = i
          b(i) = 2*i
          c(i) = 0
        END DO

        !$ACC PARALLEL LOOP COPYIN(a, b) COPYOUT(c) async
        DO i = 1, n
          c(i) = a(i) + b(i)
        END DO

        ! Wait until the asynchronous operations have completed
        !$ACC WAIT

        ! Check the results
        ALLOCATE(d(n))
        DO i = 1, n
          d(i) = a(i) + b(i)
        END DO

        IF (ANY(d /= c)) THEN
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