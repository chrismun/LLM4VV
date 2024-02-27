!T1:data construct detach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(:), ALLOCATABLE, TARGET :: testArray
        INTEGER :: i, errors = 0
        INTEGER, PARAMETER :: arraySize = 100
        ALLOCATE(testArray(arraySize))
        
        ! Initialize array on host
        DO i = 1, arraySize
           testArray(i) = 1
        END DO
        
        ! Move data to device and modify it
        !$acc enter data copyin(testArray)
        !$acc parallel loop
        DO i = 1, arraySize
           testArray(i) = testArray(i) + 1
        END DO
        !$acc exit data copyout(testArray) detach(testArray)
        
        ! Check if modifications made on device are visible on host
        DO i = 1, arraySize
          IF (testArray(i) /= 2) THEN
            errors = errors + 1
          END IF
        END DO
        
        DEALLOCATE(testArray)
        
        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        EXTERNAL test1
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        CALL EXIT (failcode)
      END PROGRAM