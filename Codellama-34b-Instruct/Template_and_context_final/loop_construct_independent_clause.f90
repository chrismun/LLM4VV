fortran
#ifndef T1
!T1:loop construct independent clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i, j, k
        REAL :: a(100), b(100), c(100)
        REAL :: sum
        
        !$acc parallel loop independent
        DO i = 1, 100
          a(i) = 1.0
          b(i) = 2.0
          c(i) = 3.0
        END DO
        
        !$acc parallel loop reduction(+:sum)
        DO i = 1, 100
          sum = sum + a(i) * b(i) * c(i)
        END DO
        
        IF (sum .ne. 60000.0) THEN
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