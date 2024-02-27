! Assume acc_testsuite.Fh is provided as part of the testing framework
! which contains necessary macros and utility functions for error handling and setup.

!T1:acc_memcpy_d2d,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: N = 10
        INTEGER :: errors = 0
        INTEGER :: sourceArray(N), destArray(N), dataArray(N)
        INTEGER :: i

        ! Initializing test data
        DO i = 1, N
          sourceArray(i) = i
        END DO

        ! Allocating device memory and copying sourceArray to device
        ! The acc present or create directive ensures data is available on the device.
        !$acc enter data copyin(sourceArray)
        !$acc enter data create(destArray)
        
        ! Performing device-to-device copy.
        ! NOTE: Here, we assume only one device or targeting the same device, hence using 0 for device numbers.
        CALL acc_memcpy_d2d(destArray, sourceArray, SIZEOF(sourceArray), 0, 0)

        ! Copying destination array back to host for verification
        !$acc exit data copyout(destArray)

        ! Verifying the result
        DO i = 1, N
          IF (destArray(i) .ne. sourceArray(i)) THEN
            errors = errors + 1
          END IF
        END DO

        !$acc exit data delete(sourceArray, destArray)

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
      END PROGRAM