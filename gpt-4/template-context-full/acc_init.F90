!T1:acc init,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
		INTEGER(acc_device_kind), DIMENSION(5) :: av_devices
		INTEGER :: kind, i 
		INTEGER :: dev_type = acc_device_nvidia ! We use NVIDIA as an example

		av_devices(1) = acc_device_none 
		av_devices(2) = acc_device_default
		av_devices(3) = acc_device_host 
		av_devices(4) = acc_device_not_host
		av_devices(5) = acc_device_nvidia

		!Let's see if the acc_init correctly initializes the device.
		!We test this with diiferent device types
		DO i=1,5
			kind = av_devices(i)
			CALL acc_init(kind)
			IF (.NOT. acc_is_present((/1.0/), SIZEOF(1.0))) THEN
				errors = errors + 1
			END IF
		END DO
        
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION 

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
      END PROGRAM main