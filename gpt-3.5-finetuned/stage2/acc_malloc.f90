!T1:acc malloc,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER :: n = 100
        REAL(8), DIMENSION(n) :: a
        INTEGER :: i

        !$acc enter data create(a(1:n))
        !$acc update device(a(1:n))
        !$acc parallel loop
        DO i = 1, n
          a(i) = i
        END DO
        !$acc exit data copyout(a(1:n))

        DO i = 1, n
          IF (a(i) .ne. i) THEN
            errors = errors + 1
          END IF
        END DO

        ! free the acc memory
        !$acc exit data delete(a(1:n))

        IF (errors .eq. 0 .and. .NOT. acc_get_device_num(a) .eq. -1) THEN
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