#ifndef T1
!T1:acc memcpy from device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: host_data
        INTEGER(C_PTR) :: device_ptr
        INTEGER(C_SIZE_T) :: bytes
        INTEGER :: n = 1000
        INTEGER :: i

        ! Allocate host and device memory
        ALLOCATE(host_data(n))
        device_ptr = acc_malloc(n*C_SIZEOF(host_data(1)))
        IF (device_ptr == C_NULL_PTR) THEN
          ERRORS = ERRORS + 1
        END IF

        ! Initialize host data
        DO i = 1, n
          host_data(i) = i
        END DO

        ! Copy host data to device
        CALL acc_memcpy_to_device(device_ptr, C_LOC(host_data(1)), n*C_SIZEOF(host_data(1)))

        ! Modify host data
        DO i = 1, n
          host_data(i) = 0
        END DO

        ! Copy data from device to host
        CALL acc_memcpy_from_device(C_LOC(host_data(1)), device_ptr, n*C_SIZEOF(host_data(1)))

        ! Verify the correctness
        DO i = 1, n
          IF (host_data(i) /= i) THEN
            ERRORS = ERRORS + 1
          END IF
        END DO

        ! Cleanup: free device memory
        CALL acc_free(device_ptr)

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