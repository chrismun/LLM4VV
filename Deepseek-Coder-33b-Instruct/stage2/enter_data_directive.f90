#ifndef T1
!T1:enter data directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        INTEGER, DIMENSION(:), ALLOCATABLE :: host_array, device_array

        ALLOCATE(host_array(N), device_array(N))

        ! Initialize host array
        DO i = 1, N
          host_array(i) = i
        END DO

        ! Copy host array to device
        !$acc enter data copyin(host_array) create(device_array)

        ! Update device array using enter data directive
        !$acc enter data copyin(host_array(1:N))
        !$acc parallel loop present(device_array)
        DO i = 1, N
          device_array(i) = host_array(i)
        END DO
        !$acc end parallel loop
        !$acc exit data copyout(device_array)

        ! Check if device array is updated correctly
        DO i = 1, N
          IF (device_array(i) .ne. host_array(i)) THEN
            errors = errors + 1
          END IF
        END DO

        DEALLOCATE(host_array, device_array)

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