! Assuming "acc_testsuite.Fh" defines common test suite utilities and constants

!T1:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER, DIMENSION(1024) :: a, b, result
        INTEGER :: i, errors = 0
        
        ! Initialize the arrays
        DO i = 1, 1024
          a(i) = i
          b(i) = i + 1024
        END DO
        
        ! Offload initial computations to two different async queues
        !$acc parallel loop async(1)
        DO i = 1, 1024
          a(i) = a(i) * 2
        END DO
        !$acc parallel loop async(2)
        DO i = 1, 1024
          b(i) = b(i) * 3
        END DO
        
        ! Explicitly wait for async queue 1 before proceeding with async queue 2
        CALL acc_wait_async(1, 2)
        
        ! Assuming computations reliant on both 'a' and 'b' modifications can now proceed
        !$acc parallel loop copyout(result) async(2)
        DO i = 1, 1024
          result(i) = a(i) + b(i)
        END DO
        
        !$acc wait(2)
        
        ! Validate results
        DO i = 1, 1024
          IF (result(i) /= (i*2 + (i+1024)*3)) THEN
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
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT(failcode)
      END PROGRAM main