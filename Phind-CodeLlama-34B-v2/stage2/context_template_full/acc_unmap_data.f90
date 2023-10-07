#ifndef T1
!T1:acc unmap data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), POINTER :: host_data
        INTEGER, DIMENSION(:), POINTER :: device_data
        INTEGER :: num_elements = 1024

        ALLOCATE(host_data(num_elements))
        host_data = 1

        ! Map data to device
        CALL acc_map_data(host_data, num_elements * SIZEOF(INTEGER))

        ! Unmap data from device
        CALL acc_unmap_data(host_data)

        ! Check if the data is still accessible on the host
        IF (ANY(host_data .NE. 1)) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF

        DEALLOCATE(host_data)
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