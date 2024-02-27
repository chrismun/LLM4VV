!T1:host_data construct use_device clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE

        ! Assuming acc_testsuite.Fh provides necessary test suite infrastructure.
        INCLUDE "acc_testsuite.Fh"

        INTEGER, DIMENSION(:), ALLOCATABLE :: hostArray
        INTEGER, DIMENSION(:), ALLOCATABLE, DEVICE :: deviceArray
        INTEGER :: arraySize, i, errors
        INTEGER(HOST_TYPE) :: devicePtr
        arraySize = 1024
        errors = 0

        ALLOCATE(hostArray(arraySize))
        ALLOCATE(deviceArray(arraySize))

        ! Initialize host array with some values.
        DO i = 1, arraySize
          hostArray(i) = i
        END DO

        ! Copy data from host to device.
        hostArray = hostArray

        ! Use the device address in a host_data construct.
        !$acc host_data use_device(deviceArray)
          devicePtr = acc_deviceptr(deviceArray)
          ! Here, one might pass devicePtr to a lower-level API.
          ! For the purpose of this test, we simply check if devicePtr is not null.
          IF (devicePtr == 0) THEN
            errors = errors + 1
          END IF
        !$acc end host_data

        ! Cleanup
        DEALLOCATE(hostArray)
        DEALLOCATE(deviceArray)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.  ! No errors found.
        ELSE
          test1 = .TRUE.   ! Errors were found.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        ! Assuming acc_testsuite.Fh sets up the test environment correctly.
        INCLUDE "acc_testsuite.Fh"

        LOGICAL :: test1
        failcode = 0
        failed = .FALSE.

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .OR. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF

        CALL EXIT(failcode)
      END PROGRAM