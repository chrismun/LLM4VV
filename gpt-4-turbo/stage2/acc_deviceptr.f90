! Assuming acc_testsuite.Fh provides necessary infrastructure for the test suite
!T1:acc_deviceptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        USE, INTRINSIC :: ISO_C_BINDING, ONLY : C_PTR, C_F_POINTER
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(:), ALLOCATABLE :: host_array
        TYPE(C_PTR) :: device_ptr
        LOGICAL :: isOnDevice
        INTEGER :: errors = 0
        INTEGER :: i, N

        ! Initialize a test array
        N = 100
        ALLOCATE(host_array(N))
        host_array = (/(i, i=1,N)/)

        ! Use OpenACC to manage the array on the device
        !$acc enter data copyin(host_array(:))

        ! Get the device pointer
        device_ptr = acc_deviceptr(host_array)

        ! Check if the device_ptr is not null which means the data is present on the device
        IF (.NOT. C_ASSOCIATED(device_ptr)) THEN
          errors = errors + 1
        END IF

        !$acc exit data delete(host_array(:))

        ! Final assessment
        IF (errors .eq. 0) THEN
          test1 = .FALSE.   ! No errors
        ELSE
          test1 = .TRUE.    ! Errors occurred
        END IF

        ! Clean up
        DEALLOCATE(host_array)
      END

      PROGRAM main
        USE OPENACC
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
        ! Use standard Fortran method of stopping the program to ensure compatibility
        STOP failcode
      END PROGRAM main