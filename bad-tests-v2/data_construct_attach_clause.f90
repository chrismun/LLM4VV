#ifndef T1
!T1:data construct attach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: a, b, c
        INTEGER, POINTER :: ap, bp, cp
        INTEGER :: i

        ap => a
        bp => b
        cp => c

        !$acc data attach(ap, bp, cp)
        !$acc end data

        !$acc parallel present(ap, bp, cp)
        DO i = 1, 10
          ap(i) = i
          bp(i) = i * 2
          cp(i) = i * 3
        END DO
        !$acc end parallel

        DO i = 1, 10
          IF (ap(i) .NE. i .OR. bp(i) .NE. i * 2 .OR. cp(i) .NE. i * 3) THEN
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