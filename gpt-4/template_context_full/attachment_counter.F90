!T1:attachment counter,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: array
        INTEGER, DEVICE, POINTER :: d_ptr
        INTEGER :: host_ptr

        ! Allocate array on host and initialize values
        ALLOCATE(array(10))
        array = (/ (i, i=1,10) /)

        ! Allocate array on device
        d_ptr = acc_malloc(SIZE(array))
        IF (.not. verify_present(d_ptr, SIZE(array))) THEN
          errors = errors + 1
        END IF

        ! Attach host array to device pointer
        CALL acc_attach(d_ptr, array)

        ! Update value in host array
        array(2) = 20
        host_ptr = array(2)

        ! Update the device
        CALL acc_update_device(array, SIZE(array))

        ! Check if value got updated in device
        IF (host_ptr /= d_ptr(2)) THEN
          errors = errors + 1
        END IF

        ! Detach the host and device pointers
        CALL acc_detach(d_ptr, array)

        if (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T2
        logical :: test1
#endif
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        CALL EXIT (failcode)
      END PROGRAM main