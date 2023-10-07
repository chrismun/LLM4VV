#ifndef T1
!T1:acc unmap data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: host_data
        INTEGER, DIMENSION(:), DEVICE :: device_data

        ALLOCATE(host_data(10))
        host_data = 1
        device_data = host_data

        ! map host data to device data manually
        CALL acc_map_data(host_data, device_data, SIZEOF(host_data))
        
        ! Check presence before unmap
        IF (.NOT. acc_is_present(host_data, SIZEOF(host_data))) THEN
          errors = errors + 1
        END IF

        ! unmap the data from the device
        CALL acc_unmap_data(host_data)

        ! check the presence after unmap
        IF (acc_is_present(host_data, SIZEOF(host_data))) THEN
          errors = errors + 1
        END IF

        DEALLOCATE(host_data)

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