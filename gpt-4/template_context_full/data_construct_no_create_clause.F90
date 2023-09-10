#ifndef T1
!T1:data construct no_create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        REAL, DIMENSION(100):: a, b
        INTEGER :: i, errors = 0

        a = 1
        b = 0

        !$ACC DATA NO_CREATE(b)
        !$ACC PARALLEL LOOP COPY(a)
        DO i=1, 100
          b(i) = a(i)
        END DO
        !$ACC END DATA

        DO i=1, 100
          IF (b(i).ne. a(i)) THEN
            errors = errors + 1
          END IF
        END DO

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