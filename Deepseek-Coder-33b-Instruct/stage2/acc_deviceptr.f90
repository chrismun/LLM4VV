#ifndef T1
!T1:acc deviceptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: host_array
        INTEGER(KIND=acc_device_kind), DIMENSION(:), ALLOCATABLE :: device_array
        INTEGER(KIND=acc_device_kind) :: device_ptr

        ! Allocate host array
        ALLOCATE(host_array(10))

        ! Allocate device array
        ALLOCATE(device_array(10))

        ! Copy host array to device
        device_array = host_array

        ! Get device pointer
        device_ptr = acc_deviceptr(host_array)

        ! Check if device pointer is the same as host pointer
        IF (.NOT. ASSOCIATED(device_ptr, TARGET=host_array)) THEN
          errors = errors + 1
        END IF

        ! Deallocate host and device arrays
        DEALLOCATE(host_array)
        DEALLOCATE(device_array)

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
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
      END PROGRAM