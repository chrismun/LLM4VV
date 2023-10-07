#ifndef T1
!T1:acc map data,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: host_data, host_data_mapped
        TYPE(C_PTR) :: device_data
        INTEGER(KIND=C_SIZE_T) :: bytes = 40

        ! Allocate memory on the device
        device_data = acc_malloc(bytes)

        ! Map the device memory to the host memory
        CALL acc_map_data(host_data_mapped, device_data, bytes)

        ! Check if the mapping was successful
        IF (C_ASSOCIATED(device_data)) THEN
          errors = errors + 1
        END IF

        ! Unmap the device memory
        CALL acc_unmap_data(host_data_mapped)

        ! Free the device memory
        CALL acc_free(device_data)

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