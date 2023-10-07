#ifndef T1
!T1:kernels construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, j, k
        REAL :: a(100), b(100), c(100)
        REAL :: sum

        !$acc kernels
        !$acc loop gang(static:1)
        DO i = 1, 100
          a(i) = i
          b(i) = i * 2
          c(i) = i * 3
        END DO
        !$acc end kernels

        !$acc kernels
        !$acc loop gang(static:1)
        DO i = 1, 100
          sum = 0
          DO j = 1, 100
            sum = sum + a(j) * b(j) * c(j)
          END DO
          WRITE (*,*) "Sum = ", sum
        END DO
        !$acc end kernels

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