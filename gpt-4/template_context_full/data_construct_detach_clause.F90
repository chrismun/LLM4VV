!T1:data construct detach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER, DIMENSION(10) :: arr
        INTEGER, POINTERS :: pArr
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER :: i

        ! Initialize the array
        DO i = 1, 10
          arr(i) = i
        END DO

        ! Create a device copy of arr and get a host pointer to it
        pArr(:) = arr(:)
        !$ACC ENTER DATA COPYIN(arr) ATTACH(pArr)

        ! Detach the array
        !$ACC EXIT DATA DETACH(pArr)

        ! Now, arr should be inaccessible
        ACC_ON_DEVICE: IF (acc_is_present(arr, SIZE(arr)) .NE. 0) THEN
          ACC_TESTSUITE_FAILURE(1, errors)
        END IF

        ! Finally, test if error count is 0
        IF (errors == 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1

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