PROGRAM verif_openacc_if_clause
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: errors = 0
        INTEGER :: i
        INTEGER, DIMENSION(10) :: testArray
        LOGICAL :: testCondition
        INTEGER :: failcode
        INTEGER :: numTestCalls = 1
        
        ! Initializing testCondition and testArray
        testCondition = .TRUE.
        testArray = 0
        
        ! Parallel region with the if clause
        !$acc parallel loop if(testCondition)
        DO i = 1, 10
          testArray(i) = i
        END DO
        !$acc end parallel loop
        
        ! Check if the testArray is modified as expected
        DO i = 1, 10
          IF (testArray(i) /= i) THEN
            errors = errors + 1
          END IF
        END DO

        ! Based on errors, set the failcode
        IF (errors == 0) THEN
          failcode = 0
        ELSE
          failcode = 1
        END IF
        
        ! Return or print the result based on failcode
        IF (failcode == 0) THEN
          PRINT *, "Test Passed."
        ELSE
          PRINT *, "Test Failed."
        END IF
      END PROGRAM verif_openacc_if_clause