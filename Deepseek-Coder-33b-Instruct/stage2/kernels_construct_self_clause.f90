#ifndef T1
!T1:kernels construct self clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        REAL, DIMENSION(N) :: a, b, c
        INTEGER :: i

        ! Initialize arrays
        DO i = 1, N
          a(i) = i * 1.0
          b(i) = i * 2.0
        END DO

        !$acc kernels copyin(a, b), copyout(c)
        !$acc loop self
        DO i = 1, N
          c(i) = a(i) + b(i)
        END DO
        !$acc end kernels

        ! Verify results
        DO i = 1, N
          IF (c(i) .ne. a(i) + b(i)) THEN
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