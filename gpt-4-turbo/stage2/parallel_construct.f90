!T1:parallel construct,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        
        INTEGER, DIMENSION(10) :: testArray
        INTEGER :: i
        INTEGER :: errors = 0
        
        ! Initializing array elements to 0
        testArray = 0
        
        !$acc parallel loop
        DO i = 1, 10
          testArray(i) = i + 1
        END DO
        !$acc end parallel

        ! Check if parallel computation was successful
        DO i = 1, 10
          IF (testArray(i) /= i + 1) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, 1  ! Adjust based on how many iterations of the test you wish to run
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        PRINT *, "Test failed with code:", failcode
        CALL EXIT (failcode)
      END PROGRAM