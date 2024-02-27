!T1:update directive,V:2.7-2.3
      MODULE test_module
        USE OPENACC
        IMPLICIT NONE
      END MODULE test_module

      LOGICAL FUNCTION test1()
        USE test_module
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(10) :: hostArray
        INTEGER :: i, errors = 0

        ! Initialize host array
        hostArray = (/ (i, i=1,10) /)

        ! Move data to device
        !$acc enter data copyin(hostArray)

        ! Modify data in device
        !$acc parallel loop
        DO i = 1, 10
          hostArray(i) = hostArray(i) * 2
        END DO

        ! Update host with modified data
        !$acc update self(hostArray)

        ! Check for correctness
        DO i = 1, 10
          IF (hostArray(i) /= i*2) THEN
            errors = errors + 1
          END IF
        END DO
        
        !$acc exit data delete(hostArray)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END


      PROGRAM main
        USE test_module
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
        CALL EXIT (failcode)
      END PROGRAM main