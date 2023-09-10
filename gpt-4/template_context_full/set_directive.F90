! This code tests the OpenACC set directive in Fortran
! Default async, Device num, and Device type clauses are tested
! This will return 0 if the feature is working properly and not zero otherwise

#ifndef T1
!T1:set directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: TEST_DEVICE_NUM = 0
        INTEGER, PARAMETER :: TEST_ASYNC_TOP = acc_async_sync
        INTEGER, PARAMETER :: TEST_DEVICE_TYPE = acc_device_gpu

        INTEGER :: errors = 0

        ! Test set device_num clause
        !$acc set device_num(TEST_DEVICE_NUM)
        IF (acc_get_device_num() .NE. TEST_DEVICE_NUM) THEN
            errors = errors + 1
        END IF

        ! Test set default_async clause
        !$acc set default_async(TEST_ASYNC_TOP)
        IF (acc_get_default_async() .NE. TEST_ASYNC_TOP) THEN
            errors = errors + 1
        END IF

        ! Test set device_type clause
        !$acc set device_type(TEST_DEVICE_TYPE)
        IF (acc_get_device_type() .NE. TEST_DEVICE_TYPE) THEN
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
      END PROGRAM main