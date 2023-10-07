#ifndef T1
!T1:kernels construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(LOOPCOUNT) :: a, b, c

        !$acc kernels default(present)
        DO i = 1, LOOPCOUNT
          a(i) = 3.14
          b(i) = 2.71
          c(i) = a(i) * b(i)
        END DO
        !$acc end kernels

        DO i = 1, LOOPCOUNT
          IF (ABS(c(i) - 8.214) .gt. PRECISION) THEN
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

In this code, we are testing the kernels construct default clause with the present option. We create three arrays, a, b, and c, and initialize a and b with some values. We then use a kernels construct with the default(present) clause, which means that only present variables will be copied to the device. Inside the construct, we calculate the product of the corresponding elements of a and b and store it in c. After the construct, we check if the calculated values in c are correct. If there are no errors, the test returns 0, otherwise it returns a non-zero value.