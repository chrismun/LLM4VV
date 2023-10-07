#ifndef T1
!T1:declare directive create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, POINTER :: devPtr, hosPtr
        INTEGER, DIMENSION(:) :: devArr, hosArr
        ALLOCATE(devArr(100))
        ALLOCATE(hosArr(100))

        devPtr => devArr
        hosPtr => hosArr

        !$ACC DECLARE CREATE(devPtr[:100])
        !$ACC ENTER DATA COPYIN(hosPtr[:100])
        !$ACC PARALLEL
        devPtr = hosPtr
        !$ACC END PARALLEL
      
        IF (SUM(ABS(devPtr - hosPtr)) /= 0) THEN
          errors = errors + 1
        END IF
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF

        DEALLOCATE(devArr,hosArr)
      END FUNCTION
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
      END PROGRAM main