!T1:kernels construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: n = 100
        INTEGER, DIMENSION(n) :: A
        INTEGER :: Sum, i, errors = 0

        ! Initialize array 'A'
        DO i = 1, n
          A(i) = i
        END DO
        
        Sum = 0
        !$ACC KERNELS REDUCTION(+:Sum)
        DO i = 1, n
          Sum = Sum + A(i)
        END DO
        !$ACC END KERNELS
        
        IF (Sum /= n*(n+1)/2) THEN
          errors = errors + 1
        END IF

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