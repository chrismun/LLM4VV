! Compiler directives for test suite structure
!T1:declare directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: hostArray
        INTEGER :: i

        !$acc declare create(hostArray)

        ! Allocate the array and initialize values on the host
        ALLOCATE(hostArray(100))
        hostArray = [(i, i=1,100)]

        ! Perform operation on device
        !$acc parallel loop copy(hostArray)
        DO i = 1, SIZE(hostArray)
            hostArray(i) = hostArray(i) + 5
        END DO
        
        ! Check results
        DO i = 1, SIZE(hostArray)
            IF (hostArray(i) /= i + 5) THEN
                errors = errors + 1
            END IF
        END DO
        
        DEALLOCATE(hostArray)

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