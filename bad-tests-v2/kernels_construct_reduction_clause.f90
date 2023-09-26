#ifndef T1
!T1:kernels construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, j, k
        REAL :: a(10), b(10), c(10)
        REAL :: sum

        !$acc kernels reduction(+:sum)
        DO i = 1, 10
          DO j = 1, 10
            DO k = 1, 10
              a(i, j, k) = i + j + k
              b(i, j, k) = i * j * k
              c(i, j, k) = a(i, j, k) + b(i, j, k)
            END DO
          END DO
        END DO
        !$acc end kernels

        sum = 0.0
        DO i = 1, 10
          DO j = 1, 10
            DO k = 1, 10
              sum = sum + c(i, j, k)
            END DO
          END DO
        END DO

        IF (sum .ne. 1000.0) THEN
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