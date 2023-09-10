#ifndef T1
!T1:loop construct worker clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: x = 0
        INTEGER, DIMENSION(2) :: x_ = (/0, 0/)
        REAL(8), DIMENSION(1) :: random
        REAL(8), DIMENSION(LOOPCOUNT, 2) :: a, b

        call random_number(random)
        a = 1+random
        b = 2*random
        
        !$acc data copyin(a(1:LOOPCOUNT, 1:2), b(1:LOOPCOUNT, 1:2)) copy(x)
          !$acc parallel loop worker reduction(+:x)
          DO
            DO WHILE (x .lt. LOOPCOUNT)
              CALL usleep(100)
              x = x + 1
            END DO
            DO i = 1, LOOPCOUNT
              b(i, 1) = b(i, 1) + a(i, 1)
            END DO
            !$acc loop worker
            DO i = 1, LOOPCOUNT
              b(i, 2) = b(i, 2) + a(i, 2)
            END DO
          END DO
        !$acc end data

        x_(1) = x

        !verify
        DO i = 1, LOOPCOUNT
          IF (abs(b(i, 1) - (b(i, 2) / 2))  .gt.  PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        IF (x_ .lt. 1) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END