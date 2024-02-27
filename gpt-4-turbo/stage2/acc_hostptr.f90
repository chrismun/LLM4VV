!acc_testsuite.Fh content
      INTEGER, PARAMETER :: NUM_TEST_CALLS = 1
!End of acc_testsuite.Fh content

!T1:acc_hostptr,V:2.7-2.3
      MODULE test_acc_hostptr
        USE ISO_C_BINDING
        USE OPENACC
      CONTAINS
        LOGICAL FUNCTION test1()
          IMPLICIT NONE
          INTEGER, DIMENSION(:), ALLOCATABLE :: src_array
          TYPE(C_PTR) :: device_ptr, host_ptr
          INTEGER(C_SIZE_T) :: array_size
          INTEGER :: errors
          INTEGER :: i

          errors = 0
          array_size = 10_C_SIZE_T

          ! Allocate and initialize the array
          ALLOCATE(src_array(array_size))
          DO i = 1, array_size
            src_array(i) = i
          END DO

          ! Copy the array to the device and obtain the device pointer
          device_ptr = acc_copyin(src_array, array_size * SIZEOF(src_array(1)))

          ! Use acc_hostptr to get the host pointer associated with the device pointer
          host_ptr = acc_hostptr(device_ptr)

          ! Check if acc_hostptr successfully returned the original address by comparing values
          ! Note: Assuming a clean and clear implementation where device and host 
          ! synchronization do not cause discrepancies, and pointers directly correlate.
          IF (host_ptr /= C_LOC(src_array)) THEN
            errors = errors + 1
          END IF

          DEALLOCATE(src_array)

          IF (errors .eq. 0) THEN
            test1 = .TRUE.
          ELSE
            test1 = .FALSE.
          END IF
        END FUNCTION test1
      END MODULE test_acc_hostptr

      PROGRAM main
        USE test_acc_hostptr
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .OR. .NOT. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        CALL EXIT (failcode)
      END PROGRAM