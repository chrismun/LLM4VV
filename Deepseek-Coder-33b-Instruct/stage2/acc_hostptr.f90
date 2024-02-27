!T1:acc hostptr,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=4), DIMENSION(:), ALLOCATABLE :: host_array, device_array
        REAL(KIND=4), POINTER :: host_ptr
        INTEGER :: i

        ! Allocate host and device arrays
        ALLOCATE(host_array(N), device_array(N))

        ! Initialize host array
        DO i = 1, N
          host_array(i) = REAL(i)
        END DO

        ! Copy data from host to device
        !$acc data copyin(host_array), copyout(device_array)
        !$acc host_data use_device(host_array, device_array)
        host_ptr => host_array(1)
        !$acc parallel loop pcopy(host_array)
        DO i = 1, N
          device_array(i) = host_array(i)
        END DO
        !$acc end host_data
        !$acc end data

        ! Verify that acc_hostptr returns the correct host pointer
        DO i = 1, N
          IF (.NOT. ASSOCIATED(host_ptr, host_array(i))) THEN
            errors = errors + 1
          END IF
        END DO

        ! Deallocate host and device arrays
        DEALLOCATE(host_array, device_array)

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