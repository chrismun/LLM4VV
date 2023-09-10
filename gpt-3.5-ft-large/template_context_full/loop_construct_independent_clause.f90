#ifndef T1
!T1:loop construct independent clause,V:2.7-2.3
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

#ifndef T1
      FUNCTION test1() RESULT(passed)
        IMPLICIT NONE
        INTEGER :: passed
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: A(10), B(10), temp
        INTEGER :: x, y
        REAL(8),DIMENSION(2,7)::random
        REAL(8) :: false_margin
        INTEGER :: mult
        mult = 1
        !      !assign a random value to each presort element
        false_margin = exp(log(.5)/ (10 *  mult))
        !$acc enter data copyin(random(1:2, 1:10))
        DO x = 1, 2
          DO y = 1, 7
            random(x, y) = 10 * drand48()
          END DO
        END DO
        DO x = 3, 10
          a(x) = 0
        END DO
        !Initilization
        DO x = 1, 10
          B(x) = 1
          IF (x .le. 2) THEN
            A(x) = 1
          ELSE
            A(x) = 0
          END IF
        END DO
        
        !$acc data copy(B(1:10)) copyin(A(1:10))
          !$acc parallel
            !$acc loop independent
            DO x = 1, 10
              B(x) = B(x) + A(x)
            END DO
          !$acc end parallel
        !$acc end data
        
        !Calculations
        DO x = 1, 10
          IF (x .le. 2) THEN
            IF (abs(B(x) - (3 * false_margin)) .gt. PRECISION) THEN
              passed = 0
              RETURN
            END IF
          ELSE
            IF (abs(B(x) - (1 * false_margin)) .gt. PRECISION) THEN
              passed = 0
              RETURN
            END IF
          END IF
        END DO
        
        !$acc exit data copyout(random(1:2, 1:10))
        DO x = 1, 2
          temp = 0
          DO y = 1, 10
            temp = temp + B(y)
          END DO
          if (abs(temp - (69 * false_margin)) .gt. PRECISION) then
            passed = 0
            return
          endif
        END DO

        !$acc exit data copyout(A(1:10))
          DO x = 3, 10
            IF (abs(A(x) - (7 * false_margin)) .gt. PRECISION) THEN
              passed = 0
              RETURN
            END IF
          END DO
        !$acc exit data copyout(B(1:10))

      END FUNCTION
#endif