! Template updated for testing the OpenACC wait directive
!T1:wait directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: array_host
        INTEGER, DIMENSION(:), ALLOCATABLE :: array_device
        INTEGER :: size, i
        
        size = 100
        ALLOCATE(array_host(size))
        ALLOCATE(array_device(size))
        
        ! Initialize host array
        DO i = 1, size
          array_host(i) = i
        END DO
        
        ! Copying data to device asynchronously (using async clause)
        !$acc enter data copyin(array_host) async(1)
        
        ! Perform computation on the device (also asynchronously)
        !$acc parallel loop async(1)
        DO i = 1, size
          array_host(i) = array_host(i) + 1
        END DO
        
        ! Wait for all previously enqueued operations in async queue 1 to complete
        !$acc wait(1)
        
        ! Copy back the array from the device to the host
        !$acc exit data copyout(array_host)

        ! Verify the operation completed correctly
        DO i = 1, size
          IF (array_host(i) /= i+1) THEN
            errors = errors + 1
          END IF
        END DO

        ! Cleanup
        DEALLOCATE(array_host)
        DEALLOCATE(array_device)
        
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
        CALL EXIT (failcode)
      END PROGRAM