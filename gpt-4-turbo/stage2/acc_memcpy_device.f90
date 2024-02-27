! Template extended with test for acc_memcpy_device
!T1:acc_memcpy_device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        USE ISO_C_BINDING, ONLY: C_SIZE_T, C_F_POINTER, C_LOC, C_NULL_PTR
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER(C_SIZE_T) :: num_bytes
        INTEGER, ALLOCATABLE, DIMENSION(:) :: host_array, check_array
        TYPE(C_PTR) :: dev_ptr_src, dev_ptr_dest
        INTEGER :: i

        ! Allocate and initialize arrays
        num_bytes = 256
        ALLOCATE(host_array(64))
        ALLOCATE(check_array(64))
        host_array = [(i, i=1, 64)]
        check_array = 0

        ! Allocate memory on the device
        dev_ptr_src = acc_malloc(num_bytes)
        IF (C_NULL_PTR == dev_ptr_src) THEN
          errors = errors + 1
          RETURN
        END IF
        
        dev_ptr_dest = acc_malloc(num_bytes)
        IF (C_NULL_PTR == dev_ptr_dest) THEN
          errors = errors + 1
          RETURN
        END IF

        ! Copy data from host to device
        acc_memcpy_to_device(dev_ptr_src, C_LOC(host_array), num_bytes)
        
        ! Use acc_memcpy_device to copy data within device
        CALL acc_memcpy_device(dev_ptr_dest, dev_ptr_src, num_bytes)
        
        ! Copy data from device to host for verification
        acc_memcpy_from_device(C_LOC(check_array), dev_ptr_dest, num_bytes)
        
        ! Verify that data was copied correctly
        DO i = 1, 64
          IF (check_array(i) /= host_array(i)) THEN
            errors = errors + 1
          END IF
        END DO
        
        ! Free device memory
        CALL acc_free(dev_ptr_src)
        CALL acc_free(dev_ptr_dest)

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