#ifndef T1
!T1:acc map data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        REAL(KIND=4), DIMENSION(:), ALLOCATABLE :: host_data
        REAL(KIND=4), DIMENSION(:), ALLOCATABLE :: device_data
        INTEGER :: i

        ! Allocate host memory
        ALLOCATE(host_data(N))
        ALLOCATE(device_data(N))

        ! Initialize host data
        DO i = 1, N
          host_data(i) = REAL(i)
        END DO

        ! Map host data to device data
        CALL acc_map_data(host_data, device_data, N*4)

        ! Copy data from host to device
        CALL acc_memcpy_to_device(device_data, host_data, N*4)

        ! Check that data was correctly copied
        DO i = 1, N
          IF (device_data(i) .NE. REAL(i)) THEN
            errors = errors + 1
          END IF
        END DO

        ! Unmap data
        CALL acc_unmap_data(host_data)

        ! Deallocate host memory
        DEALLOCATE(host_data)
        DEALLOCATE(device_data)

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