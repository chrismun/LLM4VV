!T1:acc get property,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        USE ISO_C_BINDING
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: device_num, device_type
        INTEGER(KIND=C_SIZE_T) :: memory_size
        INTEGER, PARAMETER :: acc_device_host = 1
        INTEGER, PARAMETER :: acc_property_memory = 1

        ! Get the device number and type
        device_num = acc_get_device_num(acc_device_host)
        device_type = acc_get_device_type()

        ! Get the memory size of the device
        memory_size = acc_get_property(device_num, device_type, acc_property_memory)

        ! Check if the memory size is greater than 0
        IF (memory_size .LE. 0) THEN
          errors = errors + 1
        END IF

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