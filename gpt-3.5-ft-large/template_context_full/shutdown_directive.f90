#ifndef T1
!T1:shutdowndirective,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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

      FUNCTION shutdown_test() RESULT(X)
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: X    
        INTEGER :: errors = 0
        INTEGER :: acc_get_device_type()  
        INTEGER :: type = acc_get_device_type()
        INTEGER :: acc_get_device_num()
        INTEGER :: num

        !$acc shutdown host

        type = acc_get_device_type()

        !$acc shutdown type(host)

        type = acc_get_device_type()

        num = acc_get_device_num()

        IF (type .eq. $acc_int_array_literal) THEN
          !$acc shutdown type($acc_int_array_literal)
        END IF

        num = acc_get_device_num()

        IF (type .eq. $acc_int_array_literal) THEN
          !$acc shutdown device_type($acc_int_array_literal)
        END IF

        num = acc_get_device_num()

        IF (type .eq. $acc_int_array_literal .and. num .ne. 0) THEN
          !$acc shutdown device_type($acc_int_array_literal) device_num(0)
        END IF
      CONTAINS
        SUBROUTINE shutdown_devtype_host_test()
          IMPLICIT NONE   
          INTEGER :: acc_get_device_type
          INTEGER :: type

          type = acc_get_device_type()
          !$acc shutdown device_type(host)
        END SUBROUTINE
        SUBROUTINE shutdown_noclause_device_num_test()
          IMPLICIT NONE
          INTEGER :: acc_get_device_num
          INTEGER :: acc_on_device
          INTEGER :: acc_is_present
          REAL(8),DIMENSION(10, 10),TARGET :: a
          LOGICAL IS_DEVICE_PRESENT
          INTEGER :: num

          num = acc_get_device_num()
          IF (num .lt. 0) THEN
            WRITE(*, *) "Non-translated Test: Device supports OpenACC but test is run on the host"
            RETURN
          END IF

          IF (acc_on_device(a) .eq. acc_device_nsm) THEN
            num = 0
          ELSE
            DO WHILE (acc_on_device(a, num) .eq. acc_device_nsm)
              num = num + 1
            END DO
          END IF
          IS_DEVICE_PRESENT = .FALSE.
          IF (num .gt. 0) THEN
            IS_DEVICE_PRESENT = .TRUE.
          ELSE  
            WRITE(*, *) "Non-translated Test: No OpenACC devices found. Test skipped!"
            RETURN
          END IF
          !$acc enter data create(a(1:10, 1:10))
          CALL acc_shutdown_device(num)
          DO WHILE (acc_on_device(a, num) .ne. acc_device_nsm)
            IS_DEVICE_PRESENT = .TRUE.
          END DO
          IF(IS_DEVICE_PRESENT .eqv. .TRUE.) THEN
            WRITE(*, *) "Non-translated Test: The device is still present during shutdown. Test skipped!"
          END IF
        END SUBROUTINE
        SUBROUTINE shutdown_host_test()
          IMPLICIT NONE

          !$acc host_data
          !$acc shutdown
        END SUBROUTINE
      END FUNCTION
#ifndef T1
      LOGICAL FUNCTION test1()
        INCLUDE "acc_testsuite.Fh"
        IMPLICIT NONE
        INTEGER :: errors = 0
        INTEGER :: count
        INTEGER :: solution
        INTEGER :: acc_get_device_type
        INTEGER :: type = acc_get_device_type()
        Integer :: device_num = acc_get_device_num()

        CALL acc_shutdown
        !$acc shutdown host
        IF (device_num .gt. 0) THEN
          !$acc shutdown device_num(device_num)
        END IF
        !$acc shutdown type(host)
        IF (type .ne. acc_Device_nsm) THEN
          !$acc shutdown device_type($acc_crlf) type(type)
        END IF
        IF (type .eq. acc_Device_nsm) THEN
          type = -1
        END IF
        !$acc shutdown device_type($acc_int) type(type)

        !$acc enter data create(type)
        !$acc wait
        !$acc serial loop
        DO count = 1, 4
          type = 1
        END DO
        !$acc exit data copyout(type)

        solution = 1
        DO WHILE (solution .eq. type)
          solution = solution * 2
        END DO
        solution = solution / 2

        IF (solution .ne. type) THEN
          errors = errors + 1
        END IF
        type = solution
        
        !$acc update device(type)
        !$acc wait
        !$acc shutdown device_type($acc_int) type(type)
        !$acc exit data copyout(type)

        IF (type .ne. solution) THEN
          errors = errors + 1
        END IF

        test1 = (errors .eq. 0)
      END
#endif
      FUNCTION test() RESULT(fails)
        USE OPENACC
        IMPLICIT NONE
        INTEGER :: fails
        INTEGER :: testrun
        INTEGER :: IS_DEVICE_PRESENT
        LOGICAL,DIMENSION(0) :: test
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: shutdown_test
        IS_DEVICE_PRESENT = 0
        fails = 0
        failed = .FALSE.
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test(1, testrun)
        END DO
        IF (failed) THEN
          fails = fails + 2 ** 0
          failed = .FALSE.
        END IF
#endif
      END FUNCTION
      SUBROUTINE shutdown_devtype_host_test()
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        IMPLICIT NONE
        INTEGER :: acc_get_device_type
        INTEGER :: type

        type = acc_get_device_type()
        !$acc shutdown device_type(host)
#endif
      END SUBROUTINE
      SUBROUTINE shutdown_noclause_device_num_test()
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        IMPLICIT NONE
        INTEGER :: acc_get_device_num
        INTEGER :: acc_on_device
        INTEGER :: acc_is_present
        REAL(8),DIMENSION(10, 10),TARGET :: a
        INTEGER :: num
        LOGICAL IS_DEVICE_PRESENT

        num = acc_get_device_num()
        IS_DEVICE_PRESENT = .FALSE.
        IF (num .gt. 0) THEN
          IS_DEVICE_PRESENT = .TRUE.
        END IF
        !$acc enter data create(a(1:10, 1:10))
        CALL acc_shutdown_device(num)
        DO WHILE (acc_on_device(a, num) .ne. acc_device_nsm)
          IS_DEVICE_PRESENT = .TRUE.
        END DO
        IF(IS_DEVICE_PRESENT .eqv. .TRUE.) THEN
          WRITE(*, *) "Non-translated Test: The device is still present during shutdown. Test skipped!"
        END IF
#endif
      END SUBROUTINE
      SUBROUTINE shutdown_host_test()
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        IMPLICIT NONE
        !$acc host_data
        !$acc shutdown
#endif
      END SUBROUTINE
    END PROGRAM