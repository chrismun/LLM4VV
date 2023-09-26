#ifndef T1
!T1:host_data construct if_present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        INCLUDE "acc_testsuite.Fh"
        IMPLICIT NONE

        INTEGER, DIMENSION(10):: a, b
        INTEGER:: i
        INTEGER:: errors = 0

        !! Initialize the regular array
        DO i = 1, 10
            a(i) = i
        END DO

        !! Using the host_data construct with if_present clause
        !$ACC ENTER DATA COPYIN(a)
        !$ACC HOST_DATA USE_DEVICE(a) IF_PRESENT
            DO i = 1, 10
                b(i) = a(i)
            END DO
        !$ACC END HOST_DATA

        !! Check whether the values in both arrays are equal
        DO i = 1, 10 
            IF (a(i) /= b(i)) THEN
                errors = errors + 1
            END IF
        END DO
        !$ACC EXIT DATA DELETE(a)

        IF (errors .eq. 0) THEN
             test1 = .FALSE.
        ELSE
             test1 = .TRUE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        USE OPENACC
        IMPLICIT NONE

        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        INTEGER :: failcode, testrun
        LOGICAL :: failed

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