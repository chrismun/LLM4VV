fortran
#ifndef T1
!T1:serial construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, j, k
        REAL :: a(10), b(10), c(10)
        REAL :: expected(10)
        
        !$acc serial private(a, b, c)
        DO i = 1, 10
          a(i) = i
          b(i) = i * 2
          c(i) = i * 3
        END DO
        !$acc end serial
        
        !$acc serial private(a, b, c)
        DO i = 1, 10
          a(i) = a(i) + b(i) + c(i)
        END DO
        !$acc end serial
        
        !$acc serial private(a, b, c)
        DO i = 1, 10
          expected(i) = a(i) + b(i) + c(i)
        END DO
        !$acc end serial
        
        DO i = 1, 10
          IF (a(i) .ne. expected(i)) THEN
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