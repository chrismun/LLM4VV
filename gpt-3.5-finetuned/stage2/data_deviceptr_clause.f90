!T1:data deviceptr clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER,PARAMETER :: N = 1000
        REAL(8),DIMENSION(N):: a
        REAL(8),DIMENSION(N),DEVICE :: a_copy
        INTEGER :: x

        a = 0.0
        a_copy = 0.0

        !$acc data copy(a(1:N)) deviceptr(a_copy(1:N))
          !$acc parallel
            !$acc loop
            DO x = 1, N
              a_copy(x) = 1.0
            END DO
          !$acc end parallel
        !$acc end data

        DO x = 1, N
          IF (abs(a(x) - 0.0) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

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