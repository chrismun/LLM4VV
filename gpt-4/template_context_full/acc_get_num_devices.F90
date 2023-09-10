#ifndef T1
!T1:acc get num devices,V:2.7-2.3
    LOGICAL FUNCTION test1()
    USE OPENACC
    IMPLICIT NONE
    INTEGER :: errors = 0
    INTEGER(acc_device_kind) :: dev_type
    INTEGER :: num_dev

    ! Assign the device type to use
    dev_type = acc_device_default

    ! Get the number of devices for the type
    num_dev = acc_get_num_devices(dev_type)

    ! If no device of 'dev_type' is available, acc_get_num_devices should return 0
    IF (num_dev .eq. 0) THEN
        errors = errors + 1
    END IF

    IF (errors .eq. 0) THEN
      test1 = .FALSE.
    ELSE
      test1 = .TRUE.
    END IF
    END FUNCTION test1
#endif

PROGRAM main
    IMPLICIT NONE
    INTEGER :: failcode = 0, testrun
    LOGICAL :: failed = .FALSE.
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
END PROGRAM main