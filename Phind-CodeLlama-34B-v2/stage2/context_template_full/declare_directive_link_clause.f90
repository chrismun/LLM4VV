#ifndef T1
!T1:declare directive link clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(:), ALLOCATABLE :: a, b, c
        INTEGER :: n

        ALLOCATE(a(10), b(10), c(10))
        a = 1.0
        b = 2.0
        c = 0.0

        !$acc declare link(a, b, c)

        !$acc parallel
        !$acc loop
        DO n = 1, 10
          c(n) = a(n) + b(n)
        END DO
        !$acc end parallel

        DO n = 1, 10
          IF (c(n) .ne. 3.0) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(a, b, c)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
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
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM