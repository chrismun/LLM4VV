!T1:kernels construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: i

        INTEGER, DIMENSION(100) :: a, b, c
        DO i=1, 100
            a(i) = i
            b(i) = 2 * i
        END DO
        
        !$ACC ENTER DATA COPYIN(a, b) CREATE(c)
        !$ACC KERNELS
            DO i=1,100
                c(i) = a(i) + b(i)
            END DO
        !$ACC END KERNELS
        !$ACC WAIT 
        !$ACC EXIT DATA COPYOUT(c)
        
        ! Checking the result
        DO i=1,100
            IF (c(i) /= 3 * i) THEN
                errors = errors + 1
            END IF
        END DO

        IF (errors .eq. 0) THEN
            test1 = .FALSE.
        ELSE
            test1 = .TRUE.
        END IF
      END FUNCTION test1
      
     
     PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        
        failed = .FALSE.
        failcode = 0

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF

        CALL EXIT (failcode)
      END PROGRAM main