#ifndef T1
!T1:data deviceptr clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL, DIMENSION(10) :: a, b, c
        REAL, DIMENSION(:), POINTER :: ap, bp, cp
        INTEGER :: i

        !$acc data deviceptr(ap, bp, cp)
          ap => a
          bp => b
          cp => c
        !$acc end data

        !$acc parallel loop
        DO i = 1, 10
          ap(i) = 1.0
          bp(i) = 2.0
          cp(i) = ap(i) + bp(i)
        END DO
        !$acc end parallel loop

        DO i = 1, 10
          IF (ABS(cp(i) - 3.0) .gt. 1e-6) THEN
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