#ifndef T1
!T1:loop construct gang clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER, PARAMETER :: N=1024
        INTEGER :: arr(N)
        INTEGER :: errors=0, i

        !initialize array
        arr = 0

        !$acc parallel loop gang
        DO i=1,N
            arr(i) = i
        END DO

        !now check if each element in the array equals to their index.
        DO i=1,N
            IF (arr(i) .NE. i) THEN
                errors = errors + 1
            END IF
        END DO

        IF (errors .eq. 0) THEN
            test1 = .TRUE.
        ELSE
            test1 = .FALSE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode
        LOGICAL :: failed
        INTEGER :: testrun
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
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM main