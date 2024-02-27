!T1:data present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 100
        INTEGER :: i
        INTEGER, DIMENSION(N) :: a, a_dev

        ! Initialize array
        DO i = 1, N
          a(i) = i
        END DO

        ! Copy array to device
        !$acc data copyin(a)
        !$acc parallel loop present(a)
        DO i = 1, N
          a_dev(i) = a(i)
        END DO
        !$acc end parallel loop
        !$acc end data

        ! Check if data is present on device
        !$acc data copy(a_dev)
        !$acc parallel loop present(a_dev)
        DO i = 1, N
          IF (a_dev(i) .ne. i) THEN
            errors = errors + 1
          END IF
        END DO
        !$acc end parallel loop
        !$acc end data

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